#include "socketConn.h"

    proxyTest::proxyTest(){
    }
    proxyTest::proxyTest(int threadId, int id, bool isHttps, const QString ip, const QString port){
        this->id = id;
        this->ip = ip;
        this->port = port;
        this->threadId = threadId;
        this->isHttps = isHttps;
    }
    void proxyTest::setProxyArgs(int threadId, int id, bool isHttps, const QString ip, const QString port){
        this->id = id;
        this->ip = ip;
        this->port = port;
        this->threadId = threadId;
        this->isHttps = isHttps;
    }

    proxyTest::~proxyTest(){
    }

    void proxyTest::run(){
        proxy_Auth();
    }

    int proxyTest::proxy_Auth()
    {
        //设置一个socket地址结构client_addr,代表客户机internet地址, 端口
        struct sockaddr_in client_addr, proxy_addr;
        bzero(&client_addr, sizeof(client_addr)); //把一段内存区的内容全部设置为0
        client_addr.sin_family = AF_INET; //internet协议族
        client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
        client_addr.sin_port = htons(0); //0表示让系统自动分配一个空闲端口

        //创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (client_socket < 0) {
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_CR_SOCK_ERROR));
            return ERROR;

        }

        //设置非阻塞模式------start--------------//
        unsigned long ul=1;
        int rm=ioctl(client_socket,FIONBIO,&ul);
        if (rm==-1)
        {
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_SET_NBLOCK_ERROR));
            return ERROR;
        }
        //设置非阻塞模式------end--------------//


        //把客户机的socket和客户机的socket地址结构联系起来
        if (bind(client_socket, (struct sockaddr*) &client_addr,
                 sizeof(client_addr))) {
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_BIND_SOCK_ERROR));
            return ERROR;
        }

        //设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
        //struct sockaddr_in server_addr;
        //bzero(&server_addr, sizeof(server_addr));
        bzero(&proxy_addr, sizeof(proxy_addr));

        proxy_addr.sin_family = AF_INET;
        if(inet_aton(ip.toLatin1().data(), &proxy_addr.sin_addr)==0){
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_IP_ERROR));
            return ERROR;
        }
        proxy_addr.sin_port =htons(port.toInt());
        socklen_t proxy_addr_length = sizeof(proxy_addr);


//        struct timeval timeo;
//        socklen_t len = sizeof(timeo);
//        timeo.tv_sec = 100;
//        if (setsockopt(client_socket, SOL_SOCKET, SO_SNDTIMEO, &timeo, len) == -1)
//        {
//            return 0;
//        }


        QTime t;
        t.start();
        if (::connect(client_socket, (struct sockaddr*) &proxy_addr,proxy_addr_length) == -1){
            //设置超时------start--------------//
            struct timeval timeout;
            fd_set r;
            FD_ZERO(&r);
            FD_SET(client_socket,&r);
            timeout.tv_sec=10;
            timeout.tv_usec=0;
//            int error = -1;
            if(select(client_socket+1, NULL, &r, NULL, &timeout) <= 0)
            {

//                getsockopt(client_socket, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)(sizeof(int)));
//                if(error == EINPROGRESS){
                close(client_socket);
                emit sendMessage(threadId, id, QString::fromAscii(MESS_CONN_TIMEOUT));

                return ERROR;
//                }
            }
            //设置超时------end--------------//

        }





//        struct hostent *he;
//        he = gethostbyname("localhost");
        char header[BUFSIZ];//, GET[40];
        //GetLocalAddress(GET);
//        inet_ntop(AF_INET, (he->h_addr_list)[0], GET, 16);
        bzero(header, BUFSIZ);
        if(!isHttps){
            strcat(header, "GET http://www.baidu.com/");
        }else{
            strcat(header, "CONNECT www.dnspod.cn:443");
        }
        //strcat(header, "GET http://www.baidu.com443/");
        strcat(header, " HTTP/1.1\r\n");
        strcat(header, "HOST:");
        if(!isHttps){
            strcat(header, "www.baidu.com");
        }else{
            strcat(header, "www.dnspod.cn:443");
        }
        strcat(header, "\r\nProxy-Connection: Keep-Alive\r\n\r\n");

        send(client_socket, header, strlen(header), 0);
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        //int length = 0;


        unsigned long ul1=0;
        rm=ioctl(client_socket,FIONBIO,(unsigned long*)&ul1);
        if(rm==-1)
        {
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_SET_BLOCK_ERROR));
            return ERROR;
        }

//        struct timeval timeout;
//        timeout.tv_sec=10;
//        timeout.tv_usec=0;
//        int result = setsockopt(client_socket,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(struct timeval));
//        if (result < 0)
//        {
//            return ERROR;
//        }

        QString buf;

//        while(recv(client_socket,buffer, BUFFER_SIZE, 0) > 0){
//            buf.append(QString::fromLocal8Bit(buffer));
//            bzero(buffer, BUFFER_SIZE);
//        }


        int length = recv(client_socket,&buffer, BUFFER_SIZE, 0);
        if (length < 0) {
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_REV_DATA_ERROR));

            return ERROR;
        }
        buf.append(QString::fromLocal8Bit(buffer));


        QString chkWork;
        if(!isHttps){
            chkWork = QString::fromUtf8("百度");
        }else{
            chkWork = QString::fromUtf8("HTTP/1.0 200 Connection Established");
        }
        if(buf.contains(chkWork)){
            //关闭socket
            close(client_socket);
            emit sendMessage(threadId, id, QString::number((double)t.elapsed()/1000));  
            return OK;
        }else{
            //关闭socket
            close(client_socket);
            emit sendMessage(threadId, id, QString::fromAscii(MESS_CONN_ERROR));
            return ERROR;
        }


    }



int GetLocalAddress(char *szIPAddr)
{
    int sock ;
    struct sockaddr_in sin ;
    struct ifreq ifr ;
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock==-1)
    {
        return ERROR ;
    }
    strncpy(ifr.ifr_name,ETH_NAME,IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ-1]=0 ;
    if(ioctl(sock,SIOCGIFADDR,&ifr)<0)
    {
        return ERROR;
    }
    memcpy(&sin,&ifr.ifr_addr,sizeof(sin));
    sprintf(szIPAddr,"%s",inet_ntoa(sin.sin_addr));
    return OK;
}


bool checkIP(QString ip){
    //in_addr inp;
    if(inet_addr(ip.toLatin1().data()) == INADDR_NONE){
        return false;
    }else{
        return true;
    }
}

bool checkPort(QString port){
    bool ok;
    port.toInt(&ok);
    return ok;
}
