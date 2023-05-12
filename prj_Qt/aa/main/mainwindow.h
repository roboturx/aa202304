#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "adrs/clsn.h"
#include "adrs/frm.h"
#include "hsap/hc_hdty.h"
#include "hsap/hesapitem.h"
#include "hsap/hsp_tree_view.h"
#include "libs/globals.h"
#include "libs/hc_helptree.h"
#include "main/dbase.h"

//    QT_BEGIN_NAMESPACE
//    class QAction;
//    class QListWidget;
//    class QMenu;
//    class QTextEdit;
//    QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

    DBase *dbase;
    hC_CLSN *clsn;
    hC_FRM  *firma ;
    hC_hDTY *hspdty;
    hsp_Tree_view *hesapTree{};
    hC_helpTree *helpTree{};

    HesapItem *mw_currentHesapItem{};
    quint64 mw_currentHesapKod{};

    QTabWidget *w_TABs{};
    QSplitter *splitter{};

    QLabel *integerLabel{};
    QLabel *colorLabel{} ;
    QPushButton *colorButton{};



signals:
    void sgnMwHsp(HesapItem *hCTreeHsp);

private slots:
    void print();
    void about();

    // w tabs hchsptree deki hesaba göre oluşur
    // hesapitem connect ile geliyor
    void w_Tabs(HesapItem *hesapItem);
    void setColor();
    void setInteger();

private:
    void createGui();
    void createDbase();
    void createActions();
    void createStatusBar();
    void createDockWindows();
    void createTabs();

    QMenu *viewMenu;

protected:
    void closeEvent(QCloseEvent*);

};


#endif // MAINWINDOW_H
