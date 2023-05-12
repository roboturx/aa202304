#include "dlg_date.h"
#include <QCalendarWidget>

dlg_Date::dlg_Date(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QWidget *dlg_Date::createEditor(QWidget *parent,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    // Create the calendar
    QCalendarWidget *cln = new QCalendarWidget /*(parent)*/;
    cln->setAutoFillBackground(0);
    cln->setLocale(QLocale::system());
    cln->setMinimumSize(300, 200);
    cln->setGeometry(300, 600, 300, 500);

    return cln;
}

void dlg_Date::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCalendarWidget *cln = qobject_cast<QCalendarWidget *>(editor);
    Q_ASSERT(cln);
    // get the index of the text in the combobox that matches
    // the current value of the item
    const QString currentText = cln->selectedDate().toString();
    //const int cbIndex = cb->findText(currentText);
    // if it is valid, adjust the combobox
    //if (cbIndex >= 0)
    // cb->setCurrentIndex(cbIndex);
}

void dlg_Date::setModelData(QWidget *editor,
                            QAbstractItemModel *model,
                            const QModelIndex &index) const
{
    QCalendarWidget *cln = qobject_cast<QCalendarWidget *>(editor);
    Q_ASSERT(cln);
    model->setData(index, cln->selectedDate().toString(), Qt::EditRole);

    //    if (cb->currentText() == "Konum")
    //    {
    //        QModelIndex ind = model->index(index.row(),5);
    //        model->setData(ind, "DBFNAMEEEE", Qt::EditRole);
    //    }
}
