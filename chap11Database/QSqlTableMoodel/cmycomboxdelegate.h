#ifndef CMYCOMBOXDELEGATE_H
#define CMYCOMBOXDELEGATE_H

#include <QStyledItemDelegate>


class CMyComboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

private:
    QStringList m_ItemList;//选择列表
    bool    m_isEdit; //是否可编辑



public:
    CMyComboxDelegate(QObject *parent=0);

    void    setItems(QStringList items, bool isEdit);//初始化设置列表内容，是否可编辑

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // CMYCOMBOXDELEGATE_H
