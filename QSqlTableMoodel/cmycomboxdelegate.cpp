#include "cmycomboxdelegate.h"
#include <QComboBox>

CMyComboxDelegate::CMyComboxDelegate(QObject * parent): QStyledItemDelegate(parent)
{

}

void CMyComboxDelegate::setItems(QStringList items, bool isEdit)
{
    m_ItemList = items;
    m_isEdit = isEdit;
}

QWidget *CMyComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QComboBox *editor = new QComboBox(parent);
    for(int i = 0;i<m_ItemList.count();i++){
        editor->addItem(m_ItemList.at(i));
    }
    editor->setEditable(m_isEdit);
    return editor;
}

void CMyComboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index,Qt::EditRole).toString();
    QComboBox* comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);
}

void CMyComboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*> (editor);
    QString str = comboBox->currentText();
    model->setData(index,str,Qt::EditRole);
}

void CMyComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
