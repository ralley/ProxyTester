#ifndef CUSTOM_TABLEWIDGET_SITE_H
#define CUSTOM_TABLEWIDGET_SITE_H
#include <QTableWidget>
#include <QMenu>
class Custom_TableWidget_Site : public QTableWidget
{
    Q_OBJECT

public:
    explicit Custom_TableWidget_Site(QWidget *parent = 0);
    ~Custom_TableWidget_Site();
    QAction *copy;
    QAction *del;
    QAction *verify;
    QMenu *menu;
//    void sortByColumn(int column, Qt::SortOrder order);
//    void sortByValue(int column);


private:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // CUSTOM_TABLEWIDGET_SITE_H
