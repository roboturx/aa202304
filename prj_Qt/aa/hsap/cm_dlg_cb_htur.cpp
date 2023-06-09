#include "hsap/cm_dlg_cb_htur.h"
//#include "hsap/HesapItem.h"

#include <QComboBox>

cm_dlG_cb_hTur::cm_dlG_cb_hTur(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

cm_dlG_cb_hTur::~cm_dlG_cb_hTur()
{
}


QWidget *cm_dlG_cb_hTur::createEditor(QWidget *parent,
              const QStyleOptionViewItem &option,
              const QModelIndex &index) const
{

    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);
   // const QString row = QString::number (index.row());
    //qDebug() <<option<<index;


    cb->addItem(QString("Konum"));
    cb->setItemData(0,QColor(0xEFC050/*"#EFC050" mimoza*/),Qt::ForegroundRole);
    cb->addItem(QString("Şirket"));
    cb->setItemData(1,QColor(0x45B8AC/*"#45B8AC Turguoise"*/),Qt::ForegroundRole);
    cb->addItem(QString("Şahıs"));
    cb->setItemData(2,QColor(0x98DDDE /*#98DDDE Limped Shell*/),Qt::ForegroundRole);
    cb->addItem(QString("Aktif Hesap"));
    cb->setItemData(3,QColor(0x79C753 /*#79C753 Green Flash*/),Qt::ForegroundRole);
    cb->addItem(QString("Pasif Hesap"));
    cb->setItemData(4,QColor(0xDD4132 /*#DD4132 Fiesta*/),Qt::ForegroundRole);
    cb->addItem(QString("Araç"));
    cb->setItemData(5,QColor(0x92B6D5) /* #92B6D5 Airy Blue */,Qt::ForegroundRole);
    cb->addItem(QString("Malzeme"));
    cb->setItemData(6,QColor(0xB18F6A) /*#B18F6A Iced Coffee */,Qt::ForegroundRole);
    cb->addItem(QString("Gayrimenkul"));
    cb->setItemData(7,QColor(0xD8AE47 /*#D8AE47 Spicy Mustard*/),
                    Qt::ForegroundRole);
    cb->addItem(QString("Menkul"));
    cb->setItemData(8,QColor(0xFAE03C /*#FAE03C Buttercup*/),
                    Qt::ForegroundRole);

    return cb;
}


void cm_dlG_cb_hTur::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    // get the index of the text in the combobox that matches
    // the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);
}


void cm_dlG_cb_hTur::setModelData(QWidget *editor,
                   QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);

    if (cb->currentText() == "Konum")
    {
        QModelIndex ind = model->index(index.row(),5);
        model->setData(ind, "DBFNAMEEEE", Qt::EditRole);
    }

//    model->setData(index,cb->currentData(Qt::ForegroundRole),
//                   Qt::ForegroundRole);
    ///
//    QString x= cb->itemData (index.row (), Qt::ForegroundRole).toString ();

//    model->setData(index, x, Qt::UserRole+1);
//    model->setData(index, x, Qt::ForegroundRole);


//    QModelIndex ind = model->index(index.row(),0);
//    model->setData(ind  , x, Qt::ForegroundRole);

//    qDebug()<< "clsdlgt_combobox set model data cb itemdata "<<
//        cb->itemData (index.row (), Qt::ForegroundRole).toString ();
}

