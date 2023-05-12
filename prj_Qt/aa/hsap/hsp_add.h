#ifndef hsp_Add_H
#define hsp_Add_H

#include "hsap/hesapitem.h"
#include "libs/globals.h"

class hsp_Add : public QMainWindow
{
    Q_OBJECT
public:
    explicit hsp_Add(QWidget *parent = nullptr);
    ~hsp_Add();
    QWidget *mainwdgt;

    HesapItem *yeni() { return yeniItem; };

    QLineEdit* le_ad ;
    QLineEdit* le_acklama ;
    QComboBox* cb_topluHesap;
    QComboBox* cb_hesapTuru ;
    QComboBox* cb_ustHesap ;

private:
    HesapItem *yeniItem;
    QString f_ms_hesapAd;
    QString f_ms_hesapAcklm;
    bool    f_mb_topluHesap;
    QString f_ms_hesapTuru;
    QString f_ms_ustHesap;
    QString f_ms_DBFile;


private slots:
    void yaz();


signals:

};

#endif // hsp_Add_H
