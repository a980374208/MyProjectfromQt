#ifndef CDIALOGPEN_H
#define CDIALOGPEN_H

#include <QDialog>
#include <QPen>

namespace Ui {
class CDialogPen;
}

class CDialogPen : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogPen(QWidget *parent = nullptr);
    ~CDialogPen();

    void    setPen(QPen pen); //设置QPen，用于对话框的界面显示
    QPen    getPen(); //获取对话框设置的QPen的属性
    static  QPen    getPen(QPen  iniPen, bool &ok);  //静态函数


private slots:
    void on_btnColor_clicked();

private:
    Ui::CDialogPen *ui;
    QPen  m_pen;
};

#endif // CDIALOGPEN_H
