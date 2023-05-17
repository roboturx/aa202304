#include "dlg_hlist.h"
#include <QComboBox>
#include "hsap/hsp_tree_model_xml.h"

dlG_hList::dlG_hList(QObject *parent)
    : QStyledItemDelegate{parent}
{
    
}

QWidget *dlG_hList::createEditor(QWidget *parent,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    qDebug() << "---dlg_hlist::create editor";
    QComboBox *cb_hspList = new QComboBox(parent);

    hsp_Tree_model_XML *modelXML = new hsp_Tree_model_XML;
    QList<HesapItem *> hesapItems;
    modelXML->load("aaa.knm");
    modelXML->save("yedekkk");
    hesapItems = modelXML->getListXML();
    qDebug() << "----------------- size before------" << hesapItems.size();

    for (auto i = hesapItems.begin(), end = hesapItems.end(); i != end; ++i)
        cb_hspList->addItem((*i)->hesapAd());

    qDebug() << "----------------- size after for ------" << hesapItems.size();

    return cb_hspList;
}

void dlG_hList::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb_hspList = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb_hspList);
    const QString currentText = cb_hspList->currentText();
    const int cbIndex = cb_hspList->findText(currentText);
    //if it is valid, adjust the combobox
    if (cbIndex >= 0)
        cb_hspList->setCurrentIndex(cbIndex);
}

void dlG_hList::setModelData(QWidget *editor,
                             QAbstractItemModel *model,
                             const QModelIndex &index) const
{
    QComboBox *cb_hspList = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb_hspList);
    model->setData(index, cb_hspList->currentText(), Qt::EditRole);
}
