#ifndef DLG_R_H
#define DLG_R_H

#include <QStyledItemDelegate>

class dlg_R : public QStyledItemDelegate
{
public:
    explicit dlg_R(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // DLG_R_H
