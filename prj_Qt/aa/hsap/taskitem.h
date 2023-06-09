#ifndef HesapItem_HPP
#define HesapItem_HPP
/*
    Copyright (c) 2009-10 Qtrac Ltd. All rights reserved.
*/

#include <QDateTime>
#include <QList>
#include <QPair>
#include <QString>


    // QList::value() returns default constructed value
    // for out of range
    // row
class HesapItem
{
public:
    explicit HesapItem(const QString &hesapAd = QString(),
                       const QString &hesapAcklm = QString(),
                       const bool bool_topluHesap = false,
                       const QString &hesapTuru = QString(),
                       const QString &ustHesap = QString(),
                       const quint64 &hesapKod = 0,
                       const QString &DBFile = QString(),
                       HesapItem *parent = 0);
    ~HesapItem() { qDeleteAll(lo_children); }

    /// XML:002
    /// getters and setters
    /// variables for XML file
    ///


    QString hesapAd() const { return f_ms_hesapAd; }
    void setHesapAd(const QString &hesapAd) { f_ms_hesapAd = hesapAd; }

    QString hesapAcklm() const { return f_ms_hesapAcklm; }
    void setHesapAcklm(const QString &hesapAcklm) { f_ms_hesapAcklm = hesapAcklm; }

    bool isTopluHesap() const
       { return f_mb_topluHesap; }
    void setTopluHesap(bool bool_topluHesap)
        { f_mb_topluHesap = bool_topluHesap; }

    QString hesapTuru() const
        { return f_ms_hesapTuru; }
    void setHesapTuru(const QString &hesapTuru)
        { f_ms_hesapTuru = hesapTuru; }

    QString ustHesap() const
        { return f_ms_ustHesap; }
    void setUstHesap(const QString &ustHesap)
        { f_ms_ustHesap = ustHesap; }

    quint64 hesapKod() const
        { return f_mi_hesapKod; }
    void setHesapKod(const quint64 &hesapKod)
        { f_mi_hesapKod = hesapKod; }

    QString DBFile() const
        { return f_ms_DBFile; }
    void setDBFile(const QString &DBFile)
        { f_ms_DBFile = DBFile; }

    QList<QPair<QDateTime, QDateTime> > dateTimes() const
        { return m_dateTimes; }
    void addDateTime(const QDateTime &start, const QDateTime &end)
        { m_dateTimes << qMakePair(start, end); }
    QString todaysTime() const;
    QString totalTime() const;
    void incrementLastEndTime(int msec);

    HesapItem *parent() const { return o_parent; }
    HesapItem *childAt(int row) const { return lo_children.value(row); }
    int rowOfChild(HesapItem *child) const { return lo_children.indexOf(child); }
    int childCount() const
        { return lo_children.count(); }
    bool hasChildren() const
        { return !lo_children.isEmpty(); }
    QList<HesapItem *> children() const { return lo_children; }

    void insertChild(int row, HesapItem *item)
    {
        item->o_parent = this;
        lo_children.insert(row, item); }
    void addChild(HesapItem *item)
    {
        item->o_parent = this;
        lo_children << item; }
    void swapChildren(int oldRow, int newRow)
        //  qt5      { m_children.swap(oldRow, newRow); }
        { lo_children.swapItemsAt (oldRow, newRow); }
        HesapItem *takeChild(int row);

    private:
        int minutesForTask(bool onlyForToday) const;

        /// XML:001
        /// define
        /// variables for XML file
        ///

        QString f_ms_hesapAd;
        QString f_ms_hesapAcklm;
        bool f_mb_topluHesap;
        QString f_ms_hesapTuru;
        QString f_ms_ustHesap;
        quint64 f_mi_hesapKod;
        QString f_ms_DBFile;
        QList<QPair<QDateTime, QDateTime> > m_dateTimes;

        HesapItem *o_parent;
        QList<HesapItem *> lo_children;
};

#endif // HesapItem_HPP
