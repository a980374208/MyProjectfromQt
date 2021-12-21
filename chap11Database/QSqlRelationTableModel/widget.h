#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_actOpenDB_triggered();

private:
    Ui::Widget *ui;
    QSqlDatabase m_Db;
    QSqlRelationalTableModel *m_pTableModel;
    QItemSelectionModel *m_pSelectionModel;
};
#endif // WIDGET_H
