#ifndef PERROR_H
#define PERROR_H

#define OK 0                     //成功
#define ERROR -1                  //失败
#define CONN_TIMEOUT 1           //socket链接超时
#define MKDIR_ERROR 2            //创建文件夹失败
#define CRFILE_ERROR 3           //创建配置文件失败
#define RDFILE_ERROR 4           //读取配置文件失败
#define URL_ERROR   5

#define TYPE_HTTP 200
#define TYPE_HTTPS 201



#define MESS_CONN_TIMEOUT "Connect timeout."           //socket链接超时
#define MESS_MKDIR_ERROR "Create Directory failed."     //创建文件夹失败
#define MESS_CRFILE_ERROR "Create Config file failed."  //创建配置文件失败
#define MESS_RDFILE_ERROR "Read Config file failed."     //读取配置文件失败
#define MESS_REV_DATA_ERROR "Recieve data failed."      //接收数据错误
#define MESS_CR_SOCK_ERROR "Create socket failed."      //创建套节字错误
#define MESS_BIND_SOCK_ERROR "Bind socket failed."      //绑定套节字错误
#define MESS_IP_ERROR "Proxy's ip address error!"       //代理地址非法
#define MESS_CONN_ERROR "Wrong data."                    //错误的数据
#define MESS_SET_NBLOCK_ERROR "Set Non-blocking status failed."  //设置非阻塞模式错误
#define MESS_SET_BLOCK_ERROR "Set blocking status failed."  //设置非阻塞模式错误
#endif // PERROR_H
