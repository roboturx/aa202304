#include "dlg_r.h"
#include <QComboBox>

dlg_R::dlg_R(QObject *parent)
    : QStyledItemDelegate{parent}
{

}
QWidget *dlg_R::createEditor(QWidget *parent,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    // Create the combobox
    QComboBox *cb = new QComboBox(parent);
    cb->addItem("Ok");
    cb->addItem("NO");
    return cb;
}

void dlg_R::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    const QString currentText = cb->currentText();
    const int cbIndex = cb->findText(currentText);
    //if it is valid, adjust the combobox
    if (cbIndex >= 0)
        cb->setCurrentIndex(cbIndex);
}

void dlg_R::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}
