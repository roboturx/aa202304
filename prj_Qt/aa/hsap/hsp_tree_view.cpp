#include "hsap/hsp_tree_view.h"
#include "hsap/cm_dlg_richtxt.h"
#include "hsap/hsp_add.h"

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
                      const QKeySequence &shortcut = QKeySequence())
{
    QAction *action = new QAction(QIcon(icon), text, parent);
    if (!shortcut.isEmpty())
        action->setShortcut(shortcut);
    return action;
}

} // anonymous namespace

hsp_Tree_view::hsp_Tree_view(QWidget *parent)
    : QMainWindow()
    ,
#ifndef CUSTOM_MODEL
    timedItem(0)
    ,
#endif
    currentIcon(0)
{
    qDebug() << "        Constructor hsp_Tree_view **************************";

    createModelViewDelegate();
    createGui();
    createActions();
    createMenusAndToolBar();
    createConnections();

    AQP::accelerateMenu(menuBar());
    setWindowTitle(tr("%1 (Hesap Dosyası)[*]").arg(QApplication::applicationName()));

    statusBar()->showMessage(tr("Uygulama Hazır"), StatusTimeout);

    timer.setInterval(333);
    iconTimeLine.setDuration(5000);
    iconTimeLine.setFrameRange(FirstFrame, LastFrame + 1);
    iconTimeLine.setLoopCount(0);
    iconTimeLine.setEasingCurve(QEasingCurve::InOutQuad);

    QCoreApplication::setOrganizationName("aaSoft");
    QCoreApplication::setOrganizationDomain("roboturx@gmail.com");
    QCoreApplication::setApplicationName("EVREN 23.4.1");

    QSettings settings;

    restoreGeometry(settings.value(GeometrySetting).toByteArray());
    QString filename = settings.value(FilenameSetting).toString();

    qDebug() << "Ana Hesap dosyası kontrol ediliyor...";

    if (filename.isEmpty()) {
        /// Dosya adı XML de yok
        /// yeni dosya oluştur ve
        /// XMl e dosya adınıda kaydet
        ///
        /// filenew

        qDebug() << "Ana Hesap Dosya Kaydı Hiç Yok ... ";
        qDebug() << "       Yeni Dosya oluşturuluyor...";

        QTimer::singleShot(0, this, SLOT(fileNew()));
    } else {
        /// Dosya adı XML de var ve
        /// Dosya disk te bulundu
        ///
        /// load

        qDebug() << "Ana Hesap Dosyası Diskte bulundu... ";
        qDebug() << "                     Yükleniyor...";

        QMetaObject::invokeMethod(this,
                                  "load",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, filename),
                                  Q_ARG(QStringList,
                                        settings.value(CurrentTaskPathSetting).toStringList()));
    }

    /// Dosya adı XML de VAR AMA
    /// XML de belirtildiği yerde dosya bulunamdı
    /// yeni dosya oluştur ve
    /// XMl e dosya adınıda kaydet
    ///
    /// fileNew

    if (!QFile::exists(filename)) {
        qDebug() << "Dosya Adı : " << filename << " :" << QFile::exists(filename);
        qDebug() << "Kayıtlı Hesap Dosyası Diskte bulunamadı !! ";
        qDebug() << "       Yeni Hesap Dosyası oluşturuluyor...";

        statusBar()->showMessage(tr("Yeni Dosya Oluşturuluyor... %1").arg(filename), StatusTimeout);

        QTimer::singleShot(0, this, SLOT(fileNew()));
    }
}

hsp_Tree_view::~hsp_Tree_view()
{
    //    qDebug()<<"Destructor hsp_Tree_view ----------- ~ :"
    //             << " filename               : " << modelXML->filename()
    //             << " pathforindex (curindex): " << modelXML->pathForIndex(hsp_Tree_ViewXML->currentIndex());
    stopTiming();

    QSettings settings;
    settings.setValue(GeometrySetting, saveGeometry());
    settings.setValue(FilenameSetting, modelXML->filename());
    settings.setValue(CurrentTaskPathSetting,
                      modelXML->pathForIndex(hsp_Tree_ViewXML->currentIndex()));

    qDebug() << "hsp_Tree_view   ~    destructor : settings.filename " << settings.fileName();
}

HesapItem *hsp_Tree_view::getCurrentItem()
{
    qDebug() << "hsp_Tree_view :: getcurrentitem";
    HesapItem *currentHesap = static_cast<HesapItem *>(
        hsp_Tree_ViewXML->currentIndex().internalPointer());
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
    return currentHesap;
}

/// 100-01
///
void hsp_Tree_view::createModelViewDelegate()
{
    qDebug() << "hsp_Tree_view :: MVC";

    hsp_Tree_ViewXML = new QTreeView;
    modelXML = new hsp_Tree_model_XML(this);

    hsp_Tree_ViewXML->setDragDropMode(QAbstractItemView::InternalMove);

#ifdef MODEL_TEST
    (void) new ModelTest(modelXML, this);
#endif

    // kod kolonunu gizle
    ///  hsp_Tree_ViewXML->setColumnHidden(1,true);
    hsp_Tree_ViewXML->setAllColumnsShowFocus(false);
    hsp_Tree_ViewXML->setAnimated(true);
    hsp_Tree_ViewXML->setAutoExpandDelay(100);
    hsp_Tree_ViewXML->setIndentation(16);
    hsp_Tree_ViewXML->setSelectionBehavior(QAbstractItemView::SelectItems);
    hsp_Tree_ViewXML->setSelectionMode(QAbstractItemView::SingleSelection);

    // xx ile gönderilen renk kodu column 0 için text rengi olur
    //    int xx= {0x00ff00};
    //    cL_dlG_ColmColor *clmColor =
    //        new cL_dlG_ColmColor(xx,hsp_Tree_ViewXML->currentIndex (),this);

    //    hsp_Tree_ViewXML->setItemDelegateForColumn(0, clmColor);

    hsp_Tree_ViewXML->setItemDelegateForColumn(1, new cm_dlG_RichTxt);
    hsp_Tree_ViewXML->setItemDelegateForColumn(3, new cm_dlG_cb_hTur);
    hsp_Tree_ViewXML->setModel(modelXML);

    lB_Hesap = new QLabel("Kod-------");
}

void hsp_Tree_view::createGui()
{
    QWidget *page0 = new QWidget(this);
    QVBoxLayout *layout0 = new QVBoxLayout(page0);

    layout0->addWidget(hsp_Tree_ViewXML);
    layout0->addWidget(lB_Hesap);

    /// central widget
    wdgt_central = new QWidget;
    setCentralWidget(page0);
}

void hsp_Tree_view::createActions()
{
    qDebug() << "-----------    ::hChsp createActions";
    fileNewAction = createAction(":/rsm/images/filenew.png",
                                 tr("Yeni Hesap Dosyası"),
                                 this,
                                 QKeySequence::New);
    fileOpenAction = createAction(":/rsm/images/fileopen.png",
                                  tr("Hesap Dosyası Aç..."),
                                  this,
                                  QKeySequence::Open);
    fileSaveAction = createAction(":/rsm/images/filesave.png",
                                  tr("Kaydet"),
                                  this,
                                  QKeySequence::Save);
    fileSaveAsAction = createAction(":/rsm/images/filesave.png",
                                    tr("Farklı Kaydet..."),
                                    this
#if QT_VERSION >= 0x040500
                                    ,
                                    QKeySequence::SaveAs
#endif
    );
    fileQuitAction = createAction(":/rsm/images/filequit.png", tr("Çıkış"), this);
#if QT_VERSION >= 0x040600
    fileQuitAction->setShortcuts(QKeySequence::Quit);
#else
    fileQuitAction->setShortcut(QKeySequence("Ctrl+Q"));
#endif
    editAddAction = createAction(":/rsm/images/editadd.png",
                                 tr("Hesap Ekle..."),
                                 this,
                                 QKeySequence(tr("Ctrl+A")));
    editDeleteAction = createAction(":/rsm/images/editdelete.png",
                                    tr("Hesap Sil..."),
                                    this,
                                    QKeySequence::Delete);

    editCutAction = createAction(":/rsm/images/editcut.png", tr("Kes"), this, QKeySequence::Cut);
    editPasteAction = createAction(":/rsm/images/editpaste.png",
                                   tr("Yapıştır"),
                                   this,
                                   QKeySequence::Paste);
    editMoveUpAction = createAction(":/rsm/images/editup.png",
                                    tr("Hesap Yukarı"),
                                    this,
                                    QKeySequence(tr("Ctrl+Up")));
    editMoveDownAction = createAction(":/rsm/images/editdown.png",
                                      tr("Hesap Aşağı"),
                                      this,
                                      QKeySequence(tr("Ctrl+Down")));
    editPromoteAction = createAction(":/rsm/images/editpromote.png",
                                     tr("Üst Hesap Yap"),
                                     this,
                                     QKeySequence(tr("Ctrl+Left")));
    editDemoteAction = createAction(":/rsm/images/editdemote.png",
                                    tr("Alt Hesap Yap"),
                                    this,
                                    QKeySequence(tr("Ctrl+Right")));

    editStartOrStopAction = createAction(":/rsm/images/0.png",
                                         tr("S&tart"),
                                         this,
                                         QKeySequence(tr("Ctrl+T")));
    editStartOrStopAction->setCheckable(true);
    editStartOrStopAction->setChecked(false);
    editHideOrShowDoneTasksAction = new QAction(tr("Kapalı Hesaplaı Gizle"), this);
    editHideOrShowDoneTasksAction->setCheckable(true);
    editHideOrShowDoneTasksAction->setChecked(false);
}

void hsp_Tree_view::createMenusAndToolBar()
{
    qDebug() << "-----------    ::hChsp createMenusAndToolBar";

    /*QMenu **/ fileMenu = menuBar()->addMenu(tr("Dosya"));
    /*QToolBar **/ fileToolBar = addToolBar(tr("Dosya"));
    fileToolBar->setAllowedAreas(Qt::LeftToolBarArea);

    foreach (QAction *action,
             QList<QAction *>() << fileNewAction << fileOpenAction << fileSaveAction
                                << fileSaveAsAction) {
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
    editToolBar->setAllowedAreas(Qt::LeftToolBarArea);

    foreach (QAction *action,
             QList<QAction *>() << editAddAction << editDeleteAction << emptyAction << editCutAction
                                << editPasteAction << emptyAction << editMoveUpAction
                                << editMoveDownAction << editPromoteAction << editDemoteAction
                                << emptyAction << editStartOrStopAction
                                << editHideOrShowDoneTasksAction)

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

void hsp_Tree_view::createConnections()
{
    qDebug() << "-----------    ::hChsp createConnections";
    connect(hsp_Tree_ViewXML->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this,
            &hsp_Tree_view::updateUi);

    connect(hsp_Tree_ViewXML->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            &hsp_Tree_view::updateUi);

    connect(this,
            SIGNAL(customContextMenuRequested(QPoint)),
            this,
            SLOT(customContextMenuRequested(QPoint)));

    connect(modelXML, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setDirty()));

    connect(modelXML, SIGNAL(stopTiming()), this, SLOT(stopTiming()));

    connect(modelXML, SIGNAL(modelReset()), this, SLOT(setDirty()));

    //  connect(modelXML, &cm_TreeXML::);

    QHash<QAction *, QString> slotForAction;
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

    QHashIterator<QAction *, QString> i(slotForAction);
    while (i.hasNext()) {
        i.next();
        connect(i.key(), SIGNAL(triggered()), this, qPrintable(i.value()));
    }

    connect(editStartOrStopAction, SIGNAL(triggered(bool)), this, SLOT(editStartOrStop(bool)));
    connect(editHideOrShowDoneTasksAction,
            SIGNAL(triggered(bool)),
            this,
            SLOT(editHideOrShowDoneTasks(bool)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(&iconTimeLine, SIGNAL(frameChanged(int)), this, SLOT(updateIcon(int)));
    qDebug() << "                  kntrl son";
}

void hsp_Tree_view::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(fileNewAction);
    menu.addAction(fileOpenAction);
    menu.addAction(fileSaveAction);
    menu.exec(event->globalPos());
}

void hsp_Tree_view::customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);
    menu.addActions(actions());
    menu.exec(mapToGlobal(pos));
}

///////////////////////////***************************************
void hsp_Tree_view::updateUi()
{
    qDebug() << "-----------    ::hChsp updateUi..." << modelXML->rowCount();
    fileSaveAction->setEnabled(isWindowModified());
    int rows = modelXML->rowCount();
    fileSaveAsAction->setEnabled(isWindowModified() || rows);
    editHideOrShowDoneTasksAction->setEnabled(rows);
    bool enable = hsp_Tree_ViewXML->currentIndex().isValid();


    foreach (QAction *action,
             QList<QAction *>() << editDeleteAction << editMoveUpAction << editMoveDownAction
                                << editCutAction << editPromoteAction << editDemoteAction)

        action->setEnabled(enable);

    editStartOrStopAction->setEnabled(rows);
    editPasteAction->setEnabled(modelXML->hasCutItem());

    qDebug() << " upt ui HesapItem";

    /// tree deki mevcut indexi internalpointer ile belirleyelim
    HesapItem *currentItem = static_cast<HesapItem *>(
        hsp_Tree_ViewXML->currentIndex().internalPointer());
    if (currentItem) {
        ///
        ///  mevcut hesap tüm evrene yayılsın
        ///

        emit sgnHesap(currentItem);

        ///
        /// hesap değiştiğinde detaylarda değişsin
        ///
        ///

        lB_Hesap->setText(QString::number(currentItem->hesapKod()) + " : "
                          + currentItem->parent()->hesapAd() + " - " + currentItem->hesapAd()
                          + " - " + currentItem->hesapAcklm() + " : "
                          + QString::number(currentItem->isTopluHesap()) + " : "
                          + currentItem->hesapTuru() + " : " + currentItem->DBFile());
    }
    qDebug() << " upt ui HesapItem";
}

void hsp_Tree_view::setCurrentIndex(const QModelIndex &index)
{
    //qDebug()<<"-----------    ::hChsp setcurindx";
    if (index.isValid()) {
        hsp_Tree_ViewXML->scrollTo(index);
        hsp_Tree_ViewXML->setCurrentIndex(index);
    }
}

////////////// E D I T S //////////////////////////////////////////////
///
///

void hsp_Tree_view::editAdd()
{
    qDebug() << "-----------    ::hChsp editAdd Yeni Hesap Ekleniyor...............";

    QWidget *addwdgt = new QWidget;
    addwdgt->setWindowModality(Qt::WindowModality::WindowModal);

    QGridLayout *lyt = new QGridLayout;
    addwdgt->setLayout(lyt);

    QPushButton *pb_ekle = new QPushButton("Yeni Hesap Ekle");
    QPushButton *pb_kaydet = new QPushButton("Kaydet");
    QPushButton *pb_Vazgeç = new QPushButton("Vazgeç");

    QLabel *a1 = new QLabel("Hesap Adı   : ");
    QLabel *a2 = new QLabel("Açıklama    : ");
    QLabel *a3 = new QLabel("Toplu Hesap : ");
    QLabel *a4 = new QLabel("Hesap Türü  : ");
    QLabel *a5 = new QLabel("Üst Hesap   : ");

    QLineEdit *le_ad = new QLineEdit;
    QLineEdit *le_acklama = new QLineEdit;
    QComboBox *cb_topluHesap = new QComboBox;
    cb_topluHesap->addItem("Normal Hesap ");
    cb_topluHesap->addItem("Toplu Hesap - Normal hesapların toplandığı hesap");

    QComboBox *cb_hesapTuru = new QComboBox;
    cb_hesapTuru->addItem("Konum");
    cb_hesapTuru->addItem("Şirket");
    cb_hesapTuru->addItem("Şahıs");
    cb_hesapTuru->addItem("Aktif Hesap");
    cb_hesapTuru->addItem("Pasif Hesap");
    cb_hesapTuru->addItem("Araç");
    cb_hesapTuru->addItem("Malzeme");
    cb_hesapTuru->addItem("Gayrimenkul");
    cb_hesapTuru->addItem("Menkul");

    QComboBox *cb_ustHesap = new QComboBox;

    lyt->addWidget(a1, 3, 1, 1, 1);
    lyt->addWidget(le_ad, 3, 2, 1, 2);
    lyt->addWidget(a2, 4, 1, 1, 1);
    lyt->addWidget(le_acklama, 4, 2, 1, 2);
    lyt->addWidget(a3, 5, 1, 1, 1);
    lyt->addWidget(cb_topluHesap, 5, 2, 1, 2);
    lyt->addWidget(a4, 6, 1, 1, 1);
    lyt->addWidget(cb_hesapTuru, 6, 2, 1, 2);
    lyt->addWidget(a5, 7, 1, 1, 1);
    lyt->addWidget(cb_ustHesap, 7, 2, 1, 2);
    lyt->addWidget(pb_kaydet, 5, 5, 1, 1);
    lyt->addWidget(pb_ekle, 6, 5, 1, 1);
    lyt->addWidget(pb_Vazgeç, 7, 5, 1, 1);

    addwdgt->show();

    connect(pb_ekle, &QPushButton::clicked, this, [=]() {
        le_ad->setText("");
        le_acklama->setText("");
        cb_topluHesap->setCurrentIndex(0);
        cb_hesapTuru->setCurrentText(0);
        cb_ustHesap->setCurrentText(0);
    });

    connect(pb_kaydet, &QPushButton::clicked, this, [=]() {
        QModelIndex index = hsp_Tree_ViewXML->currentIndex();
        if (modelXML->insertRows(0, 1, index)) {
            index = modelXML->index(0, 0, index);
            setCurrentIndex(index);

            HesapItem *Item = getCurrentItem();
            Item->setHesapAd(le_ad->text());
            Item->setHesapAcklm(le_acklama->text());
            Item->setTopluHesap(0);
            Item->setHesapTuru(cb_hesapTuru->currentText());
            Item->setUstHesap(cb_ustHesap->currentText());
            Item->setDBFile("xxx");
        }
    });
    connect(pb_Vazgeç, &QPushButton::clicked, this, [=]() { addwdgt->close(); });

    setDirty();
    updateUi();
}

void hsp_Tree_view::editDelete()
{
    //qDebug()<<"-----------    ::hChsp editDelete";
    //qDebug() << "editdelete";
    QModelIndex index = hsp_Tree_ViewXML->currentIndex();
    if (!index.isValid())
        return;

    QString name = modelXML->data(index).toString();
    int rows = modelXML->rowCount(index);
    if (modelXML->isTimedItem(index))
        stopTiming();
    qDebug() << "--edit delete 01";
    QString message;
    if (rows == 0)
        message = tr("<p>HESAP SİL '%1'").arg(name);
    else if (rows == 1)
        message = tr("<p>HESAP SİL '%1' ve alt hesabı (ve "
                     "alt hesaba bağlı hesaplar)")
                      .arg(name);
    else if (rows > 1)
        message = tr("<p>HESAP SİL '%1' ve ona bağlı %2 alt hesap "
                     "(ve alt hesaplara bağlı hesaplar)")
                      .arg(name)
                      .arg(rows);
    if (!AQP::okToDelete(this, tr("Delete"), message))
        return;
    qDebug() << "--edit delete 02";
    modelXML->removeRow(index.row(), index.parent());
    qDebug() << "--edit delete 03";
    setDirty();
    qDebug() << "--edit delete 04";
    updateUi();
    qDebug() << "--edit delete s0n";
}

void hsp_Tree_view::editCut()
{
    qDebug() << "-----------    ::hChsp editCut";
    QModelIndex index = hsp_Tree_ViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->cut(index));
    editPasteAction->setEnabled(modelXML->hasCutItem());
}

void hsp_Tree_view::editPaste()
{
    qDebug() << "-----------    ::hChsp editpaste";
    setCurrentIndex(modelXML->paste(hsp_Tree_ViewXML->currentIndex()));
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
}

void hsp_Tree_view::editMoveUp()
{
    qDebug() << "-----------    ::hChsp editmoveup";
    hsp_Tree_ViewXML->setCurrentIndex(modelXML->moveUp(hsp_Tree_ViewXML->currentIndex()));
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
}

void hsp_Tree_view::editMoveDown()
{
    qDebug() << "-----------    ::hChsp editmovedown";

    hsp_Tree_ViewXML->setCurrentIndex(modelXML->moveDown(hsp_Tree_ViewXML->currentIndex()));
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
}

void hsp_Tree_view::editPromote()
{
    qDebug() << "-----------    ::hChsp editPromote";
    QModelIndex index = hsp_Tree_ViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    setCurrentIndex(modelXML->promote(index));
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
}

void hsp_Tree_view::editDemote()
{
    qDebug() << "-----------    ::hChsp editDemote";
    QModelIndex index = hsp_Tree_ViewXML->currentIndex();
    if (modelXML->isTimedItem(index))
        stopTiming();
    hsp_Tree_ViewXML->setCurrentIndex(modelXML->demote(index));
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
}

//////////// X M L  F I L E  O P E R A T I O N S ////////////////////
///
///
///

bool hsp_Tree_view::okToClearData()
{
    // qDebug()<<"-----------    ::hChsp OkToClearData";
    if (isWindowModified())
        return AQP::okToClearData(&hsp_Tree_view::fileSave,
                                  this,
                                  tr("Sayfada değişiklikler var"),
                                  tr("Değişiklikler Kayıt Edilsin mi?"));
    return true;
}

void hsp_Tree_view::fileNew()
{
    // qDebug()<<"-----------    ::hChsp filenew XML";

    if (!okToClearData())
        return;
    modelXML->clear();
    modelXML->setFilename(QString());
    setDirty(false);
    setWindowTitle(tr("%1 - İsimsiz hesap dosyası[*]").arg(QApplication::applicationName()));
    updateUi();
}

void hsp_Tree_view::fileOpen()
{
    // qDebug()<<"-----------    ::hChsp fileOpen XML";
    //qDebug() << "fileopen";
    if (!okToClearData())
        return;
    QString filename = modelXML->filename();
    QString dir(filename.isEmpty() ? QString(".") : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
                                            tr("%1 - Open").arg(QApplication::applicationName()),
                                            dir,
                                            tr("konumlar (*.knm)"));
    if (!filename.isEmpty())
        load(filename);
}

void hsp_Tree_view::load(const QString &filename, const QStringList &taskPath)
{
    qDebug() << "loading file (filename) '" << filename << " ' at path (taskPath): " << taskPath;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    try {
        modelXML->load(filename);
        if (!taskPath.isEmpty()) {
            setCurrentIndex(modelXML->indexForPath(taskPath));
        }
        for (int column = 0; column < modelXML->columnCount(); ++column) {
            //  hsp_Tree_ViewXML->resizeColumnToContents(column);
            hsp_Tree_ViewXML->setColumnWidth(0, 200);
            hsp_Tree_ViewXML->setColumnWidth(1, 100);
            hsp_Tree_ViewXML->setColumnWidth(2, 50);
            hsp_Tree_ViewXML->setColumnWidth(3, 100);
            hsp_Tree_ViewXML->setColumnWidth(4, 400);
        }
        hsp_Tree_ViewXML->setMinimumWidth(50);
        hsp_Tree_ViewXML->header()->setStretchLastSection(false);
        hsp_Tree_ViewXML->setColumnHidden(5, true);
        hsp_Tree_ViewXML->setAllColumnsShowFocus(false);
        hsp_Tree_ViewXML->setIndentation(10);

        setDirty(false);

        setWindowTitle(
            tr("%1 - %2[*]").arg(QApplication::applicationName(), QFileInfo(filename).fileName()));

        statusBar()->showMessage(tr("%1 yüklendi").arg(filename), StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this,
                     tr("HATA"),
                     tr("Yüklemede Hata %1: %2\n"
                        "yeni dosya oluşturuluyor")
                         .arg(filename, QString::fromUtf8(error.what())));
    }
    updateUi();
    editHideOrShowDoneTasks(editHideOrShowDoneTasksAction->isChecked());
    hsp_Tree_ViewXML->setFocus();
    QApplication::restoreOverrideCursor();
}

bool hsp_Tree_view::fileSave()
{
    qDebug() << "-----------    ::hChsp fileSave XML";
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
            statusBar()->showMessage(tr("Saved %1").arg(modelXML->filename()), StatusTimeout);
            saved = true;
        } catch (AQP::Error &error) {
            AQP::warning(this,
                         tr("Error"),
                         tr("Failed to save %1: %2")
                             .arg(modelXML->filename(),
                                  /*)
                         .arg(*/
                                  QString::fromUtf8(error.what())));
        }
    }
    updateUi();
    return saved;
}

bool hsp_Tree_view::fileSaveAs()
{
    qDebug() << "-----------    ::hChsp fileSaveAs XML";
    // qDebug() << "filesaveas";
    QString filename = modelXML->filename();
    QString dir = filename.isEmpty() ? "." : QFileInfo(filename).path();
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

void hsp_Tree_view::closeEvent(QCloseEvent *event)
{
    qDebug() << "-----------    ::hChsp closeEvent---------------------------"
             << " filename               : " << modelXML->filename() << " pathforindex (curindex): "
             << modelXML->pathForIndex(hsp_Tree_ViewXML->currentIndex());
    stopTiming();
    if (okToClearData()) {
        QSettings settings;
        settings.setValue(GeometrySetting, saveGeometry());
        settings.setValue(FilenameSetting, modelXML->filename());
        settings.setValue(CurrentTaskPathSetting,
                          modelXML->pathForIndex(hsp_Tree_ViewXML->currentIndex()));

        qDebug() << "        close -> settings.filename " << settings.fileName();
        event->accept();
    } else
        event->ignore();
}

////////////////// T A S K S ////////////////////////////////////////////////
///
///

void hsp_Tree_view::stopTiming()
{
    qDebug() << "-----------    ::hChsp stoptiming";
    if (editStartOrStopAction->isChecked())
        editStartOrStopAction->trigger(); // stop the clock
}

void hsp_Tree_view::editStartOrStop(bool start)
{
    qDebug() << "-----------    ::hChsp editStartOrStop";
    timer.stop();
    iconTimeLine.stop();
    if (start) { // start the clock iff there's a current task
        QModelIndex index = hsp_Tree_ViewXML->currentIndex();
        if (!index.isValid()) {
            editStartOrStopAction->setChecked(false);
            start = false;
        } else {
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
    } else {       // stop the clock
        timeout(); // update to now

        modelXML->setIconForTimedItem();
        modelXML->clearTimedItem();
        editStartOrStopAction->setIcon(QIcon(":/rsm/images/0.png"));
    }
    editStartOrStopAction->setText(start ? tr("S&top") : tr("S&tart"));
    editStartOrStopAction->setIcon(
        QIcon(start ? tr(":/rsm/images/4.png") : tr(":/rsm/images/0.png")));
}

void hsp_Tree_view::timeout()
{
    qDebug() << "-----------    ::hChsp timeout";
    modelXML->incrementEndTimeForTimedItem(timer.remainingTime());
    timer.start();
}

void hsp_Tree_view::updateIcon(int frame)
{
    qDebug() << "-----------    ::hChsp updateIcon";
    if (frame > LastFrame)
        return;
    QIcon icon(QString(":/rsm/images/%1.png").arg(frame));
    modelXML->setIconForTimedItem(icon);
    editStartOrStopAction->setIcon(icon);
}

void hsp_Tree_view::editHideOrShowDoneTasks(bool hide)
{
    // qDebug()<<"-----------    ::hChsp edithideorshwdonetsks";
    hideOrShowDoneTask(hide, QModelIndex());
}

void hsp_Tree_view::hideOrShowDoneTask(bool hide, const QModelIndex &index)
{
    // qDebug()<<"-----------    ::hChsp hideorshowdntsk";
    bool hideThisOne = hide && modelXML->isChecked(index);
    if (index.isValid())
        hsp_Tree_ViewXML->setRowHidden(index.row(), index.parent(), hideThisOne);
    if (!hideThisOne) {
        for (int row = 0; row < modelXML->rowCount(index); ++row)
            hideOrShowDoneTask(hide, modelXML->index(row, 0, index));
    }
}
