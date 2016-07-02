#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <pthread.h>
#include <QObject>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <config.h>
#include <QtCore>
#include <QSystemTrayIcon>
#include <queue>
#include <QFileDialog>
#include <dialog.h>
#include "socketConn.h"
#include <getWebPage.h>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int testingNum;
    const static int maxThread = 10;
//    QMutex mutex;

    QAction* restore;
    QAction* mini;
    QAction* quit;
    QMenu* menu;
    QSystemTrayIcon* trayIcon;
    QLabel *barLabel;
    proxyTest *threads[maxThread];
    htmlThread *hthread;
    bool closeFlag;
    std::queue<int> waitQueue;
    std::queue<int> threadQueue;


    void init();
    void handelMsg(int id, const QString &str);
    int addLine(const QString ip, const QString port);
    bool checkExist(const QString ip, const QString port);
    void enableUI(bool opt);
    int ParseToProxys(const QString &text);
    void saveConf();
    void loadConf();
    void showTray();
    void createThread(int itCount);
protected:
    void closeEvent(QCloseEvent *e);
private slots:
    void on_button_download_clicked();
    void on_button_import_clicked();
    void on_button_add_clicked();
    void on_button_del_clicked();
    void on_button_paste_clicked();
    void on_button_clear_clicked();
    void on_button_verify_clicked();
    void on_button_quit_clicked();
    void handleThread(int threadId, int id, const QString &str);
    void deleteSelectedRows();
    void copySelectedRows();
    void verifySelectedRows();
    void miniWindow();
    void restoreWindow();
    void handleTray(QSystemTrayIcon::ActivationReason reason);
    void handleHtmlThread(int status, const QString &html);
};

#endif // MAINWINDOW_H
