#include "custom_tablewidget_site.h"
Custom_TableWidget_Site::Custom_TableWidget_Site(QWidget *parent) :
    QTableWidget(parent)
{
    copy = new QAction(QObject::trUtf8("copy"),this);
    del = new QAction(QObject::trUtf8("delete"),this);
    verify = new QAction(QObject::trUtf8("verify"),this);
    menu = new QMenu(this);
    menu->addAction(copy);
    menu->addAction(del);
    menu->addAction(verify);
}

void Custom_TableWidget_Site::contextMenuEvent(QContextMenuEvent *)
{
    if(this->selectedIndexes().size() > 0){
        QCursor cur = this->cursor();
        if(!this->isSortingEnabled()){
//            copy->setEnabled(false);
            del->setEnabled(false);
            verify->setEnabled(false);
        }else{
//            copy->setEnabled(true);
            del->setEnabled(true);
            verify->setEnabled(true);
        }
        menu->exec(cur.pos());
    }
}

Custom_TableWidget_Site::~Custom_TableWidget_Site(){
    delete copy;
    delete del;
    delete verify;
    delete menu;
}
