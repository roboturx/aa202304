#include "hsap/hsp_cb_turu.h"

hsp_cb_Turu::hsp_cb_Turu() {}

hsp_cb_Turu::hsp_cb_Turu(const QString &hs_Tur,
                         const QColor &hs_Color,
                         const QIcon &hs_icon,
                         const QString &hs_01,
                         const QString &hs_02,
                         const quint64 &hs_T_Kod,
                         hsp_cb_Turu *parent)
    : mstr_hs_Tur(hs_Tur)
    , mcol_hs_Color(hs_Color)
    , mico_hs_Icon(hs_icon)
    , mstr_hs_01(hs_01)
    , mstr_hs_02(hs_02)
    , mint_hs_T_Kod(hs_T_Kod)
    , o_parent(parent)
{
    //  qDebug()<<"    ::Xitem constrctr";
    if (parent)
        o_parent->addChild(this);
}

hsp_cb_Turu *hsp_cb_Turu::takeChild(int row)
{
    // qDebug()<<"    ::Xitem takeechild";
    hsp_cb_Turu *item = lo_children.takeAt(row);
    Q_ASSERT(item);
    item->o_parent = 0;
    return item;
}
