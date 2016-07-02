#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    void accept();
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString getUrl();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
