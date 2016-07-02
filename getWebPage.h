#ifndef GETWEBPAGE_H
#define GETWEBPAGE_H
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>
#include <QString>
#include <sys/ioctl.h>
#include <net/if.h>
#include <QThread>
#include <QTextCodec>
#include <QString>
#include <arpa/inet.h>
#include <netdb.h>
#include <pError.h>
#include <stdio.h>

#define BUFFER_SIZE 2048


class htmlThread : public QThread{
    Q_OBJECT
public:
    htmlThread(const QString &url);
private:
    QString url;
    int getHtml(QString &html);

protected:
    void run();
signals:
    void sendHtmlMsg(int status, const QString &html);
};



#endif // GETWEBPAGE_H
