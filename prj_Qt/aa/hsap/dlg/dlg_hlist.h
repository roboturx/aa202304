#ifndef DLG_HLIST_H
#define DLG_HLIST_H

#include <QStyledItemDelegate>

class dlG_hList : public QStyledItemDelegate
{
public:
    explicit dlG_hList(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // DLG_HLIST_H
