#include <getWebPage.h>


htmlThread::htmlThread(const QString &url){
    this->url = url;
}
void htmlThread::run(){
    QString html;
    int status = getHtml(html);
    emit sendHtmlMsg(status, html);
}

int htmlThread::getHtml(QString &html){
    QString uSite, uAddr;
    hostent *hp;
    html = "";
    url = url.trimmed();
    int start = url.indexOf("http://");
    if(start == -1){
        start = 0;
    }else{
        start += 7;
    }
    url = url.mid(start);
    int siteEnd = url.indexOf("/");
    uSite = url.mid(0, siteEnd);
    uAddr = url.mid(siteEnd);
    //设置一个socket地址结构client_addr,代表客户机internet地址, 端口
    struct sockaddr_in client_addr, proxy_addr;
    bzero(&client_addr, sizeof(client_addr)); //把一段内存区的内容全部设置为0
    client_addr.sin_family = AF_INET; //internet协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
    client_addr.sin_port = htons(0); //0表示让系统自动分配一个空闲端口

    //创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        return ERROR;

    }

    //把客户机的socket和客户机的socket地址结构联系起来
    if (bind(client_socket, (struct sockaddr*) &client_addr,
             sizeof(client_addr))) {
        close(client_socket);
        return ERROR;
    }

    unsigned long ul = inet_addr(uSite.toAscii().data());
    if (ul == INADDR_NONE)
    {
        hp = gethostbyname(uSite.toAscii().data());
    }
    else
    {
        uAddr = inet_addr(uSite.toAscii().data());
        hp = gethostbyaddr((char*)&uAddr, sizeof(uAddr), AF_INET);
    }
    if   (hp == NULL)
    {
        close(client_socket);
        return URL_ERROR;
    }
    bzero(&proxy_addr, sizeof(proxy_addr));

    proxy_addr.sin_family = AF_INET;
    memcpy(&proxy_addr.sin_addr, hp->h_addr_list[0], sizeof(proxy_addr.sin_addr));
//    if(inet_aton(, &)==0){
//        close(client_socket);
//        return ERROR;
//    }
    proxy_addr.sin_port =htons(80);
    socklen_t proxy_addr_length = sizeof(proxy_addr);

    if (::connect(client_socket, (struct sockaddr*) &proxy_addr,proxy_addr_length) == -1){
        close(client_socket);
        return ERROR;
    }
    char header[BUFSIZ];
    strcat(header, "GET ");
    strcat(header, uAddr.toAscii().data());
    strcat(header, " HTTP/1.1\r\n");
    strcat(header, "HOST:");
    strcat(header, uSite.toAscii().data());
    strcat(header, "\r\nProxy-Connection: close\r\n\r\n");

    send(client_socket, header, strlen(header), 0);
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    while(recv(client_socket,buffer, BUFFER_SIZE, 0) > 0){
        html.append(buffer);
        bzero(buffer, BUFFER_SIZE);
    }
    close(client_socket);
    return OK;
}


