#include "formdoc.h"
#include "ui_formdoc.h"

FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
}

FormDoc::~FormDoc()
{
    delete ui;
}
