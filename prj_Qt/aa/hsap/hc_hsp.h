#ifndef hC_hsp_H
#define hC_hsp_H


#include "hsap/taskitem.h"
//#include "libs/globals.h"
//#include "libs/alt_key.h"
//#include "cls_dlgt_richtext.h"
#include "hsap/hsp_maintree_xmlmodel.h"
#include "hsap/cm_dlg_richtxt.h"
#include "hsap/cw_dlg_options.h"

class QAction;
class QStandardItem;
class StandardItem;
class QModelIndex;
class QTreeView;

class hsp_mainTree_XMLmodel;




class hC_hsp : public QMainWindow
{
    Q_OBJECT

public:
    explicit hC_hsp(QWidget *parent=0);



    void setHesapAdColor(TaskItem *item);
    //cls_dlgt_ComboBox *cbdlgt;

    QString* ps_Hesap_Ad;
    quint64* pi_Hesap_Kod;

    QLabel * lB_Hesap;
    QLabel *integerLabel;
    QLabel *colorLabel ;
    QPushButton *colorButton;

    QTreeView *treeViewXML;
    QWidget * wdgt_central;
    QWidget * wdgt_hesap;
    cw_Dlg_Options *colorDialogOptionsWidget;

    TaskItem *getCurrentItem();
    hsp_mainTree_XMLmodel *modelXML;

private:
    void createGui();
    void createModelViewDelegate();
    void createActions();
    void createMenusAndToolBar();
    void createConnections();
    bool okToClearData();
    void setCurrentIndex(const QModelIndex &index);

    void hideOrShowDoneTask(bool hide, const QModelIndex &index);

    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileQuitAction;
    QAction *editAddAction;
    QAction *editDeleteAction;

    QAction *editCutAction;
    QAction *editPasteAction;
    QAction *editMoveUpAction;
    QAction *editMoveDownAction;
    QAction *editPromoteAction;
    QAction *editDemoteAction;

    QAction *editStartOrStopAction;
    QAction *editHideOrShowDoneTasksAction;





    QTimer timer;
    QTimeLine iconTimeLine;
    QTime timedTime;
    int currentIcon;

protected:
    void closeEvent(QCloseEvent*);

signals:
    void sgnHesap(quint64* m_Hesap_Kod, QString* m_Hesap_Ad);


public slots:
    void stopTiming();
    void hesapdegisti();

private slots:

    void setColor();
    void setInteger();

    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void editAdd();
    void editDelete();

    void editCut();
    void editPaste();
    void editMoveUp();
    void editMoveDown();
    void editPromote();
    void editDemote();

    void editStartOrStop(bool start);
    void editHideOrShowDoneTasks(bool hide);
    void setDirty(bool dirty=true)
         {   setWindowModified(dirty);  }

    void load(const QString &filename,
              const QStringList &taskPath=QStringList());
    void timeout();
    void updateIcon(int frame);
    void updateUi();
    void customContextMenuRequested(const QPoint &pos);
    void contextMenuEvent(QContextMenuEvent *event);
private:
    enum Style {Bold, Italic, StrikeOut, NoSuperOrSubscript,
                Subscript, Superscript};

    void createShortcuts();
    void createActions2 ();
    QAction *createAction2(const QString &text, const QVariant &data);
    QMenu *createColorMenu();
    void updateContextMenuActions();

    QAction *boldAction;
    QAction *italicAction;
    QAction *strikeOutAction;
    QAction *noSubOrSuperScriptAction;
    QAction *superScriptAction;
    QAction *subScriptAction;
    QAction *colorAction;

};


///////////////////////////////////////////////////////////////
/// \brief The HesapListesi class
/// xml dosyasından hesap adları ve renklerini
/// qpair olarak veren sınıf

//class HesapListesi
//{
//public:
//    typedef QPair<QString,QColor> PairHesapColor;

//    HesapListesi() {};
//    ~HesapListesi() {};
//    PairHesapColor getHesapListesi (QString hangihesaplar);

//private:
//    PairHesapColor setHesapListesi(QString hangiListe);
//    PairHesapColor hesapListesi{};
//};

class MyDelegate : public QStyledItemDelegate {
public:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const {
        QString text, text_highlight;
        if (index.column() == 0)
        {
            text = "Qt::black";

            text_highlight = "Qt::white";
        }
        QStyleOptionViewItem s = *qstyleoption_cast<
            const QStyleOptionViewItem*>(&option);
        s.palette.setColor(QPalette::Text  ,
                           QColor(text));
        s.palette.setColor(QPalette::HighlightedText,
                           QColor(text_highlight));

        QStyledItemDelegate::paint(painter, s, index);
    }
};


#endif // hC_hsp_H

