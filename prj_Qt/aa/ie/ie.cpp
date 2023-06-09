﻿#include "ie.h"
//static int x=10;
//static int y=10;



hC_IE::hC_IE(QWidget *parent)  : hC_tBcreator (parent)
{
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
    qDebug() << "Constructor İŞ EMRİ *************************************  ";

    setAcceptDrops(true);
    setObjectName("ThisObjectsnameIsIE");

    win_Label->setText ( "İŞ EMRİ KAYITLARI");
    *tb_name  = "ie_dbtb" ;
    *tb_ndex  = "ie_no";

    tb_flds = new hC_ArrD (11, 4);
    tb_flds->setValue ( 0, "ie_ID"    , "INTEGER", "İşEmriID", "0" ) ;
    tb_flds->setValue ( 1, "ie_no"    , "INTEGER", "İş Emri No" );
    tb_flds->setValue ( 2, "ie_kurumno"   , "TEXT"   , "Kurum No" ) ;
    tb_flds->setValue ( 3, "ie_tarih" , "TEXT"   , "İş Emri Tarihi" );
    tb_flds->setValue ( 4, "ie_durum" , "TEXT"   , "Durum");
    tb_flds->setValue ( 5, "ie_girtar", "TEXT"   , "Araç Giriş Tarihi"   );
    tb_flds->setValue ( 6, "ie_ciktar", "TEXT"   , "Araç Çıkış Tarihi"   );
    tb_flds->setValue ( 7, "ie_y1"    , "TEXT"   , "Yetkili I"    );
    tb_flds->setValue ( 8, "ie_y2"    , "TEXT"   , "Yetkili II"   );
    tb_flds->setValue ( 9, "ie_resimmkn" , "BLOB"   , "ResimMkn" , "0" );
    tb_flds->setValue ( 10, "ie_resimie" , "BLOB"   , "ResimIe" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_ieno = new QLineEdit  ) ;
    tb_wdgts->append ( hClE_mkn = new hC_Le     ) ;
    tb_wdgts->append ( dE_geltar = new QDateTimeEdit(QDate::currentDate ())  ) ;
    tb_wdgts->append ( cbX_durum = new QComboBox ) ;
    tb_wdgts->append ( dE_girtar = new QDateTimeEdit(QDate::currentDate ())) ;
    tb_wdgts->append ( dE_ciktar = new QDateTimeEdit(QDate::currentDate ()) ) ;
    tb_wdgts->append ( hClE_yetkili1 = new hC_Le     ) ;
    tb_wdgts->append ( hClE_yetkili2 = new hC_Le    ) ;
    tb_wdgts->append ( new QLabel    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;


}

void hC_IE::tbsetup()
{
    qDebug() << "   ie setup ";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );
    tb_mapper->addMapping (hClE_mkn->lineEdit ,
                           tb_model->fieldIndex ("ie_kurumno"));
    tb_mapper->addMapping (hClE_yetkili1->lineEdit ,
                           tb_model->fieldIndex ("ie_y1"));
    tb_mapper->addMapping (hClE_yetkili2->lineEdit ,
                           tb_model->fieldIndex ("ie_y2"));




    mkn = new hC_MKN ;
    mkn->tbsetup();



    tbwdgt  ();
    tbui();
    tbkntrl ();
    isEmriListele ();
}


void hC_IE::tbui()
{
    qDebug() << "   ieui";

    hC_IE::setWindowTitle (win_Label->text());
    this->adjustSize ();


    //    tb_view->setAcceptDrops(false);
    //  win_Wdgt->setAcceptDrops(false);

    auto yiekle = new QPushButton("İş Emri Ekle");
    connect( yiekle, &QPushButton::clicked,
             [&]()
    {
        this->tb_view->pB_ekle->clicked() ;
    });

    auto ielist = new QPushButton("İş Emri Listele");
    connect( ielist, &QPushButton::clicked,
             [&]()
    {
        this->isEmriListele() ;
    });


    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget ( tb_view  ,  0, 0, 1, 1 );
   // win_Grid->addWidget ( win_Wdgt ,  0, 1, 1, 1 );
    win_Grid->addWidget ( yiekle   ,  1, 5, 1, 1 );
    win_Grid->addWidget ( ielist   ,  1, 6, 1, 1 );

}

void hC_IE::tbwdgt ()
{
    qDebug () << "   ie wdgt";

    auto* lB_mk = new QLabel("Araç Kurum No");
    hClE_mkn->lineEdit->setReadOnly (true);

    connect(hClE_mkn->pushButton2 , &QPushButton::clicked,
            [this ]()
    {
        hClE_mkn->lineEdit->clear () ;
    });
    connect(hClE_mkn->pushButton , &QPushButton::clicked,
            [this ]()
    {
        // mkn seçebilmek için pencere
        auto *mkndia = new QDialog();
        mkndia->setModal (true);
        mkndia->setGeometry ( 50, 300, 400, 200 );
        mkndia->setWindowTitle ( "Araç Seçimi" );

        mkn->show ();
        // ----------------------------------------------------
        // tableviewinde gezinirken
        // mkn
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------
        connect (mkn , &hC_MKN::sgnMkn ,
                 [ this ] ( QString sgnText )
        {
            qDebug ()<<"sgn mkn";
            hClE_mkn->lineEdit->setText ( sgnText );
            hClE_mkn->lineEdit->setFocus();
        });
        ////////////////////////////////////////////************
        auto *layout = new QGridLayout;
        mkndia->setLayout (layout);
        layout->addWidget (mkn  ,0 ,0 );
        mkndia->exec ();
    });



    auto* lB_ie = new QLabel("İş Emri No");
    lE_ieno->setReadOnly (true);

    auto *lB_get = new QLabel("Araç Geliş Tarihi");
    hC_Gz(dE_geltar,"nulldate");
    lB_get->setBuddy(dE_geltar);

    auto *lB_dr = new QLabel("Araç Durumu ");
    QStringList lst{ "Sıra Bekliyor",
                     "Bakıma Alındı",
                     "Tamamlandı"};
    cbX_durum->insertItems(0,lst);

    auto lB_git = new QLabel("Atölye Giriş Tarihi");
    hC_Gz(dE_girtar,"nulldate");
    lB_git->setBuddy(dE_girtar);

    auto lB_cit = new QLabel("Atölye Çıkış Tarihi");
    hC_Gz(dE_ciktar,"nulldate");

    auto lB_y1 = new QLabel("Yetkili - I ");

    auto lB_y2 = new QLabel("Yetkili - II");

    hC_Rs resim(win_Rsm);

    //////////////////////////////////////////////
    
    win_Wdgt->adjustSize ();
    auto wdgtGrid = new QGridLayout;
    win_Wdgt->setLayout (wdgtGrid);

    wdgtGrid->addWidget (lB_ie   , 0,  0, 1, 4);
    wdgtGrid->addWidget (lE_ieno , 0,  4, 1, 6);
    wdgtGrid->addWidget (lB_mk   , 0, 10, 1, 4);
    wdgtGrid->addWidget (hClE_mkn  , 0, 14, 1, 6);

    wdgtGrid->addWidget (lB_get    , 1, 0, 1, 4);
    wdgtGrid->addWidget (dE_geltar , 1, 4, 1, 6);
    wdgtGrid->addWidget (lB_dr     , 2, 0, 1, 4);
    wdgtGrid->addWidget (cbX_durum , 2, 4, 1, 6);
    wdgtGrid->addWidget (lB_git    , 3, 0, 1, 4);
    wdgtGrid->addWidget (dE_girtar , 3, 4, 1, 6);
    wdgtGrid->addWidget (lB_cit     , 4, 0, 1, 4);
    wdgtGrid->addWidget (dE_ciktar  , 4, 4, 1, 6);
    wdgtGrid->addWidget (lB_y1       , 1, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili1 , 1, 14, 1, 6);
    wdgtGrid->addWidget (lB_y2       , 2, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili2 , 2, 14, 1, 6);
    wdgtGrid->addWidget (new QLabel("Resim") , 3, 10, 1, 4);
    wdgtGrid->addWidget (win_Rsm      , 3, 14, 2, 6);



}

void hC_IE::tbkntrl()
{

    qDebug()<<"   ie kntrl";

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        /// yeni kayıt için kurum noyu mkn den alalım

        QDialog makinasec;
        QHBoxLayout xl ;
        makinasec.setLayout (&xl);
        xl.addWidget (mkn);

        //*** seçim penceresinde makina seçilir
        // yoksa yeni oluşturulur
        QString kurumno_sT ;
        mknrsm_bA = new QByteArray ;
        son_bA = new QByteArray ;

        connect(mkn, &hC_MKN::sgnMkn,
                [&kurumno_sT, this  ]
                (QString krmNo_sT,
                QByteArray byteArray) mutable
        {
            //***  1   iş emri için kurum no
            kurumno_sT = krmNo_sT ;
            //*** signal dan gelen byte array
            *mknrsm_bA  =  byteArray.fromRawData
                    (byteArray, byteArray.size ());

            *son_bA = mkn->tb_view->table->
                    model()->index(
                        mkn->tbx_slctnMdl->currentIndex ().row (),
                        mkn->tb_model->fieldIndex ( "mkn_resim" )
                        ).data().toByteArray();
        });
        makinasec.exec ();

        qDebug()<<"   ie kntrl seçilen  kurumno st---------> "<< kurumno_sT;


        //*** makina seçildi yola devam
        ////////////////////////////////////////////////
        /// yeni iş emri numaasını bul
        /// iş emri nosu _dbtb de
        /// no alanındaki en büyük sayı
        hC_Nr maxID;
        int ieno_nT ;
        ieno_nT     = maxID.hC_NrMax ( tb_name,
                                       tb_flds->value (0,0));

        ////////////////////////////////////////////////
        /// yeni kaydı ekle

        QSqlQuery q;
        QString qry, mesaj("");
        qry = QString("INSERT INTO %1 ( "
                      "ie_no    , "
                      "ie_kurumno   , "
                      "ie_durum , "
                      "ie_tarih ) "
                      " values ( '%2', '%3', '%4', '%5'  ) " )
                .arg ( *tb_name)
                .arg ( QString::number( ieno_nT))
                .arg ( kurumno_sT )
                .arg ( cbX_durum->itemText (0))
                .arg ( QDate::currentDate ().toString ("dd/MM/yy"));

        if ( !q.exec(qry) )
        {
            mesaj = mesaj + " İş Emri Eklenemedi"+
                    "-----"+
                    q.lastError().text ()+
                    "-----";
            QMessageBox::information(this,"Kayıt Ekleme Hatası:",
                                     "HATA - İş Emri Kaydı Eklenemedi!\n"
                                     +q.lastError ().text ());

        }
        else
        {
            mesaj = mesaj + " İş Emri eklendi.";



            //// resmi de yazalım
            /// yeni eklenenleri kaydedelim

            hClE_mkn->lineEdit->setText ( kurumno_sT );
            hC_Gz (dE_geltar , "nulldate");
            hC_Gz (dE_girtar , "nulldate");
            hC_Gz (dE_ciktar , "nulldate");
            cbX_durum->setCurrentText (" ");
            hClE_yetkili1->lineEdit->setText ("");
            hClE_yetkili2->lineEdit->setText ("");

            // iş emrinde yeni kayda git
            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, ieno_nT , 0);
            ////////////////////////////////////////////////

            /// yeni boş ie kayıt eklendi

            ///////////////////////////////////////////////////////////////////
            /// ieno nun olduğu indexteyiz
            QModelIndex iendx = tb_view->table->currentIndex ();
            int iendxrow = iendx.row ();

            *son_bA=son_bA->toHex();

            /// mkn den gelen resmi ie ye yazalım
            tb_model->setData(tb_model->
                              index(iendxrow, tb_model->fieldIndex
                                    ( "ie_resimmkn" )), *son_bA );

            //qDebug()<<"   ie kntrl kayıt tamamlandı";
            tb_model->submitAll();

            QDateTime tarih_dT = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_tarih" )).data ().toDateTime ();
            QString durum_sT = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_durum" )).data ().toString();
            QDateTime girtar_dT {} ;
            QDateTime ciktar_dT {} ;
            QString   y1_sT     {} ;
            QString   y2_sT     {} ;


            QByteArray iersmie_bA = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_resimie" )).data ().toByteArray ();
            QByteArray iersmmkn_bA = tb_view->table->model ()
                    ->index ( iendxrow, tb_model
                              ->fieldIndex( "ie_resimmkn" )).data ().toByteArray ();

            iersmmkn_bA=QByteArray::fromHex(iersmmkn_bA);
            ///////////////////////////////////////////////////////////////////




            isEmriYeni (ieno_nT,
                        kurumno_sT,
                        tarih_dT,
                        durum_sT,
                        girtar_dT,
                        ciktar_dT,
                        y1_sT,
                        y2_sT,
                        iersmmkn_bA,
                        iersmie_bA,
                        QPoint (10,10));

        }
        qDebug () <<mesaj;
        // iş emri ekle

    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                    "ie_resimie", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "ie_resimie", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // ie  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("İŞ EMRİNİ SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "İş emrini silerseniz;\n"
                       "bu İş Emri bağlı (iş emri detay, taşınır ve işçilik)\n "
                       "tüm kayıtlarda silinir\n "
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            /// önce bu iş emrine bağlı
            /// iedet
            /// iedet kayıtlarına bağlı
            /// taşınır
            /// işçilik kayıtlarını silelim



            // şimdi iş emrini silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex indx = tb_view->table->currentIndex ();

            // iedet sil
            QString ieieno = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("ie_no"))).toString ();

            s_qry = QString("DELETE FROM iedet_dbtb "
                            "WHERE iedet_id = %1").arg( ieieno );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Detay Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {
                QMessageBox::information(this,"Kayıt Silme Hatası:",
                                         "HATA - İş Emri Detay Kaydı Silinemedi!\n"
                                         +q_qry.lastError ().text ());
            }
            // ie sil
            QString idie = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("ie_id"))).toString ();


            s_qry = QString("DELETE FROM ie_dbtb "
                            "WHERE ie_id = %1").arg( idie );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {
                QMessageBox::information(this,"Kayıt Silme Hatası:",
                                         "HATA - İş Emri Kaydı Silinemedi!\n"
                                         +q_qry.lastError ().text ());
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
        // 011-02 setfilter
        // 011-02 filtrele

        /// iş emri no her yılbaşında birden başlar


        /*       int no = tb_model->data
                (tb_model->index
                 (Index.row (),
                  tb_model->fieldIndex ("no"))).toInt ();
*/
        // 011-03 ie de row değiştiğinde ie noyu ismini etrafa yayınlayalım
        emit hC_IE::sgnIsEmri ( tb_view->table->model()->
                                index( Index.row() ,
                                       tb_model->fieldIndex ("ie_no")
                                       ).data().toInt() );

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });

    // --- 013-01 iş durumuna göre tarihleri gizle
    connect(  cbX_durum , &QComboBox::currentTextChanged,
              [this]( QString text )
    {
        if (text == " ")
        {
            hC_Gz ( dE_geltar, "0" );
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );



        }
        else if (text == "Sıra Bekliyor")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Bakıma Alındı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Tamamlandı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "1" );
        }
    });


}


void hC_IE::isEmriListele()
{
    qDebug () <<"   işemrilistele";
    ///// toolbutton için
    ////////////////// iş emirlerini ekrana listele

    //  cards = new QMap<int,IEcard*> ;

    QSqlQuery query("SELECT * FROM ie_dbtb "
                    "WHERE ie_durum != 'Tamamlandı'");
    if (!query.isActive ())
    {
        QMessageBox::information(this,"İş Emri Kart Hatası:",
                                 "HATA - İş Emri Kartları Listelenemiyor !\n"
                                 +query.lastError ().text ());

        return;
    }

    static int x11=10;
    static int y11=10;
    static int x21=410;
    static int y21=10;

    QPoint iepos_pT(x11,y11);     // ( x11+=20, y11+=20 );

    int qy=0;

    while (query.next())
    {
        ++qy;
      QSqlRecord rec = query.record();


        //int nameCol = rec.indexOf("ie_no"); // index of the field "name"

        int ieno_nT {query.value ("ie_no").toInt () };
        QString krmno_sT {query.value ("ie_kurumno").toString ()};

        // tb-view de indexi bul
        hC_Nr xnr;
        xnr.hC_NrGo(tb_view, tb_model, ieno_nT, 1 );

        ///////////////////////////////////////////////////////////////////
        /// ieno nun olduğu index i bulalım

        QSortFilterProxyModel proxy;
        proxy.setSourceModel(tb_model);
        proxy.setFilterKeyColumn( tb_model->fieldIndex ("ie_no"));
        proxy.setFilterFixedString( QString::number(ieno_nT));
        // now the proxy only contains rows that match the name
        // let's take the first one and map it to the original model

        QModelIndex matchingIndex = proxy.mapToSource(proxy.index(0,1));
        if(matchingIndex.isValid())
        {
            tb_view->table->scrollTo(matchingIndex,
                                     QAbstractItemView::EnsureVisible);

        } else {
            QMessageBox::information(this,"Name Search:", "Match not found!");
        }
        /// index  istediğimiz yere geldi

        QModelIndex ndx = tb_view->table->currentIndex ();
        int iendxrow = ndx.row ();
        //QMessageBox::information(this,"ie index row", QString::number(ndxrow));
        /// ie resmini table dan alalım
        QString kurumno_sT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_kurumno" )).data ().toString();
        QDateTime tarih_dT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_tarih" )).data ().toDateTime ();
        QString durum_sT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_durum" )).data ().toString();
        QDateTime girtar_dT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_girtar" )).data ().toDateTime ();
        QDateTime ciktar_dT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_ciktar" )).data ().toDateTime ();
        QString y1_sT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_yetkili1" )).data ().toString();
        QString y2_sT = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_yetkili2" )).data ().toString();
        QByteArray iersmie_bA = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_resimie" )).data ().toByteArray ();
        QByteArray iersmmkn_bA = tb_view->table->model ()
                ->index ( iendxrow, tb_model
                          ->fieldIndex( "ie_resimmkn" )).data ().toByteArray ();


        if ( durum_sT == "Sıra Bekliyor")
        {
            x11 += 50 ;
            y11 += 30 ;
            iepos_pT.rx() = x11 ;
            iepos_pT.ry() = y11 ;

            qDebug () <<"---------------------------sıra bekliyor  ="
                     << iepos_pT ;

        }
        if (durum_sT == "Bakıma Alındı")
        {

            x21 += 50 ;
            y21 += 30 ;
            iepos_pT.rx() = x21 ;
            iepos_pT.ry() = y21 ;
            qDebug () <<"---------------------------bakımaalındı = x ="
                     << iepos_pT;

        }


        isEmriYeni (ieno_nT,
                    kurumno_sT,
                    tarih_dT,
                    durum_sT,
                    girtar_dT,
                    ciktar_dT,
                    y1_sT,
                    y2_sT,
                    iersmmkn_bA,
                    iersmie_bA,
                    iepos_pT )  ;
    }

}

void hC_IE::isEmriYeni(int ieno_nT,
                       QString kurumno_sT,
                       QDateTime tarih_dT,
                       QString durum_sT,
                       QDateTime girtar_dT,
                       QDateTime ciktar_dT,
                       QString y1_sT,
                       QString y2_sT,
                       QByteArray iersmmkn_bA,
                       QByteArray iersmie_bA,
                       QPoint iepos_pT )
{



    //    qDebug()<<"   ie yeni ";

    iersmmkn_bA=QByteArray::fromHex(iersmmkn_bA);
    QImage iemkn_img = QImage ( ":/rsm/rsm_yok.png" );
    if ( ! iersmmkn_bA.isEmpty () )
    {
        iemkn_img = QImage::fromData(iersmmkn_bA);
    }
    QPixmap iemkn_pX=QPixmap::fromImage (iemkn_img);

    QImage ie_img = QImage ( ":/rsm/rsm_yok.png" );
    if ( ! iersmie_bA.isEmpty ()  )
    {
        ie_img = QImage ( ":/rsm/rsm_yok.png" );
    }
    QPixmap ie_pX=QPixmap::fromImage (ie_img);




    auto iec = new IEcard (  this ,
                             ieno_nT,
                             kurumno_sT,
                             tarih_dT,
                             durum_sT,
                             girtar_dT,
                             ciktar_dT,
                             y1_sT,
                             y2_sT,
                             iemkn_pX,
                             ie_pX,
                             iepos_pT) ;
    iec->setObjectName("ChildObjNameOf_krmno_"+kurumno_sT+"--");


}




hC_IE::~hC_IE()
{
    qDebug() << "*********** destructor İŞ EMRİ " ;
}







void hC_IE::mousePressEvent(QMouseEvent *event)
{

    if (event->button () == Qt::LeftButton )
    {

        //    IEcard *iechild = this->findChild<IEcard*>("");

        ///burada child olarak alınıyor
        IEcard *child = static_cast< IEcard *>(this->childAt(event->pos()));

        //  qDebug () << "-child ne--------------------------------"
        //  << child->objectName();


        if (!child || child->objectName()=="")
        {

            qDebug () << "-child yok --------------------------------";
            //<< child->getIeno_nT();

            return;
        }
        else
        {
            qDebug () << "--child var-------------------------------"
                      << child->getIeno_nT() <<" pos = "<<event->pos();

        }

        qDebug() << "this objname   "<< this->objectName();
        //qDebug() << "this parent objname   "<< this->parent()->objectName();
        qDebug() << " -child objname "<< child->objectName()<<" pos = "<<event->pos();
        qDebug() << " -child getpos "<<" pos = "<<child->getIepos_pT();
        qDebug() << " -child parent objname "<< child->parent()->objectName();



        QByteArray datatoStream_bA;

        QDataStream streamGotFromObject
                ( &datatoStream_bA, QIODevice::WriteOnly);

        streamGotFromObject << child->getIeno_nT ()
                            << child->getKurumno_sT ()
                            << child->getTarih_dT()
                            << child->getDurum_sT()
                            << child->getGirtar_dT()
                            << child->getCiktar_dT()
                            << child->getY1_sT()
                            << child->getY2_sT()
                            << child->getIemkn_pX()
                            << child->getIe_pX()
                            << event->pos() ; //getIepos_pT();
        //burdaki farkı drop ta kullan

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", datatoStream_bA);
        ///datatoStream_bA);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        ///resmin küçüğününü yap
        /// // dragger pixmap
        QPixmap tempPixmap = child->getIemkn_pX () ;
        drag->setPixmap(tempPixmap.scaled(160,100,Qt::KeepAspectRatio));
        drag->setHotSpot(event->pos() - child->pos());

        /// dragger pixmap painter
        /*QPainter painter;
    painter.save ();
       // painter.begin(&tempPixmap);
  //      painter.drawPixmap (rect (),tempPixmap);
      //  painter.end();
        painter.drawText ( 5, 20, "1. sıra yazı" );
        painter.drawText ( 5, 35, "2. sıra yazı" );
        painter.drawText ( 5, 50, "3. sıra yazı" );
        painter.drawText ( 5, 65, "4. sıra yazı" );
        painter.drawText ( 5, 80, "5. sıra yazı" );
painter.restore ();

*/
        child->setIemkn_pX (tempPixmap);

        //        if (drag->exec(Qt::CopyAction  | Qt::MoveAction,
        //                     Qt::CopyAction) == Qt::MoveAction)
        if (drag->exec() == Qt::MoveAction)
        {
            child->close();
        }
        else
        {
            child->show();
            child->setIemkn_pX (tempPixmap);
        }
    }

}



void hC_IE::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void hC_IE::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}


void hC_IE::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        IEcard *newIcon = new IEcard ( this ) ;

        QByteArray datafromStream_bA = event->
                mimeData()->data("application/x-dnditemdata");
        QBuffer buffer(&datafromStream_bA);
        buffer.open(QIODevice::ReadOnly);
        QDataStream streamSentToObject(&buffer);
        // stream ile obje datalarını yeni objeye yolla

        int ieno_nTx;
        QString kurumno_sTx;
        QDateTime tarih_dTx ;
        QString durum_sTx ;
        QDateTime girtar_dTx ;
        QDateTime ciktar_dTx ;
        QString y1_sTx ;
        QString y2_sTx ;
        QPixmap iemkn_pXx;
        QPixmap ie_pXx;
        QPoint iepos_pTx;

        streamSentToObject
                >> ieno_nTx
                >> kurumno_sTx
                >> tarih_dTx
                >> durum_sTx
                >> girtar_dTx
                >> ciktar_dTx
                >> y1_sTx
                >> y2_sTx
                >> iemkn_pXx
                >> ie_pXx
                >> iepos_pTx;


        newIcon->setIeno_nT (ieno_nTx);
        newIcon->setKurumno_sT (kurumno_sTx);
        newIcon->setTarih_dT   ( tarih_dTx   ) ;
        newIcon->setDurum_sT   ( durum_sTx   ) ;
        newIcon->setGirtar_dT  ( girtar_dTx  ) ;
        newIcon->setCiktar_dT  ( ciktar_dTx  ) ;
        newIcon->setY1_sT      ( y1_sTx      ) ;
        newIcon->setY2_sT      ( y2_sTx      ) ;
        newIcon->setIemkn_pX   ( iemkn_pXx   ) ;
        newIcon->setIe_pX      ( ie_pXx      ) ;
        newIcon->setIepos_pT   ( iepos_pTx   ) ;

        newIcon->setObjectName("ChildObjNameOf_krmno_"+kurumno_sTx+"--");

        //  newIcon->setIepos_pT   ( newIcon->getIepos_pT()  ) ;
        //newIcon->move ( event->pos() - newIcon->getIepos_pT());
       //++++ newIcon->move ( event->pos() );
        //newIcon->move(newIcon->getIepos_pT());
        newIcon->show();
        newIcon->setToolTip ( newIcon->ietooltip() );
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this )
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();

        } else
        {
            event->acceptProposedAction();
        }
    } else
    {
        event->ignore();
    }

}








/////////////////////////////////////////////////////////
/// \brief IEcard::IEcard
/// \param parent
///
///
///
///


IEcard::IEcard(QWidget *parent , int ieno_nTx,
               QString kurumno_sTx,
               QDateTime tarih_dTx,
               QString durum_sTx,
               QDateTime girtar_dTx,
               QDateTime ciktar_dTx,
               QString y1_sTx,
               QString y2_sTx,
               QPixmap iemkn_pXx,
               QPixmap ie_pXx,
               QPoint iepos_pTx) :
    QWidget(parent),
    ieno_nT   (ieno_nTx),
    kurumno_sT (kurumno_sTx),
    tarih_dT   (tarih_dTx),
    durum_sT   (durum_sTx),
    girtar_dT  (girtar_dTx),
    ciktar_dT  (ciktar_dTx),
    y1_sT     (y1_sTx),
    y2_sT     (y2_sTx),
    iemkn_pX  (iemkn_pXx),
    ie_pX     (ie_pXx),
    iepos_pT  (iepos_pTx)
{

    qDebug ()<< "-----------iepos pT new create ptx   "<< iepos_pTx;
    qDebug ()<< "-----------iepos pT new create pt    "<< iepos_pT;

    IEcard::setIeno_nT    ( ieno_nT    ) ;
    IEcard::setKurumno_sT ( kurumno_sT ) ;
    IEcard::setTarih_dT   ( tarih_dT   ) ;
    IEcard::setDurum_sT   ( durum_sT   ) ;
    IEcard::setGirtar_dT  ( girtar_dT  ) ;
    IEcard::setCiktar_dT  ( ciktar_dT  ) ;
    IEcard::setY1_sT      ( y1_sT      ) ;
    IEcard::setY2_sT      ( y2_sT      ) ;
    IEcard::setIemkn_pX   ( iemkn_pX   ) ;
    IEcard::setIe_pX      ( ie_pX      ) ;
    IEcard::setIepos_pT   ( iepos_pT   ) ;


    IEcard::setAcceptDrops( false      ) ;
    IEcard::setMinimumSize( 160, 100   ) ;
    IEcard::move          ( getIepos_pT()   ) ;
    IEcard::setAttribute  ( Qt::WA_DeleteOnClose);
    IEcard::setToolTip (   ietooltip ());
    IEcard::show();


    //    SimileIcon = QPixmap(":/rsm/ex.ico");
    //    QToolButton* xxx1 = new QToolButton() ;
    //    //x->setIcon ( QIcon(":/images/boat.png"));
    //    xxx1->setIcon (QIcon( SimileIcon ));
    //    xxx1->setIconSize (QSize(25,25));
    //    xxx1->setAutoRaise (true);
    //    connect (xxx1, &QToolButton::clicked, this,
    //             &IEcard::smSLOT );

    QToolButton* x2 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x2->setIconSize (QSize(25,25));
    x2->setAutoRaise (true);
    connect (x2, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x3 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x3->setIconSize (QSize(25,25));
    x3->setAutoRaise (true);
    connect (x3, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    QToolButton* x4 = new QToolButton() ;
    //x->setIcon ( QIcon(":/images/boat.png"));
    x4->setIconSize (QSize(25,25));
    x4->setAutoRaise (true);
    connect (x4, &QToolButton::clicked, this,
             &IEcard::smSLOT );

    // x->move (50,50);
    //  auto gr = new QGridLayout(this);

    //gr->addWidget (resim    ,0 ,3 ,5 , 3 );

    //  gr->addWidget (xxx1       ,1 ,0 ,2 , 2 );
    //    gr->addWidget ( resim   ,2 ,0 ,2 , 2 );
    // gr->addWidget (x3       ,3 ,0 ,2 , 2 );
    // gr->addWidget (x4       ,4 ,0 ,2 , 2 );



}






//Paint event of button
void IEcard::paintEvent(QPaintEvent *paint)
{
    QWidget::paintEvent(paint);
    QPainter painter(this);

    painter.save();
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::SmoothPixmapTransform,1);
    painter.scale (1,1) ;
    painter.setPen(Qt::blue);                       //changing the color of pen.
    painter.setFont(QFont("Arial", 12, QFont::Bold));     //Changing the font.
    /////////////////////////////////////////////////////////////////////////////
    /// resim mkn çizelim
    QPixmap outPixmap = getIemkn_pX ();

    QPoint rr(rect ().x()+25,rect ().y()+25 );
    painter.drawPixmap ( rr ,outPixmap.scaled(120,75,Qt::KeepAspectRatio));
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra ie no yu yazalım
    QRect UstRect(0,0,150,24);
    painter.drawRect (UstRect);
    painter.fillRect (UstRect, QBrush (QColor(60,60,60,234)));
    painter.setPen(Qt::cyan);
    painter.drawText(UstRect, Qt::AlignHCenter | Qt::AlignCenter,
                     " "+ QString::number (getIeno_nT ())+
                     ":"+getKurumno_sT ());
    /////////////////////////////////////////////////////////////////////////////
    /// üst satıra kurumnoyu yazalım
    QRect altRect(rect ().x(),rect ().y()+105,
                  150,24);
    painter.drawRect (altRect);
    painter.fillRect (altRect, QBrush (QColor(60,60,60,224)));

    painter.setPen(Qt::green);
    painter.drawText(altRect, Qt::AlignHCenter | Qt::AlignCenter,
                     " İŞ EMRİ ");
    painter.restore();
}



void IEcard::mousePressEvent(QMouseEvent *event)
{
    if (event->button () == Qt::RightButton )
    {
        smSLOT ();
    }
    else
    {
        event->ignore ();
    }
    /*if (event->button () == Qt::LeftButton )
    {
        event->ignore ();
    }*/
}


QString IEcard::ietooltip()
{
    QString tool;
    tool = tool +"\nİş Emri No          : "+ QString::number(getIeno_nT    (  )) ;
    tool = tool +"\nKurum No            : "+ getKurumno_sT () ;
    tool = tool +"\nGeliş Tarihi        : "+ getTarih_dT   ().toString ("dd/MMM/yyyy");
    tool = tool +"\nDurum               : "+ getDurum_sT   () ;
    tool = tool +"\nAtölye Giriş Tarihi : "+ getGirtar_dT  ().toString ("dd/MMM/yyyy") ;
    tool = tool +"\nAyrılış Tarihi      : "+ getCiktar_dT  ().toString ("dd/MMM/yyyy") ;
    tool = tool +"\nYetkili             : "+ getY1_sT      () ;
    tool = tool +"\nYetkili             : "+ getY2_sT      () ;
    //tool = tool + getIemkn_pX   ();
    //tool = tool + getIe_pX      () ;
    //tool = tool + getIepos_pT   () ;
    return tool;
}



void IEcard::smSLOT()
{
    //qDebug ()  <<"  cw mkn view sağ tuş 001";
    auto *menu = new QMenu(this);

    // sigorta kaydı ekle
    const QIcon ekleIc_sgrt = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sgrt = new QAction(ekleIc_sgrt, tr("Sıra Bekliyor"), this);
    ekleAct_sgrt->setShortcuts (QKeySequence::New);
    ekleAct_sgrt->setStatusTip ("Sigorta Kaydı Ekle");
    connect (ekleAct_sgrt, &QAction::triggered,
             []()
    {
        qDebug()<<"menu sıra bekliyor of kurum no";
        //          << itemAt(pos) << ""<< &shapeItems[itemAt(pos)] ;
        //delete this;
    });

    menu->addAction(ekleAct_sgrt);

    // muayene kaydı ekle
    const QIcon ekleIc_mua = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_mua = new QAction(ekleIc_mua, tr("Usta Bekliyor"), this);
    ekleAct_mua->setShortcuts (QKeySequence::New);
    ekleAct_mua->setStatusTip ("Muayene Kaydı Ekle");
    connect (ekleAct_mua, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_mua);


    // yağ
    const QIcon ekleIc_yag = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_yag = new QAction(ekleIc_yag, tr("Parça Bekliyor"), this);
    ekleAct_yag->setShortcuts (QKeySequence::New);
    ekleAct_yag->setStatusTip ("Yağ Kaydı Ekle");
    connect (ekleAct_yag, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_yag);


    // filtre
    const QIcon ekleIc_flt = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_flt = new QAction(ekleIc_flt, tr("Tamamlandık"), this);
    ekleAct_flt->setShortcuts (QKeySequence::New);
    ekleAct_flt->setStatusTip ("Filtre Kaydı Ekle");
    connect (ekleAct_flt, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_flt);



    // yeni iş emri kaydı ekle
    const QIcon ekleIc_sipr = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_sipr = new QAction(ekleIc_sipr, tr("İş Emri Ekle..."), this);
    ekleAct_sipr->setShortcuts (QKeySequence::New);
    ekleAct_sipr->setStatusTip ("İş Emri Kaydı Ekle");
    connect (ekleAct_sipr, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(ekleAct_sipr);



    //  mkn kaydı SİL
    const QIcon silIc_mkn = QIcon(":/rsm/Erase.ico");
    QAction* silAct_mkn = new QAction(silIc_mkn, tr("Makina &Sil..."), this);
    silAct_mkn->setShortcuts (QKeySequence::New);
    silAct_mkn->setStatusTip ("DİKKAT :: Makina Kaydını ve bu makina ile ilgili herşeyi siler...");
    connect (silAct_mkn, &QAction::triggered, this,
             []()
    {
    });
    menu->addAction(silAct_mkn);

    menu->addSeparator();

    // QPoint pos(50,50);
    //menu->popup(this->mapToParent ( pos () ) ) ;
    menu->popup( QCursor::pos()  ) ;

}

IEcard::~IEcard()
{
}





int IEcard::getIeno_nT() const
{    return ieno_nT; }
void IEcard::setIeno_nT(int value)
{    ieno_nT = value ; }

QString IEcard::getKurumno_sT() const
{
    return kurumno_sT; }
void IEcard::setKurumno_sT(const QString value)
{
    kurumno_sT = value; }

QDateTime IEcard::getTarih_dT() const
{    return tarih_dT; }
void IEcard::setTarih_dT(const QDateTime value)
{    tarih_dT = value; }

QString IEcard::getDurum_sT() const
{    return durum_sT; }
void IEcard::setDurum_sT(const QString value)
{    durum_sT = value; }

QDateTime IEcard::getGirtar_dT() const
{    return girtar_dT; }
void IEcard::setGirtar_dT(const QDateTime value)
{    girtar_dT = value; }

QDateTime IEcard::getCiktar_dT() const
{    return ciktar_dT; }
void IEcard::setCiktar_dT(const QDateTime value)
{    ciktar_dT = value; }


QString IEcard::getY1_sT() const
{    return y1_sT; }
void IEcard::setY1_sT(const QString value)
{    y1_sT = value; }

QString IEcard::getY2_sT() const
{     return y2_sT; }
void IEcard::setY2_sT(const QString value)
{    y2_sT = value; }

QPixmap IEcard::getIemkn_pX() const
{    return iemkn_pX; }
void IEcard::setIemkn_pX(const QPixmap value)
{    iemkn_pX = value; }

QPixmap IEcard::getIe_pX() const
{    return ie_pX; }
void IEcard::setIe_pX(const QPixmap value)
{    ie_pX = value; }

QPoint IEcard::getIepos_pT() const
{    return iepos_pT; }
void IEcard::setIepos_pT(const QPoint value)
{    iepos_pT = value; }



void IEcard::mdia(QString baslik, QPixmap iemkn_pX, QPixmap ie_pX)
{

    auto *dkia = new QDialog();
    dkia->setModal (true);
    dkia->setGeometry ( 50, 300, 400, 200 );
    dkia->setWindowTitle ( baslik );

    QLabel xxx1("pixmap mkn",this);
    QLabel xxx10(this);
    xxx10.setPixmap (iemkn_pX);

    QLabel xxx2("pixmap ie",this);
    QLabel xxx20(this);
    xxx20.setPixmap (ie_pX);
    ////////////////////////////////////////////************
    auto *layout = new QGridLayout;
    dkia->setLayout (layout);
    layout->addWidget (&xxx1   ,0 ,0 );
    layout->addWidget (&xxx10  ,0 ,1 );
    layout->addWidget (&xxx2   ,1 ,0 );
    layout->addWidget (&xxx20  ,1 ,1 );
    dkia->exec ();
}




//QDataStream &operator <<(QDataStream &streamGotFromObject,
//                         const IEcard &IEcard)
//{


//    streamGotFromObject << IEcard.getIeno_nT ()
//                        << IEcard.getKurumno_sT ()
//                        << IEcard.getTarih_dT()
//                        << IEcard.getDurum_sT()
//                        << IEcard.getGirtar_dT()
//                        << IEcard.getCiktar_dT()
//                        << IEcard.getY1_sT()
//                        << IEcard.getY2_sT()
//                        << IEcard.getIemkn_pX()
//                        << IEcard.getIe_pX()
//                        << IEcard.getIepos_pT();


///*
//    auto *dia = new QDialog();
//    dia->setModal (true);
//    dia->setGeometry ( 50, 300, 400, 200 );
//    dia->setWindowTitle ( "<< içinde IEcard.getIemkn_pX()-------"+IEcard.getIeno_nT () );

//    QLabel xxx1("pixmap mkn");
//    QLabel xxx10;
//    xxx10.setPixmap (IEcard.getIemkn_pX());

//    QLabel xxx2("pixmap ie");
//    QLabel xxx20;
//    xxx20.setPixmap (IEcard.getIe_pX());
//    ///////////////////////////////////////////
//    auto *layout = new QGridLayout;
//    dia->setLayout (layout);
//    layout->addWidget (&xxx1   ,0 ,0 );
//    layout->addWidget (&xxx10  ,0 ,1 );
//    layout->addWidget (&xxx2   ,1 ,0 );
//    layout->addWidget (&xxx20  ,1 ,1 );
//    dia->exec ();

//*/


//    return streamGotFromObject;


//}

//QDataStream &operator >>(QDataStream
//                         &streamSentToObject, IEcard &IEcard)
//{

//    int ieno_nTx;
//    QString kurumno_sTx;
//    QDateTime tarih_dTx ;
//    QString durum_sTx ;
//    QDateTime girtar_dTx ;
//    QDateTime ciktar_dTx ;
//    QString y1_sTx ;
//    QString y2_sTx ;
//    QPixmap iemkn_pXx;
//    QPixmap ie_pXx;
//    QPoint iepos_pTx;

//    streamSentToObject
//            >> ieno_nTx
//            >> kurumno_sTx
//            >> tarih_dTx
//            >> durum_sTx
//            >> girtar_dTx
//            >> ciktar_dTx
//            >> y1_sTx
//            >> y2_sTx
//            >> iemkn_pXx
//            >> ie_pXx
//            >> iepos_pTx;


//    IEcard.setIeno_nT (ieno_nTx);
//    IEcard.setKurumno_sT (kurumno_sTx);
//    IEcard.setTarih_dT   ( tarih_dTx   ) ;
//    IEcard.setDurum_sT   ( durum_sTx   ) ;
//    IEcard.setGirtar_dT  ( girtar_dTx  ) ;
//    IEcard.setCiktar_dT  ( ciktar_dTx  ) ;
//    IEcard.setY1_sT      ( y1_sTx      ) ;
//    IEcard.setY2_sT      ( y2_sTx      ) ;
//    IEcard.setIemkn_pX   ( iemkn_pXx   ) ;
//    IEcard.setIe_pX      ( ie_pXx      ) ;
//    IEcard.setIepos_pT   ( iepos_pTx   ) ;


///*
//    auto *dia = new QDialog();
//    dia->setModal (true);
//    dia->setGeometry ( 50, 300, 400, 200 );
//    dia->setWindowTitle ( " >> içinde IEcard.getIemkn_pX()" );

//    QLabel xxx1("pixmap mkn");
//    QLabel xxx10;
//    xxx10.setPixmap (IEcard.getIemkn_pX());

//    QLabel xxx2("pixmap ie");
//    QLabel xxx20;
//    xxx20.setPixmap (IEcard.getIe_pX());
//    /////////////////////////////////////////
//    auto *layout = new QGridLayout;
//    dia->setLayout (layout);
//    layout->addWidget (&xxx1   ,0 ,0 );
//    layout->addWidget (&xxx10  ,0 ,1 );
//    layout->addWidget (&xxx2   ,1 ,0 );
//    layout->addWidget (&xxx20  ,1 ,1 );
//    dia->exec ();
//*/

//    return streamSentToObject;

//}




/*QFile file("isemri"+QString::number (ieno_nT)+".dat");
if (!file.open(QIODevice::WriteOnly)) {

    QMessageBox::information(this,"İş Emri Kartı Dosya "
                                  "Yazma Hatası: "+file.fileName (),
                             "HATA - İş Emri Kartı Dosyaya Yazılamıyor !\n"
                             + file.errorString());
    return;
}

/// iş emri bilgileri dosyaya yazılıyor
/// bu bilgiler iş emri objeleri oluşturulurken
/// tekrar dosyadan okunur
QDataStream out(&file);
out.setVersion(QDataStream::Qt_4_3);
out << int       ( ieno_nT   )
    << QString   ( kurumno_sT)
    << QDateTime ( tarih_dT  )
    << QString   ( durum_sT  )
    << QDateTime ( girtar_dT )
    << QDateTime ( ciktar_dT )
    << QString   ( y1_sT     )
    << QString   ( y2_sT     )
    << QPixmap   ( iemkn_pX  )
    << QPixmap   ( ie_pX     )
    << QPoint    ( iepos     ) ;
*/


/*
QFile file("isemri"+QString::number (ieno_nT)+".dat");
if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Cannot open file for reading: "
             << qPrintable(file.errorString()) << endl;
    return;
}
*/

//    int ieno_nT;
//    QString kurumno_sT ;
//    QDateTime tarih_dT ;
//    QString durum_sT ;
//    QDateTime girtar_dT ;
//    QDateTime ciktar_dT ;
//    QString y1_sT ;
//    QString y2_sT ;
//    QPixmap iemkn_pX;
//    QPixmap ie_pX;
//    QPoint iepos_pT;

/*
QDataStream in(&file);
in.setVersion(QDataStream::Qt_4_3);
/// yeni kart bilgileri objeye
in  >> ieno_nT
        >> kurumno_sT
        >> tarih_dT
        >> durum_sT
        >> girtar_dT
        >> ciktar_dT
        >> y1_sT
        >> y2_sT
        >> iemkn_pX
        >> ie_pX
        >> iepos_pT ;
*/
