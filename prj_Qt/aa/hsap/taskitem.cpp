
#include "hsap/HesapItem.h"

HesapItem::HesapItem(const QString &hesapAd,
                     const QString &hesapAcklm,
                     const bool topluHesap,
                     const QString &hesapTuru,
                     const QString &ustHesap,
                     const quint64 &hesapKod,
                     const QString &DBFile,
                     HesapItem *parent)
    : f_ms_hesapAd(hesapAd)
    , f_ms_hesapAcklm(hesapAcklm)
    , f_mb_topluHesap(topluHesap)
    , f_ms_hesapTuru(hesapTuru)
    , f_ms_ustHesap(ustHesap)
    , f_mi_hesapKod(hesapKod)
    , f_ms_DBFile(DBFile)
    , o_parent(parent)
{
  //  qDebug()<<"    ::Xitem constrctr";
    if (parent )
        o_parent->addChild(this);
}

QString HesapItem::todaysTime() const
{
   // qDebug()<<"    ::Xitem todaystime";
    int minutes = minutesForTask(true);
    return QString("%1:%2").arg(minutes / 60)
                           .arg(minutes % 60, 2, 10, QChar('0'));
}

QString HesapItem::totalTime() const
{
   // qDebug()<<"    ::Xitem totaltime";
    int minutes = minutesForTask(false);
    return QString("%1:%2").arg(minutes / 60)
                           .arg(minutes % 60, 2, 10, QChar('0'));
}

int HesapItem::minutesForTask(bool onlyForToday) const
{
   // qDebug()<<"    ::Xitem minutesfortask";
    int minutes = 0;
    QListIterator<QPair<QDateTime, QDateTime> > i(m_dateTimes);
    while (i.hasNext()) {
        const QPair<QDateTime, QDateTime> &dateTime = i.next();
        if (onlyForToday &&
            dateTime.first.date() != QDate::currentDate())
            continue;
        minutes += (dateTime.first.secsTo(dateTime.second) / 60);
    }
    foreach (HesapItem *child, lo_children)
        minutes += child->minutesForTask(onlyForToday);
    return minutes;
}

void HesapItem::incrementLastEndTime(int msec)
{
   // qDebug()<<"    ::Xitem icrementlastendtime";
    QDateTime &endTime = m_dateTimes.last().second;
    endTime.setTime(endTime.time().addMSecs(msec));
}

HesapItem *HesapItem::takeChild(int row)
{
   // qDebug()<<"    ::Xitem takeechild";
    HesapItem *item = lo_children.takeAt(row);
    Q_ASSERT(item);
    item->o_parent = 0;
    return item;
}
