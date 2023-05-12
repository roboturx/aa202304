#ifndef DLG_DATE_H
#define DLG_DATE_H

#include <QStyledItemDelegate>
#include <QObject>

class dlg_Date : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit dlg_Date(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // DLG_DATE_H
