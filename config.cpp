#include <config.h>

int readFile(const QString &importPath, QString &str){
    QString path;
    if(importPath == NULL){
        path = getenv("HOME");
        path.append("/.proxyVerify");
        QString filename = "/proxys.cfg";
        path.append(filename);
    }else{
        path = importPath;
    }


    QFile *dataFile = new QFile;
    dataFile->setFileName(path);
    QTextStream *textStream = new QTextStream(dataFile);
    if(dataFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        str = textStream->readAll();
        dataFile->close();
        free(dataFile);
        free(textStream);
        return OK;
    }else{
        dataFile->close();
        delete(dataFile);
        delete(textStream);
        return RDFILE_ERROR;
    }

}

int writeFile(const QString &str){
    QString path = getenv("HOME");
    path.append("/.proxyVerify");
    QString filename = "/proxys.cfg";
    if(access(path.toAscii().data(),0))//判断目录是否存在
    {
        if(mkdir(path.toAscii().data(), S_IRWXU) == -1){
            return MKDIR_ERROR;
        }
    }
    QFile *dataFile = new QFile;
    dataFile->setFileName(path.append(filename));
    if(dataFile->open(QIODevice::WriteOnly | QIODevice::Text)){
        //dataFile->w
        dataFile->write(str.toAscii().data());
        dataFile->close();
        delete(dataFile);
    }else{
        dataFile->close();
        delete(dataFile);
        return CRFILE_ERROR;

    }

    return OK;
}

