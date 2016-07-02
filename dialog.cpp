#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getUrl(){
    return ui->urlEdit->text();
}

void Dialog::accept(){
    if(ui->urlEdit->text().length() == 0){
        QMessageBox::information(this,"Error", "URL cannot be blank.");
    }else{
        QDialog::accept();
    }
}
