#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init(){
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForTr(gbk);
    QTextCodec::setCodecForLocale(gbk);
    QTextCodec::setCodecForCStrings(gbk);
    testingNum = 0;
    closeFlag = false;
    for(int i = 0; i < maxThread; i ++){
        threadQueue.push(i);
    }
    showTray();
    int i = 0;
    while(i < maxThread + 1){
        threads[i] = NULL;
        i ++;
    }
    barLabel = new QLabel("");
    barLabel->setFixedWidth(200);
    barLabel->setFixedHeight(17);
    barLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->statusBar->addWidget(barLabel);
    connect(ui->tableWidget->del,SIGNAL(activated()),this,SLOT(deleteSelectedRows()));
    connect(ui->tableWidget->copy,SIGNAL(activated()),this,SLOT(copySelectedRows()));
    connect(ui->tableWidget->verify,SIGNAL(activated()),this,SLOT(verifySelectedRows()));
    loadConf();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete restore;
    delete mini;
    delete quit;
    delete menu;
    delete trayIcon;
    delete barLabel;
    int i = 0;
    while(i < maxThread){
        if(threads[i] != NULL){
            delete threads[i];
        }
        i ++;
    }
}

void MainWindow::handleThread(int threadId, int id, const QString &str){
//    mutex.lock();
    --testingNum;
//    mutex.unlock();
    handelMsg(id, str);
    threadQueue.push(threadId);
    barLabel->setText(tr("current:").append(QString::number(testingNum)).append("  Waiting:").append(QString::number(waitQueue.size())));
    threads[threadId]->wait();
    delete threads[threadId];
    threads[threadId]= NULL;
    if(waitQueue.size() > 0){
        createThread(waitQueue.front());
        waitQueue.pop();
    }
    if(testingNum <= 0){
        enableUI(true);
        ui->tableWidget->sortByColumn(2, Qt::AscendingOrder);
        barLabel->setText("");
    }

}

void MainWindow::on_button_verify_clicked()
{
    if(ui->tableWidget->rowCount() > 0){
        int itCount = 0;
        enableUI(false);
        while(itCount < ui->tableWidget->rowCount() && ui->tableWidget->rowCount() > 0){
            createThread(itCount);
            ++itCount;
        }
        barLabel->setText(tr("current:").append(QString::number(testingNum)).append("  Waiting:").append(QString::number(waitQueue.size())));
    }
}

void MainWindow::on_button_quit_clicked()
{
    closeFlag = true;
    this->close();

}

void MainWindow::on_button_add_clicked()
{
    if(addLine(ui->ip->text(), ui->port->text()) != ERROR){
        ui->ip->setText("");
        ui->port->setText("");
    }else{
        QMessageBox::critical(this, "failed", "Invalid IP address or port.");
    }
}
void MainWindow::handelMsg(int id, const QString &str){
    QTableWidgetItem *item = new QTableWidgetItem(str);
    bool ok;
    float value = str.toFloat(&ok);
    if(ok){
        item->setData(Qt::DisplayPropertyRole, value);
    }else{
        item->setData(Qt::DisplayPropertyRole, -1);
    }
//    mutex.lock();
    ui->tableWidget->setItem(id, 2, item);
//    mutex.unlock();
}

void MainWindow::on_button_paste_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString text;
    text= clipboard->text();
    if(ParseToProxys(text) > 0){
        saveConf();
    }


}
int MainWindow::addLine(const QString ip, const QString port){
    if( ip.size() != 0 && port.size() != 0 && checkIP(ip) && checkPort(port) && !checkExist(ip, port)){
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(ip));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(port));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem("Not verified."));
        return rowCount;
    }else{
        return ERROR;

    }
}

bool MainWindow::checkExist(const QString ip, const QString port){
    int i = 0, count = ui->tableWidget->rowCount();
    QString cip, cport;

    while(i < count){
        cip.clear();
        cport.clear();
        cip = ui->tableWidget->item(i, 0)->text();
        //int ii =  ui->tableWidget->takeItem(1, 1)->row();
        cport = ui->tableWidget->item(i, 1)->text();
        if(cip == ip && cport == port)
            return true;
        i++;
    }
    return false;
}

void MainWindow::on_button_del_clicked()
{
    deleteSelectedRows();
    saveConf();
}

void MainWindow::on_button_clear_clicked()
{
    if(ui->tableWidget->rowCount() > 0){
        QMessageBox message("Confirm", "Are you sure to delete all proxys?", QMessageBox::Information, QMessageBox::No, QMessageBox::Yes, NULL);
        if(message.exec() == QMessageBox::Yes){
            int i = ui->tableWidget->rowCount() - 1;
            while(i >= 0){
                ui->tableWidget->removeRow(i);
                -- i;
            }
        }
        saveConf();
    }

}

void MainWindow::deleteSelectedRows(){
    QModelIndexList indexs = ui->tableWidget->selectionModel()->selectedRows();
    //QModelIndexList::const_iterator index;
    if(indexs.size() > 0){
        char info[50];
        sprintf(info, "Are you sure to delete %d proxy(s)?", indexs.size());
        QMessageBox message("Confirm", info , QMessageBox::Information, QMessageBox::No, QMessageBox::Yes, NULL);
        int i = indexs.size() - 1;
        if(message.exec() == QMessageBox::Yes){
            for(;i >= 0; i--){
                ui->tableWidget->removeRow(indexs.at(i).row());
            }
        }
    }else{
        QMessageBox message("Warning", "No row selected.", QMessageBox::Information, NULL, QMessageBox::Yes, NULL);
        message.exec();

    }
}

void MainWindow::verifySelectedRows(){
    enableUI(false);
    QModelIndexList indexs = ui->tableWidget->selectionModel()->selectedRows();
    QModelIndex index;
    foreach(index, indexs){
        createThread(index.row());
    }
    barLabel->setText(tr("current:").append(QString::number(testingNum)).append("  Waiting:").append(QString::number(waitQueue.size())));
}

void MainWindow::copySelectedRows(){
    QModelIndexList indexs = ui->tableWidget->selectionModel()->selectedRows();
    QModelIndex index;
    QString str = "";
    foreach(index, indexs){
        str.append(ui->tableWidget->item(index.row(), 0)->text().append(':').append(ui->tableWidget->item(index.row(), 1)->text()).append('\n'));
        str.append(ui->tableWidget->item(index.row(), 2)->text());
    }
    QApplication::clipboard()->setText(str);
}

void MainWindow::enableUI(bool opt){
    ui->tableWidget->setSortingEnabled(opt);
    ui->button_add->setEnabled(opt);
    ui->button_paste->setEnabled(opt);
    ui->button_clear->setEnabled(opt);
    ui->button_del->setEnabled(opt);
    ui->button_verify->setEnabled(opt);
    ui->button_quit->setEnabled(opt);
    ui->button_import->setEnabled(opt);
    ui->button_download->setEnabled(opt);
    quit->setEnabled(opt);
}

void MainWindow::closeEvent(QCloseEvent *e){
    if(closeFlag){
        if(testingNum > 0){
            QMessageBox message("Alert", "Attention!Threads are still running!", QMessageBox::Warning, NULL, NULL,QMessageBox::Yes,this, NULL);
            message.exec();

            e->ignore();
            return;
        }

        saveConf();
    }else{
        e->ignore();
        this->hide();
    }
}

void MainWindow::loadConf(){
    QString proxys;
    if(readFile(NULL, proxys) == OK){
        ParseToProxys(proxys);
    }
}

void MainWindow::saveConf(){
    int i = 0;
    QString proxys;
    while(i < ui->tableWidget->rowCount()){
        proxys.append(ui->tableWidget->item(i, 0)->text()).append(":").append(ui->tableWidget->item(i, 1)->text());
        if(ui->tableWidget->item(i, 2) != 0 && !ui->tableWidget->item(i, 2)->text().isEmpty()){
            proxys.append("@").append(ui->tableWidget->item(i, 2)->text());
        }
        proxys.append("\n");
        ++i;
    }
    if(writeFile(proxys) != OK){

    }
}

int MainWindow::ParseToProxys(const QString &text){
    char* proxys = (char *)malloc(sizeof(char)*(text.size()+1));
    strncpy(proxys, text.toAscii().data(), text.size());
    proxys[text.size()] = '\0';
    int i = 0, start = 0, end = 0, mid = 0, ext = 0, newRow = 0;
    bool hasMsg = false;
    while(i < text.size()){
        hasMsg = false;
        while(i < text.size()){
            if(proxys[i] >= 48 && proxys[i] <= 57){
                break;
            }
            ++i;
        }
        start = i;
        while(proxys[i] != '\n' && i < text.size()){


            if(proxys[i] == ':' && mid <= start){
               mid = i;
            }
            if(proxys[i] == '@' && ext <= mid){
                hasMsg = true;
                ext = i;
            }
            if(mid > start && ext <= mid && (proxys[i] < 48 || proxys[i] > 57)){
                ext = i;
            }
            ++i;
        }
        if(end < ext){
            end = i;
        }
        if(ext <= mid)
            ext = i;
        if(start < ext && start < mid){
            char serIp[16], serPort[6], serMsg[1024];
            if(mid - start < 16){
                strncpy(serIp, &proxys[start], mid - start);
                serIp[mid - start] = '\0';
            }else{
                continue;
            }
            if(ext - 1 - mid < 6){
                strncpy(serPort, &proxys[mid + 1], ext - 1 - mid);
                serPort[ext -1 - mid] = '\0';
                if(end > ext && hasMsg){
                    int msgLen = (end - ext -1 < 1024 ? end - ext -1 : 1024);
                    strncpy(serMsg, &proxys[ext + 1], msgLen);
                    serMsg[msgLen] = '\0';
                }
            }else{
                continue;
            }
            QString qIp = serIp;
            QString qPort = serPort;
            QString qMsg = serMsg;
            int id;
            if((id = addLine(qIp, qPort)) != ERROR){
                if(end > ext + 1 && hasMsg){
                    handelMsg(id, qMsg);
                }else{
                    handelMsg(id, "Not verified.");
                }
            }
            ++newRow;
            ++ i;
            start = i;
        }
    }
    free(proxys);
    proxys = NULL;
    return newRow;
}

void MainWindow::showTray(){
        //初始化托盘控件并组装**************************************************************
        trayIcon = new QSystemTrayIcon(QIcon(":new/icon/proxy.png"), this);
        menu = new QMenu(this);
        restore = new QAction(tr("Restore"), this);
        mini = new QAction(tr("Mini"), this);
        quit = new QAction(tr("Quit"), this);
        menu->addAction(restore);
        menu->addAction(mini);
        menu->addAction(quit);
        trayIcon->setContextMenu(menu);
        connect(restore,SIGNAL(triggered()),this,SLOT(restoreWindow()));
        connect(mini,SIGNAL(triggered()),this,SLOT(miniWindow()));
        connect(quit,SIGNAL(triggered()),this,SLOT(on_button_quit_clicked()));
        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(handleTray(QSystemTrayIcon::ActivationReason)));
        //将托盘显示
        trayIcon->show();
        //初始化托盘控件并组装**************************************************************
}

void MainWindow::miniWindow(){
    this->hide();
}

void MainWindow::restoreWindow(){
    this->show();
}


void MainWindow::handleTray(QSystemTrayIcon::ActivationReason reason){
    if(reason == QSystemTrayIcon::DoubleClick){
        if(this->isHidden()){
            this->show();
        }else{
            this->hide();
        }
    }
}

void MainWindow::createThread(int itCount){
    if(maxThread > testingNum && threadQueue.size() > 0){
        handelMsg(itCount, "Verifying...");
        int threadId = threadQueue.front();
        if(threads[threadId] == NULL){
            threads[threadId] = new proxyTest(threadId, itCount, ui->https->isChecked(), ui->tableWidget->item(itCount, 0)->text(), ui->tableWidget->item(itCount, 1)->text());
            connect(threads[threadId], SIGNAL(sendMessage(int, int, const QString&)), this, SLOT(handleThread(int, int, const QString &)));
        }else{
            threads[threadId]->setProxyArgs(threadId, itCount, ui->https->isChecked(), ui->tableWidget->item(itCount, 0)->text(), ui->tableWidget->item(itCount, 1)->text());
        }
        ++testingNum;
        threadQueue.pop();
        threads[threadId]->start();
        barLabel->setText(tr("current:").append(QString::number(testingNum)).append("  Waiting:").append(QString::number(waitQueue.size())));

    }else{
        waitQueue.push(itCount);
        handelMsg(itCount, "Waiting...");
    }
}

void MainWindow::on_button_import_clicked()
{
    QString proxys;
    QString path = QFileDialog::getOpenFileName(this, tr("Import Proxys"), ".", tr("Text Files(*.txt)"));
    if(path.length() != 0) {
        ui->button_import->setEnabled(false);
        if(readFile(path, proxys) == OK){
            ParseToProxys(proxys);
            ui->button_import->setEnabled(true);
        }
    }
}

void MainWindow::on_button_download_clicked()
{
    Dialog *urlDialog = new Dialog(this);
    if(urlDialog->exec() == 1){
        if(hthread == NULL){
            hthread = new htmlThread(urlDialog->getUrl());
            connect(hthread, SIGNAL(sendHtmlMsg(int, const QString&)), this, SLOT(handleHtmlThread(int, const QString&)));
            hthread->start();
            enableUI(false);
        }
    }
    delete urlDialog;

}

void MainWindow::handleHtmlThread(int status, const QString &html){
    switch(status){
    case OK:
        int proCount;
        proCount = ParseToProxys(html);
        QMessageBox::information(this,"Congratulation!", QString::fromAscii("%1 new proxy(s) were added!").arg(proCount),QMessageBox::Ok, NULL);
        break;
    case ERROR:
        QMessageBox::critical(this,"Connection error!", QString::fromAscii("Connect to website error!"),QMessageBox::Ok, NULL);
        break;
    case URL_ERROR:
        QMessageBox::critical(this,"URL ERROR!", QString::fromAscii("Illegal URL, Please check and retry!"),QMessageBox::Ok, NULL);
        break;
    default:
        break;

    }
    enableUI(true);
    if(hthread != NULL){
        delete hthread;
        hthread = NULL;
    }
}
