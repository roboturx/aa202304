#include "hsp_tree_model_xml.h"

/// fields :
/// change these for data manipulation
///
/// 001- -  in HesapItem.h - field's variable declarations
/// 002- -  in HesapItem.h - field variables' getters and setters
/// 003- fields, attributes, counts, enum
/// 004- make editable checkable etc.
/// 005- get data
/// 006- header data
/// 007- set data
/// 008- insert new record
/// 009- announce when data column changed
/// 010- read datas from XML file
/// 011- save XML file
/// 012- write datas to XML file
///

/// XML:003
/// fields, attributes, counts, enum
/// variables for XML file
///
namespace {

const QString TaskTag("ACCOUNT");
const QString NeZamanTag("WORKED");
const QString IlkAttribute("FROM: ");
const QString SonAttribute("TO: ");

/// fields for XML file
const QString HesapAdAttribute("AccNAME");
const QString AcklmAttribute("AccNOTE");
const QString TopluHesapAttribute("AccIsBATCH");
const QString HesapTuruAttribute("AccTYPE");
const QString UstHesapAttribute("AccsPARENT");
const QString HesapKodAttribute("AccCODE");
const QString DBFileAttribute("AccDBFile");

/// fields' count
const int ColumnCount = 7;
enum Column { HesapAd, HesapAciklama, Topluhesap, HesapTuru, UstHesap, HesapKod, DBFile };

const int MaxCompression = 9;
const QString MimeType = "application/vnd.qtrac.xml.task.z";
} // namespace

/// XML:004
/// make editable, checkable, drag-dropable
/// variables for XML file
///
Qt::ItemFlags hsp_Tree_model_XML::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);

    if (index.isValid()) {
        if (index.column() == HesapAd || index.column() == HesapAciklama
            || index.column() == HesapTuru || index.column() == DBFile
            || index.column() == UstHesap) {
            theFlags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable
                        | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
        }

        if (index.column() == Topluhesap) {
            theFlags |= Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled
                        | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
        }
    }

    return theFlags;
}

/// XML:005
/// data
/// variables for XML file
///
QVariant hsp_Tree_model_XML::data(const QModelIndex &index, int role) const
{
    // qDebug()<<"::Xmdl data";
    if (!rootItem || !index.isValid() || index.column() < 0 || index.column() >= ColumnCount)
        return QVariant();

    if (HesapItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (index.column()) {
            case HesapAd:
                return item->hesapAd();
            case HesapAciklama:
                return item->hesapAcklm();
            case Topluhesap:
                return item->isTopluHesap();
            case HesapTuru:
                return item->hesapTuru();
            case UstHesap:
                return item->ustHesap();
            case HesapKod:
                return item->hesapKod();
            case DBFile:
                return item->DBFile();
            default:
                Q_ASSERT(false);
            }
        }
        if (role == Qt::CheckStateRole && index.column() == Topluhesap) {
            return static_cast<int>(item->isTopluHesap() ? Qt::Checked : Qt::Unchecked);
        }
        if (role == Qt::TextAlignmentRole) {
            if (index.column() == DBFile) {
                return static_cast<int>(Qt::AlignVCenter | Qt::AlignCenter);
            }
            if (index.column() == HesapAd || index.column() == HesapAciklama
                || index.column() == HesapTuru || index.column() == UstHesap) {
                return static_cast<int>(Qt::AlignVCenter | Qt::AlignLeft);
            }
            return static_cast<int>(Qt::AlignVCenter | Qt::AlignCenter);
        }
        if (role == Qt::DecorationRole) {
            if (index.column() == 0) {
                if (item->hesapTuru() == "Şirket") {
                    return QIcon(":/rsm/icon/file.png");
                }
                if (item->hesapTuru() == "Konum") {
                    return QIcon(":/rsm/icon/globe.png");
                }

                if (item->hesapTuru() == "Şahıs") {
                    return QIcon(":/rsm/person.jpeg");
                }
                if (item->hesapTuru() == "Aktif Hesap") {
                    return QIcon(":/rsm/ico/plus-minus-green.ico");
                }
                if (item->hesapTuru() == "Pasif Hesap") {
                    return QIcon(":/rsm/ico/plus-minus-red.ico");
                }
                if (item->hesapTuru() == "Araç") {
                    return QIcon(":/rsm/ex.ico");
                }
                if (item->hesapTuru() == "Malzeme") {
                    return QIcon(":/rsm/plt.png");
                }
                if (item->hesapTuru() == "Gayrimenkul") {
                    return QIcon(":/rsm/ico/x.png");
                }
                if (item->hesapTuru() == "Menkul") {
                    return QIcon(":/rsm/icon/candlestick.png");
                }
            }
        }

        if (role == Qt::DecorationRole && index.column() == HesapKod && timedItem
            && item == timedItem && !m_icon.isNull())
            return m_icon;

        if (role == Qt::FontRole) {
            QFont font;
            font.setPointSize(14);
            return font;
        }

        if (role == Qt::ForegroundRole) {
            if (index.column() == 0 || index.column() == 3) {
                if (item->hesapTuru() == "Konum") {
                    return QVariant(QColor("#DFCFBE"));
                }
                if (item->hesapTuru() == "Şirket") {
                    return QVariant(QColor("#EFC050"));
                }
                if (item->hesapTuru() == "Şahıs") {
                    return QVariant(QColor("#FAE03C"));
                }
                if (item->hesapTuru() == "Aktif Hesap") {
                    return QVariant(QColor("#7FCDCD"));
                }
                if (item->hesapTuru() == "Pasif Hesap") {
                    return QVariant(QColor("#E15D44"));
                }
                if (item->hesapTuru() == "Araç") {
                    return QVariant(QColor("#88B04B"));
                }
                if (item->hesapTuru() == "Emtia") {
                    return QVariant(QColor("#FF6F61"));
                }
                if (item->hesapTuru() == "GayriMenkul") {
                    return QVariant(QColor("#92B6D5"));
                }
                if (item->hesapTuru() == "Menkul") {
                    return QVariant(QColor("#D8AE47"));
                }
                //                    if (item->hesapTuru() == "" )
                //                    {
                //                        return QVariant( QColor(  ) );
                //                    }
                //                    if (item->hesapTuru() == "" )
                //                    {
                //                        return QVariant( QColor(  ) );
                //                    }
                //                    if (item->hesapTuru() == "" )
                //                    {
                //                        return QVariant( QColor(  ) );
                //                    }
            }
            return QVariant(QColor(Qt::cyan));
        }
    }
    return QVariant();
}

/// XML:006
/// headers
/// variables for XML file
///
QVariant hsp_Tree_model_XML::headerData(int section, Qt::Orientation orientation, int role) const
{
    // qDebug()<<"::Xmdl headerdata";
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == HesapAd)
            return tr("Hesap Adı");
        else if (section == HesapAciklama)
            return tr("Açıklama");
        else if (section == Topluhesap)
            return tr("Toplu Hesap");
        else if (section == HesapTuru)
            return tr("Hesap Türü");
        else if (section == UstHesap)
            return tr("Üst Hesap");
        else if (section == HesapKod)
            return tr("Hesap Kodu");
        else if (section == DBFile)
            return tr("DBF");
    }
    return QVariant();
}

/// XML:007
/// setdata
/// variables for XML file
///
bool hsp_Tree_model_XML::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //    qDebug()<<"::Xmdl setdata";
    if (!index.isValid()) //|| index.column() != HesapAd)
    {
        return false;
    }

    if (HesapItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole) {
            if (index.column() == HesapAd) {
                if (updateXMLHesapAd(item, value)) {
                    /// hesapdetay deki tüm transfer hesap adları
                    /// yeni hale geldi
                    item->setHesapAd(value.toString());
                };
            }
            if (index.column() == HesapAciklama) {
                item->setHesapAcklm(value.toString());
            }
            if (index.column() == HesapTuru) {
                item->setHesapTuru(value.toString());
            }
            if (index.column() == UstHesap) {
                item->setUstHesap(value.toString());
            }
            if (index.column() == DBFile) {
                item->setDBFile(value.toString());
            }
        }

        else if (role == Qt::CheckStateRole) {
            if (index.column() == Topluhesap) {
                item->setTopluHesap(value.toBool());
            }
        } else {
            return false;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool hsp_Tree_model_XML::updateXMLHesapAd(HesapItem *item, QVariant &value)
{
    qDebug() << "::Xmdl update XML hesap ad -----------";
    QSqlQuery query;
    QString str;
    str = "REPLACE ALL f_hspdty_transfer WITH " + value.toString()
          + " FOR f_hspdty_transfer=" + item->hesapAd();
    if (!query.exec(str))
        return false;
    return true;
}

/// XML:008
/// insertrows
/// variables for XML file
///
bool hsp_Tree_model_XML::insertRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "::Xmdl insertrows";

    if (!rootItem) {
        rootItem = new HesapItem("T", "T", 0, "T", "T", 0);
        *pi_max_Hesap_ID = rootItem->hesapKod();
    }

    HesapItem *parentItem = parent.isValid() ? itemForIndex(parent) : rootItem;
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        // hesaba en yüksek id yi ver

        ++*pi_max_Hesap_ID;

        // yeni bir hesap oluştur
        HesapItem *item = new HesapItem("", "", 0, "", "", *pi_max_Hesap_ID + 10000);

        parentItem->insertChild(row, item);
    }
    //    qDebug() << "hsp_Tree_model_XML.cpp-::insertRows(*****************"
    //                "end***************************";
    endInsertRows();
    return true;
}

/// XML:009
/// changing
/// variables for XML file
///
void hsp_Tree_model_XML::announceItemChanged(HesapItem *item)
{
    qDebug() << "::Xmdl announceitemchanged";

    if (item == rootItem)
        return;
    HesapItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);

    QModelIndex startIndex = createIndex(row, static_cast<int>(HesapAd), item);
    QModelIndex endIndex = createIndex(row, static_cast<int>(UstHesap), item);

    emit dataChanged(startIndex, endIndex);

    // Update the parent & parent's parent etc too
    announceItemChanged(parent);
}

/// XML:010
/// read from XML
/// variables for XML file
///
void hsp_Tree_model_XML::readTasks(QXmlStreamReader *reader, HesapItem *task)
{
    while (!reader->atEnd()) {
        reader->readNext();
        /// İLK kayıt mı
        if (reader->isStartElement()) {
            /// TASK lar
            if (reader->name() == TaskTag) {
                const quint64 hesapKod = reader->attributes().value(HesapKodAttribute).toULongLong();

                if (hesapKod > *pi_max_Hesap_ID) {
                    // en büyük hesapkod u bul
                    *pi_max_Hesap_ID = hesapKod;
                }

                QString hesapAd = reader->attributes().value(HesapAdAttribute).toString();

                const QString hesapAcklm = reader->attributes().value(AcklmAttribute).toString();
                bool topluHesap = reader->attributes().value(TopluHesapAttribute).toInt();
                const QString hesapTuru = reader->attributes().value(HesapTuruAttribute).toString();
                const QString ustHesap = reader->attributes().value(UstHesapAttribute).toString();
                const QString DBFile = reader->attributes().value(DBFileAttribute).toString();

                task = new HesapItem(hesapAd,
                                     hesapAcklm,
                                     topluHesap,
                                     hesapTuru,
                                     ustHesap,
                                     hesapKod,
                                     DBFile,
                                     task);

                //// item ı listeye ekle
                ///  hspdetay transfer hesaplarda kullanılacak liste
                addListXML(task);
            }
            // NZAMAN lar
            else if (reader->name() == NeZamanTag) {
                const QDateTime start
                    = QDateTime::fromString(reader->attributes().value(IlkAttribute).toString(),
                                            Qt::ISODate);
                const QDateTime end
                    = QDateTime::fromString(reader->attributes().value(SonAttribute).toString(),
                                            Qt::ISODate);
                Q_ASSERT(task);
                task->addDateTime(start, end);
            }
        }
        // YOKSA son kayıt MI
        else if (reader->isEndElement()) {
            if (reader->name() == TaskTag) {
                Q_ASSERT(task);
                task = task->parent();
                Q_ASSERT(task);
            }
        }
    } // while end
}

/// XML:011
/// save XML file
/// variables for XML file
///
void hsp_Tree_model_XML::save(const QString &filename)
{
    qDebug() << "::Xmdl save";
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw AQP::Error(tr("dosya adı belirtilmedi"));
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw AQP::Error(file.errorString());
    qDebug() << "::Xmdl save filename --->" << filename;

    Q_ASSERT(rootItem);
    qDebug() << "::Xmdl::Save -> rootitem      :";
    qDebug() << "::Xmdl::Save -> rootitem.kod  :" << rootItem->hesapKod();
    qDebug() << "::Xmdl::Save -> rootitem.Ad   :" << rootItem->hesapAd();

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("KONUM");
    writer.writeAttribute("Sürüm", "2.0");
    writeTaskAndChildren(&writer, rootItem);
    writer.writeEndElement(); // KONUM
    writer.writeEndDocument();
}

/// XML:012
/// write to XML file
/// variables for XML file
///
void hsp_Tree_model_XML::writeTaskAndChildren(QXmlStreamWriter *writer, HesapItem *task) const
{
    qDebug() << "::Xmdl writetaskandchildren";
    if (task != rootItem) {
        writer->writeStartElement(TaskTag);
        qDebug() << "::Xmdl writetaskandchildren 2";
        writer->writeAttribute(HesapAdAttribute, task->hesapAd());
        writer->writeAttribute(AcklmAttribute, task->hesapAcklm());
        writer->writeAttribute(TopluHesapAttribute, task->isTopluHesap() ? "1" : "0");
        writer->writeAttribute(HesapTuruAttribute, task->hesapTuru());
        writer->writeAttribute(UstHesapAttribute, task->ustHesap());
        writer->writeAttribute(HesapKodAttribute, QString::number(task->hesapKod()));
        writer->writeAttribute(DBFileAttribute, task->DBFile());

        qDebug() << "::Xmdl writetaskandchildren 3";
        QListIterator<QPair<QDateTime, QDateTime> > i(task->dateTimes());
        while (i.hasNext()) {
            const QPair<QDateTime, QDateTime> &dateTime = i.next();
            writer->writeStartElement(NeZamanTag);
            writer->writeAttribute(IlkAttribute, dateTime.first.toString(Qt::ISODate));
            writer->writeAttribute(SonAttribute, dateTime.second.toString(Qt::ISODate));
            writer->writeEndElement(); // WHEN
        }
    }
    qDebug() << "::Xmdl writetaskandchildren 4";
    foreach (HesapItem *child, task->children()) {
        writeTaskAndChildren(writer, child);
    }
    qDebug() << "::Xmdl writetaskandchildren 5";
    if (task != rootItem)
        writer->writeEndElement(); // TASK
    qDebug() << "::Xmdl writetaskandchildren son";
}

/////////////////////////////////////////////////////////////////
///
///
///
///
/////////////////////////////////////////////////////////////////

int hsp_Tree_model_XML::rowCount(const QModelIndex &parent) const
{
    // qDebug()<<"::Xmdl rowcount";
    if (parent.isValid() && parent.column() != 0)
        return 0;
    HesapItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int hsp_Tree_model_XML::columnCount(const QModelIndex &parent) const
{
    // qDebug()<<"::Xmdl columncount";
    return parent.isValid() && parent.column() != 0 ? 0 : ColumnCount;
}

QModelIndex hsp_Tree_model_XML::index(int row, int column, const QModelIndex &parent) const
{
    //  qDebug()<<"::Xmdl index";
    if (!rootItem || row < 0 || column < 0 || column >= ColumnCount
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    HesapItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (HesapItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}

HesapItem *hsp_Tree_model_XML::itemForIndex(const QModelIndex &index) const
{
    // qDebug()<<"::Xmdl itemforindex";
    if (index.isValid()) {
        if (HesapItem *item = static_cast<HesapItem *>(index.internalPointer()))
            return item;
    }
    return rootItem;
}

QModelIndex hsp_Tree_model_XML::parent(const QModelIndex &index) const
{
    //qDebug()<<"::Xmdl parent ";
    if (!index.isValid())
        return QModelIndex();
    if (HesapItem *childItem = itemForIndex(index)) {
        if (HesapItem *parentItem = childItem->parent()) {
            if (parentItem == rootItem)
                return QModelIndex();
            if (HesapItem *grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

bool hsp_Tree_model_XML::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "::Xmdl removeerows";
    if (!rootItem)
        return false;
    HesapItem *item = parent.isValid() ? itemForIndex(parent) : rootItem;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        delete item->takeChild(row);
    endRemoveRows();
    return true;
}

QStringList hsp_Tree_model_XML::mimeTypes() const
{
    qDebug() << "::Xmdl mimetypes";
    return QStringList() << MimeType;
}

QMimeData *hsp_Tree_model_XML::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "::Xmdl mimedata";
    Q_ASSERT(indexes.count());
    if (indexes.count() != 1)
        return 0;
    if (HesapItem *item = itemForIndex(indexes.at(0))) {
        QMimeData *mimeData = new QMimeData;
        QByteArray xmlData;
        QXmlStreamWriter writer(&xmlData);
        writeTaskAndChildren(&writer, item);
        mimeData->setData(MimeType, qCompress(xmlData, MaxCompression));
        return mimeData;
    }
    return 0;
}

bool hsp_Tree_model_XML::dropMimeData(const QMimeData *mimeData,
                                      Qt::DropAction action,
                                      int row,
                                      int column,
                                      const QModelIndex &parent)
{
    qDebug() << "::Xmdl dropmimedat";
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !mimeData || !mimeData->hasFormat(MimeType))
        return false;
    if (HesapItem *item = itemForIndex(parent)) {
        emit stopTiming();
        QByteArray xmlData = qUncompress(mimeData->data(MimeType));
        QXmlStreamReader reader(xmlData);
        if (row == -1)
            row = parent.isValid() ? parent.row() : rootItem->childCount();
        beginInsertRows(parent, row, row);
        readTasks(&reader, item);
        endInsertRows();
        return true;
    }
    return false;
}

bool hsp_Tree_model_XML::isChecked(const QModelIndex &index) const
{
    qDebug() << "::Xmdl ischecked";
    if (!index.isValid())
        return false;
    return data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
}

QModelIndex hsp_Tree_model_XML::moveUp(const QModelIndex &index)
{
    qDebug() << "::Xmdl moveup";
    if (!index.isValid() || index.row() <= 0)
        return index;
    HesapItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HesapItem *parent = item->parent();
    Q_ASSERT(parent);
    return moveItem(parent, index.row(), index.row() - 1);
}

QModelIndex hsp_Tree_model_XML::moveItem(HesapItem *parent, int oldRow, int newRow)
{
    qDebug() << "::Xmdl moveitem";
    Q_ASSERT(0 <= oldRow && oldRow < parent->childCount() && 0 <= newRow
             && newRow < parent->childCount());
    parent->swapChildren(oldRow, newRow);
    QModelIndex oldIndex = createIndex(oldRow, 0, parent->childAt(oldRow));
    QModelIndex newIndex = createIndex(newRow, 0, parent->childAt(newRow));
    emit dataChanged(oldIndex, newIndex);
    return newIndex;
}
/////////////////////////////////////////////////////////////////
/// \brief hsp_Tree_model_XML::hTurColor
///
/// hc_main - 445 signal i,le yollanan qcolor
/// hesap turu rengi olarak kullanılacak
///
void hsp_Tree_model_XML::hTurColor(QColor color)
{
    qDebug() << "------------htur siggggggnaaaaaaaaaaaal    " << color;
}

QList<HesapItem *> hsp_Tree_model_XML::getListXML()
{
    return listXML;
}

void hsp_Tree_model_XML::addListXML(HesapItem *newXMLItem)
{
    qDebug() << "listeye eklenen yeni hesap kod " << newXMLItem->hesapKod();
    if (newXMLItem->hesapTuru() == "Aktif Hesap" || newXMLItem->hesapTuru() == "Pasif Hesap") {
        listXML << newXMLItem;
    }
    qDebug() << "***************** size *********************** " << listXML.size();

    //   foreach (const HesapItem *it, newXMLItem)
    // {
    //   qDebug() << it->hesapKod();
    //}
}

QModelIndex hsp_Tree_model_XML::moveDown(const QModelIndex &index)
{
    qDebug() << "::Xmdl moveedown";
    if (!index.isValid())
        return index;
    HesapItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HesapItem *parent = item->parent();
    int newRow = index.row() + 1;
    if (!parent || parent->childCount() <= newRow)
        return index;
    return moveItem(parent, index.row(), newRow);
}

QModelIndex hsp_Tree_model_XML::cut(const QModelIndex &index)
{
    qDebug() << "::Xmdl cut";
    if (!index.isValid())
        return index;
    delete cutItem;
    cutItem = itemForIndex(index);
    Q_ASSERT(cutItem);
    HesapItem *parent = cutItem->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(cutItem);
    Q_ASSERT(row == index.row());
    beginRemoveRows(index.parent(), row, row);
    HesapItem *child = parent->takeChild(row);
    endRemoveRows();
    Q_ASSERT(child == cutItem);
    child = 0; // Silence compiler unused variable warning

    if (row > 0) {
        --row;
        return createIndex(row, 0, parent->childAt(row));
    }
    if (parent != rootItem) {
        HesapItem *grandParent = parent->parent();
        Q_ASSERT(grandParent);
        return createIndex(grandParent->rowOfChild(parent), 0, parent);
    }
    return QModelIndex();
}

QModelIndex hsp_Tree_model_XML::paste(const QModelIndex &index)
{
    qDebug() << "::Xmdl paste";
    if (!index.isValid() || !cutItem)
        return index;
    HesapItem *sibling = itemForIndex(index);
    Q_ASSERT(sibling);
    HesapItem *parent = sibling->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(sibling) + 1;
    beginInsertRows(index.parent(), row, row);
    parent->insertChild(row, cutItem);
    HesapItem *child = cutItem;
    cutItem = 0;
    endInsertRows();
    return createIndex(row, 0, child);
}

QModelIndex hsp_Tree_model_XML::promote(const QModelIndex &index)
{
    qDebug() << "::Xmdl prğmğte";
    if (!index.isValid())
        return index;
    HesapItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HesapItem *parent = item->parent();
    Q_ASSERT(parent);
    if (parent == rootItem)
        return index; // Already a top-level item

    int row = parent->rowOfChild(item);
    HesapItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    HesapItem *grandParent = parent->parent();
    Q_ASSERT(grandParent);
    row = grandParent->rowOfChild(parent) + 1;
    grandParent->insertChild(row, child);
    QModelIndex newIndex = createIndex(row, 0, child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}

QModelIndex hsp_Tree_model_XML::demote(const QModelIndex &index)
{
    qDebug() << "::Xmdl demote";
    if (!index.isValid())
        return index;
    HesapItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HesapItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);
    if (row == 0)
        return index; // No preceding sibling to move this under
    HesapItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    HesapItem *sibling = parent->childAt(row - 1);
    Q_ASSERT(sibling);
    sibling->addChild(child);
    QModelIndex newIndex = createIndex(sibling->childCount() - 1, 0, child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}

void hsp_Tree_model_XML::setTimedItem(const QModelIndex &index)
{
    qDebug() << "::Xmdl settimeditem";
    clearTimedItem();
    timedItem = itemForIndex(index);
    Q_ASSERT(timedItem);
    announceItemChanged(timedItem);
}

void hsp_Tree_model_XML::clearTimedItem()
{
    qDebug() << "::Xmdl cleartimeditem";
    if (timedItem) {
        HesapItem *item = timedItem;
        timedItem = 0;
        announceItemChanged(item);
    }
}

bool hsp_Tree_model_XML::isTimedItem(const QModelIndex &index)
{
    qDebug() << "::Xmdl istimeedata";
    return timedItem && itemForIndex(index) == timedItem;
}

void hsp_Tree_model_XML::addDateTimeToTimedItem(const QDateTime &start, const QDateTime &end)
{
    qDebug() << "::Xmdl adddatetime";
    if (timedItem) {
        timedItem->addDateTime(start, end);
        announceItemChanged(timedItem);
    }
}

void hsp_Tree_model_XML::setIconForTimedItem(const QIcon &icon)
{
    qDebug() << "::Xmdl seticonfor ";
    m_icon = icon;
    if (timedItem)
        announceItemChanged(timedItem);
}

void hsp_Tree_model_XML::incrementEndTimeForTimedItem(int msec)
{
    qDebug() << "::Xmdl incrementendtime";
    if (timedItem) {
        timedItem->incrementLastEndTime(msec);
        announceItemChanged(timedItem);
    }
}

void hsp_Tree_model_XML::clear()
{
    qDebug() << "::Xmdl clear";
    delete rootItem;
    rootItem = 0;
    delete cutItem;
    cutItem = 0;
    timedItem = 0;
    //reset();         //deleted for Qt5
    beginResetModel(); //added for Qt5
    endResetModel();   //added for Qt5
}

void hsp_Tree_model_XML::load(const QString &filename)
{
    qDebug() << "::Xmdl load";

    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw AQP::Error(tr("Dosya ismi belirtilmemiş"));
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        throw AQP::Error(file.errorString());

    clear();
    qDebug() << "hsp_Tree_model_XML::load     new root item";
    rootItem = new HesapItem("ROO", "ROO", 0, "ROO", "ROOT", 0);

    QXmlStreamReader reader(&file);
    readTasks(&reader, rootItem);
    if (reader.hasError())
        throw AQP::Error(reader.errorString());
    beginResetModel();
    endResetModel();
}

QStringList hsp_Tree_model_XML::pathForIndex(const QModelIndex &index) const
{
    //qDebug()<<"::Xmdl pathforindex ";
    QStringList path;
    QModelIndex thisIndex = index;
    while (thisIndex.isValid()) {
        path.prepend(data(thisIndex).toString());
        thisIndex = thisIndex.parent();
    }
    return path;
}

QModelIndex hsp_Tree_model_XML::indexForPath(const QStringList &path) const
{
    //qDebug()<<"::Xmdl indexforpath";
    return indexForPath(QModelIndex(), path);
}

QModelIndex hsp_Tree_model_XML::indexForPath(const QModelIndex &parent,
                                             const QStringList &path) const
{
    //qDebug()<<"::Xmdl indexforpath xxx";
    if (path.isEmpty())
        return QModelIndex();
    for (int row = 0; row < rowCount(parent); ++row) {
        QModelIndex thisIndex = index(row, 0, parent);
        if (data(thisIndex).toString() == path.at(0)) {
            if (path.count() == 1)
                return thisIndex;
            thisIndex = indexForPath(thisIndex, path.mid(1));
            if (thisIndex.isValid())
                return thisIndex;
        }
    }
    return QModelIndex();
}
