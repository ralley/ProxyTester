/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 8 13:20:41 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "custom_tablewidget_site.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_12;
    QFrame *frame;
    QLineEdit *ip;
    QLineEdit *port;
    QLabel *portPanel;
    QLabel *ipPanel;
    QPushButton *button_add;
    QPushButton *button_del;
    QPushButton *button_clear;
    QHBoxLayout *horizontalLayout_13;
    Custom_TableWidget_Site *tableWidget;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *button_import;
    QPushButton *button_paste;
    QPushButton *button_download;
    QCheckBox *https;
    QPushButton *button_verify;
    QPushButton *button_quit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(559, 445);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/icon/proxy.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_14 = new QHBoxLayout(centralWidget);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setSizeConstraint(QLayout::SetFixedSize);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 30));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        ip = new QLineEdit(frame);
        ip->setObjectName(QString::fromUtf8("ip"));
        ip->setGeometry(QRect(23, 0, 131, 27));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ip->sizePolicy().hasHeightForWidth());
        ip->setSizePolicy(sizePolicy1);
        port = new QLineEdit(frame);
        port->setObjectName(QString::fromUtf8("port"));
        port->setGeometry(QRect(192, 0, 71, 27));
        sizePolicy1.setHeightForWidth(port->sizePolicy().hasHeightForWidth());
        port->setSizePolicy(sizePolicy1);
        portPanel = new QLabel(frame);
        portPanel->setObjectName(QString::fromUtf8("portPanel"));
        portPanel->setGeometry(QRect(158, 4, 31, 17));
        sizePolicy1.setHeightForWidth(portPanel->sizePolicy().hasHeightForWidth());
        portPanel->setSizePolicy(sizePolicy1);
        ipPanel = new QLabel(frame);
        ipPanel->setObjectName(QString::fromUtf8("ipPanel"));
        ipPanel->setGeometry(QRect(9, 5, 14, 17));
        sizePolicy1.setHeightForWidth(ipPanel->sizePolicy().hasHeightForWidth());
        ipPanel->setSizePolicy(sizePolicy1);
        button_add = new QPushButton(frame);
        button_add->setObjectName(QString::fromUtf8("button_add"));
        button_add->setGeometry(QRect(267, 0, 51, 27));
        sizePolicy1.setHeightForWidth(button_add->sizePolicy().hasHeightForWidth());
        button_add->setSizePolicy(sizePolicy1);
        button_del = new QPushButton(frame);
        button_del->setObjectName(QString::fromUtf8("button_del"));
        button_del->setGeometry(QRect(327, 0, 61, 27));
        button_clear = new QPushButton(frame);
        button_clear->setObjectName(QString::fromUtf8("button_clear"));
        button_clear->setGeometry(QRect(397, 0, 51, 27));

        horizontalLayout_12->addWidget(frame);


        verticalLayout_7->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        tableWidget = new Custom_TableWidget_Site(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);
        tableWidget->horizontalHeader()->setMinimumSectionSize(100);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_13->addWidget(tableWidget);


        verticalLayout_7->addLayout(horizontalLayout_13);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        button_import = new QPushButton(centralWidget);
        button_import->setObjectName(QString::fromUtf8("button_import"));
        sizePolicy1.setHeightForWidth(button_import->sizePolicy().hasHeightForWidth());
        button_import->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(button_import);

        button_paste = new QPushButton(centralWidget);
        button_paste->setObjectName(QString::fromUtf8("button_paste"));
        sizePolicy1.setHeightForWidth(button_paste->sizePolicy().hasHeightForWidth());
        button_paste->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(button_paste);

        button_download = new QPushButton(centralWidget);
        button_download->setObjectName(QString::fromUtf8("button_download"));
        sizePolicy1.setHeightForWidth(button_download->sizePolicy().hasHeightForWidth());
        button_download->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(button_download);

        https = new QCheckBox(centralWidget);
        https->setObjectName(QString::fromUtf8("https"));

        horizontalLayout_11->addWidget(https);

        button_verify = new QPushButton(centralWidget);
        button_verify->setObjectName(QString::fromUtf8("button_verify"));
        sizePolicy1.setHeightForWidth(button_verify->sizePolicy().hasHeightForWidth());
        button_verify->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(button_verify);

        button_quit = new QPushButton(centralWidget);
        button_quit->setObjectName(QString::fromUtf8("button_quit"));
        sizePolicy1.setHeightForWidth(button_quit->sizePolicy().hasHeightForWidth());
        button_quit->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(button_quit);


        verticalLayout_7->addLayout(horizontalLayout_11);


        horizontalLayout_14->addLayout(verticalLayout_7);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proxy Verify", 0, QApplication::UnicodeUTF8));
        ip->setText(QString());
        port->setText(QString());
#ifndef QT_NO_TOOLTIP
        portPanel->setToolTip(QApplication::translate("MainWindow", "0~65535", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        portPanel->setText(QApplication::translate("MainWindow", "Port", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ipPanel->setToolTip(QApplication::translate("MainWindow", "0.0.0.0~255.255.255.255", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ipPanel->setText(QApplication::translate("MainWindow", "IP", 0, QApplication::UnicodeUTF8));
        button_add->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        button_del->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        button_clear->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "IP", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Port", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Message", 0, QApplication::UnicodeUTF8));
        button_import->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        button_paste->setToolTip(QApplication::translate("MainWindow", "Paste from clipboard!\n"
"e.g.:127.0.0.1:8080", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        button_paste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        button_download->setText(QApplication::translate("MainWindow", "dl from URL", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        https->setToolTip(QApplication::translate("MainWindow", "Check https protocol support.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        https->setText(QApplication::translate("MainWindow", "Https", 0, QApplication::UnicodeUTF8));
        button_verify->setText(QApplication::translate("MainWindow", "Verify all", 0, QApplication::UnicodeUTF8));
        button_quit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
