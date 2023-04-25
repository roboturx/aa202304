#include "hsap/hsp_main_tree.h"
#include "hsap/hc_hspadd.h"
#include "hsap/cm_dlg_richtxt.h"


namespace {

const int StatusTimeout = AQP::MSecPerSecond * 10;
const QString FilenameSetting("Filename");
const QString GeometrySetting("Geometry");
const QString CurrentTaskPathSetting("CurrentTaskPath");
const int FirstFrame = 0;
const int LastFrame = 4;


QAction *createAction(const QString &icon,
                      const QString &text,
                      QMainWindow *parent,
                      const QKeySequence &shortcut=QKeySequence())
{
    QAction *action = new QAction(QIcon(icon), text, parent);
    if (!shortcut.isEmpty())
        action->setShortcut(shortcut);
    return action;
}

} // anonymous namespace


hsp_Main_Tree::hsp_Main_Tree(QWidget * parent)
    : QMainWindow()
    ,
      #ifndef CUSTOM_MODEL
      timedItem(0),
      #endif
      currentIcon(0)
{
    qDebug ()<<"        Constructor hsp_Main_Tree **************************";

    createModelViewDelegate();
    createGui();
    createActions();
    createMenusAndToolBar();
    createConnections();

    AQP::accelerateMenu(menuBar());
    setWindowTitle(tr("%1 (Hesap Dosyası)[*]")
                   .arg(QApplication::applicationName()));

    statusBar()->showMessage(tr("Uygulama Hazır"), StatusTimeout);

    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    iconTimeLine.setEasingCurve (QEasingCurve::InOutQuad);


    QCoreApplication::setOrganizationName("aaSoft");
    QCoreApplication::setOrganizationDomain("roboturx@gmail.com");
    QCoreApplication::setApplicationName("EVREN 23.4.1");


    QSettings settings;

    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();

    qDebug()<<"Ana Hesap dosyası kontrol ediliyor...";

    if (filename.isEmpty()  )
    {
        /// Dosya adı XML de yok
        /// yeni dosya oluştur ve
        /// XMl e dosya adınıda kaydet
        ///
        /// filenew

        qDebug()<<"Ana Hesap Dosya Kaydı Hiç Yok ... ";
        qDebug() << "       Yeni Dosya oluşturuluyor...";

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
    else
    {
        /// Dosya adı XML de var ve
        /// Dosya disk te bulundu
        ///
        /// load

        qDebug()<<"Ana Hesap Dosyası Diskte bulundu... ";
        qDebug() << "                     Yükleniyor...";

        QMetaObject::invokeMethod(this, "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, filename),
                                  Q_ARG(QStringList, settings.value(
                                            CurrentTaskPathSetting).toStringList()));

    }

    /// Dosya adı XML de VAR AMA
    /// XML de belirtildiği yerde dosya bulunamdı
    /// yeni dosya oluştur ve
    /// XMl e dosya adınıda kaydet
    ///
    /// fileNew

    if (! QFile::exists(filename))
    {
        qDebug()<<"Dosya Adı : "<< filename
                 <<" :"<<QFile::exists(filename);
        qDebug()<<"Kayıtlı Hesap Dosyası Diskte bulunamadı !! ";
        qDebug() << "       Yeni Hesap Dosyası oluşturuluyor...";

        statusBar()->showMessage(tr("Yeni Dosya Oluşturuluyor... %1")
                                 .arg(filename), StatusTimeout);

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }

}

hsp_Main_Tree::~hsp_Main_Tree()
{
//    qDebug()<<"Destructor hsp_main_tree ----------- ~ :"
//             << " filename               : " << modelXML->filename()
//             << " pathforindex (curindex): " << modelXML->pathForIndex(hsp_ViewXML_mainTree->currentIndex());
    stopTiming();

    QSettings settings;
    settings.setValue(GeometrySetting, saveGeometry());
    settings.setValue(FilenameSetting, modelXML->filename());
    settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(hsp_ViewXML_mainTree->currentIndex()));


    qDebug() <<"hsp_main_tree   ~    destructor : settings.filename "<< settings.fileName();

}

TaskItem* hsp_Main_Tree::getCurrentItem()
{
    qDebug()<<"hsp_main_tree :: getcurrentitem";
    TaskItem* currentHesap = static_cast<TaskItem*>
            (hsp_ViewXML_mainTree->currentIndex().internalPointer());
    //        if ( currentItem)
    //        {
    //            qDebug() << "               ui hsp::getcurrentItem" ;
    //            qDebug() << "               :kod:" << currentItem->hesapKod ()
    //                     << "               :ad :" << currentItem->hesapAd ()
    //                     << "               :tpl:" << QString::number(currentItem->isTopluHesap())
    //                     << "               :tur:" << currentItem->hesapTuru()
    //                     << "               :ust:" << currentItem->ustHesap()
    //                     << "               ui currentItem" ;
    //        }
    return  currentHesap;


}

/// 100-01
///
void hsp_Main_Tree::createModelViewDelegate()
{
    qDebug()<<"hsp_main_tree :: MVC";

    hsp_ViewXML_mainTree = new QTreeView;
    modelXML    = new hsp_mainTree_XMLmodel(this);

    hsp_ViewXML_mainTree->setDragDropMode(QAbstractItemView::InternalMove);

#ifdef MODEL_TEST
    (void) new ModelTest(modelXML, this);
#endif

    // kod kolonunu gizle
    hsp_ViewXML_mainTree->setColumnHidden(1,true);
    hsp_ViewXML_mainTree->setAllColumnsShowFocus(false);
    hsp_ViewXML_mainTree->setAnimated (true);
    hsp_ViewXML_mainTree->setAutoExpandDelay (100);
    hsp_ViewXML_mainTree->setIndentation (16);
    hsp_ViewXML_mainTree->setSelectionBehavior (QAbstractItemView::SelectItems);
    hsp_ViewXML_mainTree->setSelectionMode (QAbstractItemView::SingleSelection);


    // xx ile gönderilen renk kodu column 0 için text rengi olur
//    int xx= {0x00ff00};
//    cL_dlG_ColmColor *clmColor =
//        new cL_dlG_ColmColor(xx,hsp_ViewXML_mainTree->currentIndex (),this);

//    hsp_ViewXML_mainTree->setItemDelegateForColumn(0, clmColor);

    hsp_ViewXML_mainTree->setItemDelegateForColumn(1, new cm_dlG_RichTxt);
    hsp_ViewXML_mainTree->setItemDelegateForColumn(3, new cm_dlG_cb_hTur);
    hsp_ViewXML_mainTree->setModel(modelXML);

    lB_Hesap = new QLabel("Kod-------");

}



void hsp_Main_Tree::createGui()
{

    QWidget *page0 = new QWidget(this);
    QVBoxLayout *layout0 = new QVBoxLayout(page0);

    layout0->addWidget(hsp_ViewXML_mainTree);
    layout0->addWidget(lB_Hesap   );

    /// central widget
    wdgt_central = new QWidget;
    setCentralWidget(page0);

}




void hsp_Main_Tree::createActions()
{
    qDebug()<<"-----------    ::hChsp createActions";
    fileNewAction = createAction(":/rsm/images/filenew.png",
                                 tr("Yeni Hesap Dosyası"),
                                 this, QKeySequence::New);
    fileOpenAction = createAction(":/rsm/images/fileopen.png",
                                  tr("Hesap Dosyası Aç..."),
                                  this, QKeySequence::Open);
    fileSaveAction = createAction(":/rsm/images/filesave.png",
                                  tr("Kaydet"),
                                  this, QKeySequence::Save);
    fileSaveAsAction = createAction(":/rsm/images/filesave.png",
                                    tr("Farklı Kaydet..."), this
                                #if QT_VERSION >= 0x040500
                                    , QKeySequence::SaveAs
                                #endif
                                    );
    fileQuitAction = createAction(":/rsm/images/filequit.png",
                                  tr("Çıkış"), this);
#if QT_VERSION >= 0x040600
    fileQuitAction->setShortcuts(QKeySequence::Quit);
#else
    fileQuitAction->setShortcut(QKeySequence("Ctrl+Q"));
#endif
    editAddAction = createAction(":/rsm/images/editadd.png",
                                 tr("Hesap Ekle..."),
                                 this, QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/rsm/images/editdelete.png",
                                    tr("Hesap Sil..."),
                                    this, QKeySequence::Delete);

    editCutAction = createAction(":/rsm/images/editcut.png", tr("Kes"),
                                 this, QKeySequence::Cut);
    editPasteAction = createAction(":/rsm/images/editpaste.png", tr("Yapıştır"),
                                   this, QKeySequence::Paste);
    editMoveUpAction = createAction(":/rsm/images/editup.png", tr("Hesap Yukarı"),
                                    this, QKeySequence(tr("Ctrl+Up")));
    editMoveDownAction = createAction(":/rsm/images/editdown.png",
                                      tr("Hesap Aşağı"), this, QKeySequence(tr("Ctrl+Down")));
    editPromoteAction = createAction(":/rsm/images/editpromote.png",
                                     tr("Üst Hesap Yap"), this, QKeySequence(tr("Ctrl+Left")));
    editDemoteAction = createAction(":/rsm/images/editdemote.png",
                                    tr("Alt Hesap Yap"), this, QKeySequence(tr("Ctrl+Right")));

    editStartOrStopAction = createAction(":/rsm/images/0.png", tr("S&tart"),
                                         this, QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Kapalı Hesaplaı Gizle"),
                                                this);
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}


void hsp_Main_Tree::createMenusAndToolBar()
{
    qDebug()<<"-----------    ::hChsp createMenusAndToolBar";

    /*QMenu **/fileMenu = menuBar()->addMenu(tr("Dosya"));
    /*QToolBar **/fileToolBar = addToolBar(tr("Dosya"));
    fileToolBar->setAllowedAreas (Qt::LeftToolBarArea);

    foreach (QAction *action, QList<QAction*>() << fileNewAction
             << fileOpenAction << fileSaveAction << fileSaveAsAction)
    {
        fileMenu->addAction(action);
        if (action != fileSaveAsAction)
            fileToolBar->addAction(action);
        if (action == fileSaveAction || action == fileSaveAsAction)
            action->setEnabled(false);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAction);

    QAction *emptyAction = 0;
    QMenu *editMenu = menuBar()->addMenu(tr("Düzen"));
    QToolBar *editToolBar = addToolBar(tr("Düzen"));
    editToolBar->setAllowedAreas (Qt::LeftToolBarArea);

    foreach (QAction *action, QList<QAction*>() << editAddAction
             << editDeleteAction << emptyAction
             << editCutAction << editPasteAction << emptyAction
             << editMoveUpAction << editMoveDownAction
             << editPromoteAction << editDemoteAction << emptyAction
             << editStartOrStopAction << editHideOrShowDoneTasksAction)

    {
        if (action == emptyAction) {
            editMenu->addSeparator();
            editToolBar->addSeparator();
            continue;
        }
        if (action != editHideOrShowDoneTasksAction)
            editToolBar->addAction(action);
        else
            editMenu->addSeparator();
        editMenu->addAction(action);
    }
}


void hsp_Main_Tree::createConnections()
{
    qDebug()<<"-----------    ::hChsp createConnections";
    connect(hsp_ViewXML_mainTree->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this, &hsp_Main_Tree::updateUi);

    connect(hsp_ViewXML_mainTree->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &hsp_Main_Tree::updateUi);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customContextMenuRequested(QPoint)));

    connect(modelXML,
            SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(setDirty()));

    connect(modelXML, SIGNAL(stopTiming()), this,
            SLOT(stopTiming()));


    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));

  //  connect(modelXML, &cm_TreeXML::);

    QHash<QAction*, QString> slotForAction;
    slotForAction[fileNewAction] = SLOT(fileNew());
    slotForAction[fileOpenAction] = SLOT(fileOpen());
    slotForAction[fileSaveAction] = SLOT(fileSave());
    slotForAction[fileSaveAsAction] = SLOT(fileSaveAs());
    slotForAction[fileQuitAction] = SLOT(close());
    slotForAction[editAddAction] = SLOT(editAdd());
    slotForAction[editDeleteAction] = SLOT(editDelete());

    slotForAction[editCutAction] = SLOT(editCut());
    slotForAction[editPasteAction] = SLOT(editPaste());
    slotForAction[editMoveUpAction] = SLOT(editMoveUp());
    slotForAction[editMoveDownAction] = SLOT(editMoveDown());
    slotForAction[editPromoteAction] = SLOT(editPromote());
    slotForAction[editDemoteAction] = SLOT(editDemote());

    QHashIterator<QAction*, QString> i(slotForAction);
    while (i.hasNext()) {
        i.next();
        connect(i.key(), SIGNAL(triggered()),
                this, qPrintable(i.value()));
    }

    connect(editStartOrStopAction, SIGNAL(triggered(bool)),
            this, SLOT(editStartOrStop(bool)));
    connect(editHideOrShowDoneTasksAction, SIGNAL(triggered(bool)),
            this, SLOT(editHideOrShowDoneTasks(bool)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon(int)));
    qDebug() << "                  kntrl son";
}


void hsp_Main_Tree::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(fileNewAction);
    menu.addAction(fileOpenAction);
    menu.addAction(fileSaveAction);
    menu.exec(event->globalPos());
}

void hsp_Main_Tree::customContextMenuRequested(
        const QPoint &pos)
{
    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}



///////////////////////////***************************************
void hsp_Main_Tree::updateUi()
{
    qDebug()<<"-----------    ::hChsp updateUi..."
           <<modelXML->rowCount();
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = hsp_ViewXML_mainTree->currentIndex().isValid();

    //modelXML->getListXML ();

    foreach (QAction *action, QList<QAction*>()
             << editDeleteAction
             << editMoveUpAction << editMoveDownAction
             << editCutAction
             << editPromoteAction << editDemoteAction)

        action->setEnabled(enable);

    editStartOrStopAction->setEnabled(rows);
    editPasteAction->setEnabled(modelXML->hasCutItem());


    qDebug()<<" upt ui taskitem";

    /// tree deki mevcut indexi internalpointer ile belirleyelim
    TaskItem* currentItem = static_cast<TaskItem*>
            (hsp_ViewXML_mainTree->currentIndex().internalPointer());
    if ( currentItem)
    {
        ///
        ///  mevcut hesap tüm evrene yayılsın
        ///

        emit sgnHesap (currentItem );

        ///
        /// hesap değiştiğinde detaylarda değişsin
        ///
        ///

        lB_Hesap->setText(QString::number(currentItem->hesapKod()) +" : "+
                          currentItem->parent()->hesapAd ()+" - "+
                          currentItem->hesapAd() +" - "+
                          currentItem->hesapAcklm ()+" : "+
                          QString::number(currentItem->isTopluHesap() ) +" : "+
                          currentItem->hesapTuru() +" : "+
                          currentItem->DBFile()
                          );
    }
    qDebug()<<" upt ui taskitem";
}






void hsp_Main_Tree::setCurrentIndex(const QModelIndex &index)
{
    //qDebug()<<"-----------    ::hChsp setcurindx";
    if (index.isValid()) {
        hsp_ViewXML_mainTree->scrollTo(index);
        hsp_ViewXML_mainTree->setCurrentIndex(index);
    }
}



////////////// E D I T S //////////////////////////////////////////////
///
///



void hsp_Main_Tree::editAdd()
{
   qDebug()<<"-----------    ::hChsp editAdd Yeni Hesap Ekleniyor...............";

   hC_hspAdd* ekle = new hC_hspAdd;
   ekle->show ();

   QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
    if (modelXML->insertRows(0, 1, index))
    {
        index = modelXML->index(0, 0, index);
        setCurrentIndex(index);
        //hsp_ViewXML_mainTree->edit(index);

        //TaskItem * yeniItem = new TaskItem;
        TaskItem  yeniItem ;
        yeniItem = *ekle->yeni();

        TaskItem * Item = getCurrentItem ();
        Item->setHesapAd (yeniItem.hesapAd ())  ;
        Item->setHesapAcklm (yeniItem.hesapAcklm ())  ;
        Item->setTopluHesap (yeniItem.isTopluHesap ())  ;
        Item->setHesapTuru (yeniItem.hesapTuru ())  ;
        Item->setUstHesap (yeniItem.ustHesap ())  ;
        Item->setDBFile (yeniItem.DBFile ())  ;
        setDirty();
        updateUi();
   // delete yeniItem;
    }

}



void hsp_Main_Tree::editDelete()
{
    //qDebug()<<"-----------    ::hChsp editDelete";
    //qDebug() << "editdelete";
    QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
    if (!index.isValid())
        return;

    QString name = modelXML->data(index).toString();
    int rows = modelXML->rowCount(index);
    if (modelXML->isTimedItem(index))
        stopTiming();
qDebug()<<"--edit delete 01";
    QString message;
    if (rows == 0)
        message = tr("<p>HESAP SİL '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>HESAP SİL '%1' ve alt hesabı (ve "
                     "alt hesaba bağlı hesaplar)").arg(name);
    else if (rows > 1)
        message = tr("<p>HESAP SİL '%1' ve ona bağlı %2 alt hesap "
                     "(ve alt hesaplara bağlı hesaplar)").arg(name).arg(rows);
    if (!AQP::okToDelete(this, tr("Delete"), message))
        return;
    qDebug()<<"--edit delete 02";
    modelXML->removeRow(index.row(), index.parent());
    qDebug()<<"--edit delete 03";
    setDirty();
    qDebug()<<"--edit delete 04";
    updateUi();
    qDebug()<<"--edit delete s0n";
}




void hsp_Main_Tree::editCut()
{
    qDebug()<<"-----------    ::hChsp editCut";
    QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}


void hsp_Main_Tree::editPaste()
{
    qDebug()<<"-----------    ::hChsp editpaste";
    setCurrentIndex(modelXML->paste(hsp_ViewXML_mainTree->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hsp_Main_Tree::editMoveUp()
{
    qDebug()<<"-----------    ::hChsp editmoveup";
    hsp_ViewXML_mainTree->setCurrentIndex(
                modelXML->moveUp(hsp_ViewXML_mainTree->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hsp_Main_Tree::editMoveDown()
{
    qDebug()<<"-----------    ::hChsp editmovedown";

    hsp_ViewXML_mainTree->setCurrentIndex(
                modelXML->moveDown(hsp_ViewXML_mainTree->currentIndex()));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hsp_Main_Tree::editPromote()
{
    qDebug()<<"-----------    ::hChsp editPromote";
    QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}


void hsp_Main_Tree::editDemote()
{

    qDebug()<<"-----------    ::hChsp editDemote";
    QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    hsp_ViewXML_mainTree->setCurrentIndex(modelXML->demote(index));
    editHideOrShowDoneTasks(
                editHideOrShowDoneTasksAction->isChecked());
}




//////////// X M L  F I L E  O P E R A T I O N S ////////////////////
///
///
///




bool hsp_Main_Tree::okToClearData()
{
   // qDebug()<<"-----------    ::hChsp OkToClearData";
    if (isWindowModified())
        return AQP::okToClearData(&hsp_Main_Tree::fileSave, this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}



void hsp_Main_Tree::fileNew()
{
   // qDebug()<<"-----------    ::hChsp filenew XML";

    if (!okToClearData())
        return;
    modelXML->clear();
    modelXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - İsimsiz hesap dosyası[*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}


void hsp_Main_Tree::fileOpen()
{
   // qDebug()<<"-----------    ::hChsp fileOpen XML";
    //qDebug() << "fileopen";
    if (!okToClearData())
        return;
    QString filename = modelXML->filename();
    QString dir(filename.isEmpty() ? QString(".")
                                   : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
                                            tr("%1 - Open").arg(QApplication::applicationName()),
                                            dir, tr("konumlar (*.knm)"));
    if (!filename.isEmpty())
        load(filename);
}


void hsp_Main_Tree::load(const QString &filename,
                  const QStringList &taskPath)
{
   // qDebug()<<"-----------    ::hChsp load XML";
    qDebug() << "loading file (filename) '" << filename
             << " ' at path (taskPath): " << taskPath;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    try {
        modelXML->load(filename);
        if (!taskPath.isEmpty())
        {
            setCurrentIndex(modelXML->indexForPath(taskPath));
        }
        for (int column = 0;
             column < modelXML->columnCount();
             ++column)
        {
            //  hsp_ViewXML_mainTree->resizeColumnToContents(column);
            hsp_ViewXML_mainTree->setColumnWidth (0,200);
            hsp_ViewXML_mainTree->setColumnWidth (1,100);
            hsp_ViewXML_mainTree->setColumnWidth (2,50);
            hsp_ViewXML_mainTree->setColumnWidth (3,100);
            hsp_ViewXML_mainTree->setColumnWidth (4,400);

        }
        hsp_ViewXML_mainTree->setMinimumWidth (50);
        hsp_ViewXML_mainTree->header()->setStretchLastSection(false);
        hsp_ViewXML_mainTree->setColumnHidden (5,true);
        hsp_ViewXML_mainTree->setAllColumnsShowFocus (false);
        hsp_ViewXML_mainTree->setIndentation (10);


        setDirty(false);

        setWindowTitle(tr("%1 - %2[*]")
                       .arg(QApplication::applicationName(),
                            QFileInfo(filename).fileName()));

        statusBar()->showMessage(tr("%1 yüklendi").arg(filename),
                                 StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("HATA"), tr("Yüklemede Hata %1: %2\n"
                                          "yeni dosya oluşturuluyor")
                     .arg(filename,QString::fromUtf8(error.what())));


    }
    updateUi();
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
    hsp_ViewXML_mainTree->setFocus();
    QApplication::restoreOverrideCursor();

}



bool hsp_Main_Tree::fileSave()
{
    qDebug()<<"-----------    ::hChsp fileSave XML";
    // qDebug() << "filesave";
    bool saved = false;
    if (modelXML->filename().isEmpty())
        saved = fileSaveAs();
    else {
        try {
            modelXML->save();
            setDirty(false);
            setWindowTitle(tr("%1 - %2[*]")
                           .arg(QApplication::applicationName())
                           .arg(QFileInfo(modelXML->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                                     .arg(modelXML->filename()), StatusTimeout);
            saved = true;
        } catch (AQP::Error &error) {
            AQP::warning(this, tr("Error"),
                         tr("Failed to save %1: %2").arg(modelXML->filename(),/*)
                         .arg(*/QString::fromUtf8(error.what())));
        }
    }
    updateUi();
    return saved;
}


bool hsp_Main_Tree::fileSaveAs()
{
    qDebug()<<"-----------    ::hChsp fileSaveAs XML";
    // qDebug() << "filesaveas";
    QString filename = modelXML->filename();
    QString dir = filename.isEmpty() ? "."
                                     : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
                                            tr("%1 - Save As").arg(QApplication::applicationName()),
                                            dir,
                                            tr("%1 (*.knm)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".knm"))
        filename += ".knm";
    modelXML->setFilename(filename);
    return fileSave();
}





//////////////////// O T H E R S /////////////////////////////////
///
///
///
///

void hsp_Main_Tree::closeEvent(QCloseEvent *event)
{
    qDebug()<<"-----------    ::hChsp closeEvent---------------------------"
           << " filename               : " << modelXML->filename()
           << " pathforindex (curindex): " << modelXML->pathForIndex(hsp_ViewXML_mainTree->currentIndex());
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, modelXML->filename());
        settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(hsp_ViewXML_mainTree->currentIndex()));

        qDebug() <<"        close -> settings.filename "<< settings.fileName();
        event->accept();
    }
    else
        event->ignore();
}




////////////////// T A S K S ////////////////////////////////////////////////
///
///



void hsp_Main_Tree::stopTiming()
{
    qDebug()<<"-----------    ::hChsp stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}



void hsp_Main_Tree::editStartOrStop(bool start)
{
    qDebug()<<"-----------    ::hChsp editStartOrStop";
    timer.stop();
    iconTimeLine.stop();
    if (start) { // start the clock iff there's a current task
        QModelIndex index = hsp_ViewXML_mainTree->currentIndex();
        if (!index.isValid()) {
            editStartOrStopAction->setChecked(false);
            start = false;
        }
        else {
            QIcon icon(":/0.png");
            QDateTime now = QDateTime::currentDateTime();

            modelXML->setTimedItem(index);
            modelXML->addDateTimeToTimedItem(now, now);
            modelXML->setIconForTimedItem(icon);

            editStartOrStopAction->setIcon(icon);

            // qt 6 timedTime.restart();
            timer.start();
            iconTimeLine.start();
        }
    }
    else
    { // stop the clock
        timeout(); // update to now

        modelXML->setIconForTimedItem();
        modelXML->clearTimedItem();
        editStartOrStopAction->setIcon(QIcon(":/rsm/images/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top")
                                         : tr("S&tart"));
    editStartOrStopAction->setIcon(QIcon(start ? tr(":/rsm/images/4.png")
                                               : tr(":/rsm/images/0.png")));
}


void hsp_Main_Tree::timeout()
{
    qDebug()<<"-----------    ::hChsp timeout";
    modelXML->incrementEndTimeForTimedItem(timer.remainingTime ());
    timer.start ();
}


void hsp_Main_Tree::updateIcon(int frame)
{
    qDebug()<<"-----------    ::hChsp updateIcon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}


void hsp_Main_Tree::editHideOrShowDoneTasks(bool hide)
{
    // qDebug()<<"-----------    ::hChsp edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}


void hsp_Main_Tree::hideOrShowDoneTask(bool hide,
                                const QModelIndex &index)
{
    // qDebug()<<"-----------    ::hChsp hideorshowdntsk";
    bool hideThisOne = hide && modelXML->isChecked(index);
    if (index.isValid())
        hsp_ViewXML_mainTree->setRowHidden(index.row(), index.parent(),
                                  hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelXML->index(row, 0, index));
    }
}




/////////////////////////////////////////////////////////////////
///// \brief The cL_HesapListesi class
///// xml dosyasından hesap adları ve renklerini
///// qpair olarak veren sınıf


//cL_HesapListesi::PairHesapColor cL_HesapListesi::getHesapListesi(QString hangihesaplar)
//{

//    setHesapListesi( hangihesaplar);
//    return qp_hesapListesi;
//}

//cL_HesapListesi::PairHesapColor cL_HesapListesi::setHesapListesi(QString hangiListe)
//{
//    // set
//    if (hangiListe == "")
//    {
//    }
//    else if (hangiListe == "")
//    {

//    }

//    return qp_hesapListesi;
//}
