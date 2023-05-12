#ifndef hsp_cb_Turu_H
#define hsp_cb_Turu_H

#include "libs/globals.h"

class hsp_cb_Turu
{
public:
    hsp_cb_Turu();

public:
    explicit hsp_cb_Turu(const QString &hs_Tur = QString(),
                         const QColor &hs_Color = QColor(),
                         const QIcon &hs_icon = QIcon(),
                         const QString &hs_01 = QString(),
                         const QString &hs_02 = QString(),
                         const quint64 &hs_T_Kod = 0,
                         hsp_cb_Turu *parent = 0);
    ~hsp_cb_Turu() { qDeleteAll(lo_children); }

    /// XML:002
    /// getters and setters
    /// variables for XML file
    ///

    QString getHs_Tur() const { return mstr_hs_Tur; }
    void setHs_Tur(const QString &hsp_cb_Turu) { mstr_hs_Tur = hsp_cb_Turu; }

    QColor getHs_Color() const { return mcol_hs_Color; }
    void setHs_Color(const QColor &hesapColor) { mcol_hs_Color = hesapColor; }

    QIcon getHs_icon() const    { return mico_hs_Icon; }
    void setHs_Icon(const QIcon &hesapIcon) { mico_hs_Icon = hesapIcon; }

    QString getHs_01() const  { return mstr_hs_01; }
    void setHs_01(const QString &hesap01) { mstr_hs_01 = hesap01; }

    QString getHs_02() const  { return mstr_hs_02; }
    void setHs_02(const QString &hesap02) { mstr_hs_02 = hesap02; }

    quint64 getHs_T_Kod() const   { return mint_hs_T_Kod; }
    void setHs_T_Kod(const quint64 &hesapTKod)  { mint_hs_T_Kod = hesapTKod; }

    hsp_cb_Turu *parent() const { return o_parent; }
    hsp_cb_Turu *childAt(int row) const { return lo_children.value(row); }
    int rowOfChild(hsp_cb_Turu *child) const { return lo_children.indexOf(child); }
    int childCount() const     { return lo_children.count(); }
    bool hasChildren() const     { return !lo_children.isEmpty(); }
    QList<hsp_cb_Turu *> children() const { return lo_children; }

    void insertChild(int row, hsp_cb_Turu *item)
    { item->o_parent = this; lo_children.insert(row, item); }
    void addChild(hsp_cb_Turu *item)
    { item->o_parent = this; lo_children << item; }
    void swapChildren(int oldRow, int newRow)
    //  qt5      { m_children.swap(oldRow, newRow); }
    { lo_children.swapItemsAt (oldRow, newRow); }
    hsp_cb_Turu *takeChild(int row);

private:
    /// XML:001
    /// define
    /// variables for XML file
    ///


    QString mstr_hs_Tur;
    QColor  mcol_hs_Color;
    QIcon   mico_hs_Icon;
    QString mstr_hs_01;
    QString mstr_hs_02;
    quint64 mint_hs_T_Kod;

    hsp_cb_Turu *o_parent;
    QList<hsp_cb_Turu *> lo_children;
};

#endif // hsp_cb_Turu_H
