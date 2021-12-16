#include "cdialogpen.h"
#include "ui_cdialogpen.h"
#include <QColorDialog>

CDialogPen::CDialogPen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogPen)
{
    ui->setupUi(this);
    ui->comboPenStyle->clear();
    ui->comboPenStyle->addItem("NoPen");
    ui->comboPenStyle->addItem("SolidLine");
    ui->comboPenStyle->addItem("DashLine");
    ui->comboPenStyle->addItem("DotLine");
    ui->comboPenStyle->addItem("DashDotLine");
    ui->comboPenStyle->addItem("DashDotDotLine");
    ui->comboPenStyle->addItem("CustomDashLine");
    ui->comboPenStyle->setCurrentIndex(1);

}

CDialogPen::~CDialogPen()
{
    delete ui;
}

void CDialogPen::setPen(QPen pen)
{
    m_pen = pen;
    ui->spinWidth->setValue(m_pen.width());
    int i = static_cast<int>(m_pen.style());
    ui->comboPenStyle->setCurrentIndex(i);
    ui->btnColor->setAutoFillBackground(true);
    QColor color = m_pen.color();
    QString str = QString::asprintf("background-color: rgb(%d,%d,%d)"
                                    ,color.red(),color.green(),color.blue());
    ui->btnColor->setStyleSheet(str);
}

QPen CDialogPen::getPen()
{
    m_pen.setStyle(Qt::PenStyle(ui->comboPenStyle->currentIndex())); //线型
    m_pen.setWidth(ui->spinWidth->value()); //线宽

    QColor  color;
    color=ui->btnColor->palette().color(QPalette::Button);
    m_pen.setColor(color); //颜色
    return  m_pen;
}

QPen CDialogPen::getPen(QPen iniPen, bool &ok)
{
    CDialogPen * dlg = new CDialogPen;
    dlg->setPen(iniPen);
    QPen    pen;
    int ret = dlg->exec();
    if(ret == CDialogPen::Accepted){
        pen = dlg->getPen();
        ok = true;
    }else{
        pen = iniPen;
        ok = false;
    }

    delete dlg;
    return pen;
}

void CDialogPen::on_btnColor_clicked()
{
    QColor color = m_pen.color();
    color = QColorDialog::getColor(color);
    if(color.isValid()){
        QString str = QString::asprintf("background-color: rgb(%d,%d,%d)"
                                        ,color.red(),color.green(),color.blue());
        ui->btnColor->setStyleSheet(str);
    }
}




