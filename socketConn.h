#ifndef SOCKETCONN_H
#define SOCKETCONN_H

#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket      // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <time.h>                //for time_t and time
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <stdio.h>
#include <QMainWindow>
#include <QTime>
#include <sys/ioctl.h>
#include <net/if.h>
#include <QThread>
#include <errno.h>
#include <pError.h>
#include <QTextCodec>


#define BUFFER_SIZE 2048
#define ETH_NAME "etho"
class proxyTest : public QThread{
    Q_OBJECT
public:
    proxyTest();
    proxyTest(int threadId, int id, bool isHttps, const QString ip, const QString port);
    ~proxyTest();
    void setProxyArgs(int threadId, int id, bool isHttps, const QString ip, const QString port);
signals:
    void sendMessage(int threadId, int id, const QString &ss);

private:
    int threadId;
    int id;
    bool isHttps;
    QString ip;
    QString port;
    int proxy_Auth();
protected:
    void run();
};

bool checkIP(QString ip);
int GetLocalAddress(char *ip);
bool checkPort(QString port);

#endif // SOCKETCONN_H
