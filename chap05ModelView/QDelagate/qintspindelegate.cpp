#include "qintspindelegate.h"
#include <QSpinBox>

QIntSpinDelegate::QIntSpinDelegate()
{

}

QWidget *QIntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(1000);
    editor->setFrame(false);

    return editor;
}

void QIntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     int value = index.model()->data(index,Qt::EditRole).toInt();
     QSpinBox * spinBox =  static_cast<QSpinBox*>(editor);
     spinBox->setValue(value);
}

void QIntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox * spinBox =  static_cast<QSpinBox*>(editor);
//    int value = spinBox->value();
    spinBox->interpretText();//保证数据是最新的
    int value = spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

void QIntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
