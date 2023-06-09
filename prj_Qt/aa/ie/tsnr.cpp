﻿#include "tsnr.h"

hC_TSNR::hC_TSNR() : hC_tBcreator ()
{
    qDebug ()<<"Constructor TAŞINIR İSTEK ****************************";
    //************************************************************
    //************  T A Ş I N I R   İ S T E K  *******************


    win_Label->setText ( "TAŞINIR İSTEK");
    *tb_name  = "tsnr_dbtb" ;
    *tb_ndex  = "tsnr_tarih";

    tb_flds = new hC_ArrD (8, 4);
    tb_flds->setValue ( 0, "tsnr_id"      , "INTEGER", "TaşınırID", "0" ) ;
    tb_flds->setValue ( 1, "tsnr_iedet_no", "INTEGER", "İEDetayID","0" );
    tb_flds->setValue ( 2, "tsnr_no "     , "TEXT"   , "Taşınır No" );
    tb_flds->setValue ( 3, "tsnr_tarih"   , "TEXT"   , "Tarih");
    tb_flds->setValue ( 4, "tsnr_usta"    , "TEXT"   , "Usta"   );
    tb_flds->setValue ( 5, "tsnr_durum"   , "TEXT"   , "Durum"    );
    tb_flds->setValue ( 6, "tsnr_aciklama", "TEXT"   , "Açıklama"   );
    tb_flds->setValue ( 7, "tsnr_resim"   , "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_TSno = new QLineEdit  ) ;
    tb_wdgts->append ( dE_TStarih = new QDateTimeEdit(QDate::currentDate ())  ) ;
    tb_wdgts->append ( lE_TSusta = new QLineEdit ) ;
    tb_wdgts->append ( cbx_TSdurum = new QComboBox    ) ;
    tb_wdgts->append ( lE_TSaciklama  = new QLineEdit  ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;



}

void hC_TSNR:: tbsetup()
{
    qDebug() << "   tsnr setup ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_TSNR:: tbui()
{
    qDebug() << "   ui";
    hC_TSNR::setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_Grid->addWidget (win_Wdgt   , 0, 1, 1, 1);
}

void hC_TSNR:: tbwdgt()
{
    qDebug() << "   WDGT";
    auto *lB_tsno = new QLabel("Taşınır No");
    lE_TSno->setText ("*TSdetno");
    lE_TSno->setReadOnly (true);
    lB_tsno->setBuddy(lE_TSno);

    QLabel *lB_gt = new QLabel("Tarih");
    dE_TStarih->setDisplayFormat("dd.MM.yyyy");
    dE_TStarih->setMinimumDate(QDate(01, 01, 1900));
    dE_TStarih->setMaximumDate(QDate(valiDDate));
    dE_TStarih->setCalendarPopup(true);
    lB_gt->setBuddy(dE_TStarih);


    QLabel *lB_us = new QLabel("İstenen Malzeme Adı");
    lB_us->setBuddy(lE_TSusta);

    QLabel *lB_dr = new QLabel("Durum");
    cbx_TSdurum->addItem ("-");
    cbx_TSdurum->addItem ("Ambara Bildirildi");
    cbx_TSdurum->addItem ("Satın Alınıyor");
    cbx_TSdurum->addItem ("Atölyede İmal Ediliyor");
    cbx_TSdurum->addItem ("Dış piyasada İmal Ettiriliyor");
    cbx_TSdurum->addItem ("Tedarik Edildi");
    cbx_TSdurum->addItem ("Teslim Edildi");
    lB_dr->setBuddy(cbx_TSdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");
    lB_acklm->setBuddy(lE_TSaciklama);

    win_Rsm = new QLabel("Taşınır İstek");

    ///////////////////////////////////////
    
    win_Wdgt->adjustSize ();
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_TSaciklama->setMinimumSize (200,25);


    wdgtGrid->addWidget(lB_tsno      , 0, 0, 1, 1);
    wdgtGrid->addWidget(lE_TSno      , 0, 1, 1, 3);
    wdgtGrid->addWidget(lB_gt        , 1, 0, 1, 1);
    wdgtGrid->addWidget(dE_TStarih   , 1, 1, 1, 3);
    wdgtGrid->addWidget(lB_us        , 2, 0, 1, 1);
    wdgtGrid->addWidget(lE_TSusta    , 2, 1, 1, 3);
    wdgtGrid->addWidget(lB_dr        , 3, 0, 1, 1);
    wdgtGrid->addWidget(cbx_TSdurum  , 3, 1, 1, 1);
    wdgtGrid->addWidget(lB_acklm     , 4, 0, 1, 1);
    wdgtGrid->addWidget(lE_TSaciklama, 4, 1, 1, 3);
    wdgtGrid ->addWidget (win_Rsm    , 5, 1, 2, 3);
}



void hC_TSNR:: tbkntrl()
{

    qDebug()<<"   tsnr kontrol ";

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id     = maxID.hC_NrMax ( tb_name,
                            tb_flds->value (0,0));
        ////////////////////////////////////////////////
        QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO "+ *tb_name +" ( "
            "tsnr_iedet_no , tsnr_no "
            " )"
            " values( ?, ? )";
        q.prepare(q_s);

        q.bindValue(0, *max_id ); // iedet no yapılacak
        q.bindValue(1, 1 );// ts_id ile yapılacak

        q.exec();
        qDebug ()<<"ts 18";
        if (q.isActive())
        {
            qDebug () <<"Taşınır Yeni Kayıt Eklendi - "<< lE_TSno->text() << " -   Eklendi";
            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *max_id , 0,2);
            ////////////////////////////////////////////////

        }
        else
        {
            qDebug () << "Taşınır Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
        }
               // tasinir ekle
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // tasinir  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("TAŞINIR KAYDI SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "Taşınır kaydı silinecek ;\n"
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            // şimdi taşınır silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex tasinir_indx = tb_view->table->currentIndex ();
            QString ino = tb_model->data
                    (tb_model->index
                     (tasinir_indx.row (),
                      tb_model->fieldIndex ("id_tasinir"))).toString ();

            s_qry = QString("DELETE FROM dbtb_tasinir "
                            "WHERE id_tasinir = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " Taşınır Kaydı Silindi ";
                //  tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - Taşınr Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
        }
    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_TSNR::sgn(tb_view->table->model()->index( Index.row() ,
        //               tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });


}




hC_TSNR::~hC_TSNR()
{
    qDebug() << "*********** destructor TAŞINIR İSTEK";
}
