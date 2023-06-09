/*
developed by Andreas D. Christ, software(at)quantentunnel.de
using Qt Creator and Qt SDK with non-commercial license, see http://qt.nokia.com
license: GPL or any other license compatible with Qt's license (users choice)
*/

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QStandardItemModel>
#include <QSqlRelationalDelegate>
#include <QItemSelectionModel>
#include <QDebug>
#include <QSqlError>
#include <QSortFilterProxyModel>

#include "mysqlrelationaldelegate.h"
#include "testdialog.h"
#include "qxtreeproxymodel.h"

#include <QSqlRecord>
#include <QSqlDriver>

#ifdef MODEL_TEST
#include <modeltest.h>
#endif

// to test the various options: define options  in .pro file


TestDialog::TestDialog(QWidget *parent) : QDialog(parent){
    setupUi(this);
    //   qDebug() << "111111111 - testdialog constructor -----------------";
    bool ok;
#if (TABLEMODEL==QSQLTABLEMODEL) || (TABLEMODEL==QSQLRELATIONALTABLEMODEL)
    QSqlDatabase db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
    // db.setDatabaseName(QLatin1String(":memory:"));
    db.setDatabaseName(QLatin1String("qxtree.db"));

    Q_ASSERT(db.open());
    //qDebug() <<"*-*--*-**-*-*-*-*-*-*-*";
    //   qDebug() << "drriveerrr" << db.driver()->hasFeature(QSqlDriver::QuerySize );

    //   qDebug() << "11---------002 db opened---------------";
    QSqlQuery sqlQuery(db);
    // create Table1 (main table)
#ifdef AUTOINCREMENT
    qDebug() << " creating tables adding records----------------";
    ok = sqlQuery.exec(
                QLatin1String("CREATE TABLE IF NOT EXISTS Table1 "
                              "(Identifier INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "Parent INTEGER NOT NULL, "
                              "Content, Details );"));
#else
    qDebug() << "********004**** not auto increment";
    ok = sqlQuery.exec(QLatin1String("CREATE TABLE Table1 "
                                     "(Content, Identifier INTEGER PRIMARY KEY,"
                                     "Parent INTEGER NOT NULL, Details);"));
#endif
    Q_ASSERT_X(ok, "CREATE TABLE IF NOT EXISTS sql statement",
               "Table1 likely already exists");

#ifdef AUTOINCREMENT
    qDebug() << "11 has feature size "<<sqlQuery.driver()
                ->hasFeature(QSqlDriver::QuerySize);
    ok=sqlQuery.exec(QLatin1String("SELECT * "
                                   "FROM Table1 "
                                   "WHERE Details = :detail "));
    sqlQuery.bindValue(":detail","Details for first item");

qDebug() << sqlQuery.executedQuery();
    sqlQuery.next();
    int fieldNo = sqlQuery.record().indexOf("details");
    qDebug() << "value 0 "<<sqlQuery.value(fieldNo).toString() ;
    qDebug() << "value 1 "<<sqlQuery.value(1).toString() ;
    qDebug() << "value 2 "<<sqlQuery.value(2).toString() ;
    Q_ASSERT(ok);
    qDebug() <<"recouuuuuunt"<<sqlQuery.size();

    if (sqlQuery.size() < 1) // kayıt yok EKLE
    {   ok = sqlQuery.exec(
                    QLatin1String("INSERT INTO Table1 "
                                  "( Parent,Content, Details) "
                                  "VALUES ( 0, 'Details for first item',1);"));
        Q_ASSERT(ok);
    }
    /*
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 0, 'Details for first item',1);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 1, 'Details for second item',2);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 1, 'Details for 3rd item',2);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 0, 'Details for 4th item',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 0, 'Details for 5th item',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 1, 'Details for 6th item',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 2, 'Details for 7th item a',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 2, 'Details for 7th item b',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 2, 'Details for 7th item c',3);"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1 "
                              "( Parent,Content, Details) "
                              "VALUES ( 2, 'Details for 7th item d',3);"));
    Q_ASSERT(ok);
*/
#else
    qDebug() << "11------------- 006 insert reccs without auto inc.";
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (1, 1, 0, 'Details for first item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (2, 2, 1, 'Details for second item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (2, 3, 1, 'Details for 3rd item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 4, 0, 'Details for 4th item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 5, 0, 'Details for 5th item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 6, 1, 'Details for 6th item');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 7, 2, 'Details for 7th item a');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 8, 2, 'Details for 7th item b');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 9, 2, 'Details for 7th item c');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(
                QLatin1String("INSERT INTO Table1"
                              "(Content, Identifier, Parent, Details) "
                              "VALUES (3, 10, 2, 'Details for 7th item d');"));
    Q_ASSERT(ok);
#endif
#endif

    // create Table2 (lookup table)
#if (TABLEMODEL==QSQLRELATIONALTABLEMODEL)
    qDebug() << "11-------------- 007 - create table2 lookup table";
    ok = sqlQuery.exec(QLatin1String("CREATE TABLE IF NOT EXISTS Table2 "
                                     "(Number, String);"));
    Q_ASSERT_X(ok, "CREATE TABLE IF NOT EXISTS sql statement",
               "Table2 likely already exists");
    /*
    ok = sqlQuery.exec(QLatin1String("INSERT INTO Table2 "
                                     "(Number, String) "
                                     "VALUES (1, 'One');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(QLatin1String("INSERT INTO Table2 "
                                     "(Number, String) "
                                     "VALUES (2, 'Two');"));
    Q_ASSERT(ok);
    ok = sqlQuery.exec(QLatin1String("INSERT INTO Table2 "
                                     "(Number, String) "
                                     "VALUES (3, 'Three');"));
    Q_ASSERT(ok);
*/
#endif

    QAbstractItemModel* tableModel;
#if (TABLEMODEL==QSQLRELATIONALTABLEMODEL)
    qDebug() << "11---------- 008 tablemodel qasqlrelmodel created";
    tableModel = new QSqlRelationalTableModel (this, db);
#elif (TABLEMODEL==QSQLTABLEMODEL)
    // qDebug() << "009";
    tableModel = new QSqlTableModel (this, db);
#elif (TABLEMODEL==QSTANDARDITEMMODEL)
    qDebug() << "0010";
    tableModel = new QStandardItemModel (6, 4, this);
    for (int row = 0; row < 6; ++row) {
        (qobject_cast<QStandardItemModel*>(tableModel))
                ->setItem(row, 0, new QStandardItem(
                              QString::number(row)));
        (qobject_cast<QStandardItemModel*>(tableModel))
                ->setItem(row, 1, new QStandardItem(
                              QString::number(row+10)));
        (qobject_cast<QStandardItemModel*>(tableModel))
                ->setItem(row, 2, new QStandardItem(
                              QString::number(row == 0 ? 99 : (row > 2 ? 11 : 0))));
        (qobject_cast<QStandardItemModel*>(tableModel))
                ->setItem(row, 3, new QStandardItem(
                              QLatin1String("Details")));}
#else
    Q_ASSERT_X(false, "create table model",
               "no valid model in #DEFINES of *.pro file");
#endif

#if (TABLEMODEL==QSQLTABLEMODEL) || (TABLEMODEL==QSQLRELATIONALTABLEMODEL)
#if (SUBMITOPTION==ONFIELDCHANGE)
    {
        (qobject_cast<QSqlTableModel*>(tableModel))
                ->setEditStrategy(QSqlTableModel::OnFieldChange);
        //   qDebug() << "11---------- 0081 onfieldchange";
    }
#elif (SUBMITOPTION==ONROWCHANGE)
    (qobject_cast<QSqlTableModel*>(tableModel))
            ->setEditStrategy(QSqlTableModel::OnRowChange);
#elif (SUBMITOPTION==ONMANUALSUBMIT)
    (qobject_cast<QSqlTableModel*>(tableModel))
            ->setEditStrategy(QSqlTableModel::OnManualSubmit);
#else
    Q_ASSERT_X(false, "set edit strategy",
               "no valid edit strategy in #DEFINES in *.pro file");
#endif
    qDebug() << "11--- 082 tested submit strategy:"
             << (qobject_cast<QSqlTableModel*>(tableModel))
                ->editStrategy() <<" = onfieldchange";

#ifndef AUTOINCREMENT
    ok = connect(tableModel, SIGNAL(primeInsert(int,QSqlRecord&)),
                 this, SLOT(table1PrimeInsert(int, QSqlRecord&)));
    qDebug() << "---------- 0083 signal primeinsert if auto inc";
    Q_ASSERT(ok);
#endif
    (qobject_cast<QSqlTableModel*>(tableModel))
            ->setTable(QLatin1String("Table1"));
#if (TABLEMODEL==QSQLRELATIONALTABLEMODEL)
    (qobject_cast<QSqlRelationalTableModel*>(tableModel))
            ->setRelation(0, QSqlRelation(QLatin1String("Table2"),
                                          QLatin1String("Number"), QLatin1String("String")));
    qDebug() << "11---------- 0084 relation";
#endif
    (qobject_cast<QSqlTableModel*>(tableModel))->select();
#endif      //a sql model
    // qDebug() << "11-------0011";
    // how to retrieve foreign key
    /*

   qDebug() << "*** Qt::DisplayRole *** does not work";
   for (int c(0); c < tableModel->columnCount(QModelIndex()); ++c)
        qDebug() << tableModel->data(tableModel
        ->index(0, c, QModelIndex()), Qt::DisplayRole);

   qDebug() << "*** Qt::EditRole *** does not work";
   for (int c(0); c < tableModel->columnCount(QModelIndex()); ++c)
        qDebug() << tableModel->data(tableModel
        ->index(0, c, QModelIndex()), Qt::EditRole);

   qDebug() << "*** record *** does not work";
   qDebug() << tableModel->record(0);
   qDebug() << "here is how it works, using nasty workaround";
   QSqlTableModel* relatedTable = tableModel->relationModel(0);
   QModelIndex idx = relatedTable->match(relatedTable
        ->index(0, 1),Qt::DisplayRole,tableModel->data(tableModel
        ->index(0, 0, QModelIndex()), Qt::DisplayRole)).at(0);

   qDebug() << relatedTable->data(relatedTable
        ->index(idx.row(), 0, QModelIndex()), Qt::DisplayRole);*/

    /*how to update table
   qDebug() << "original row count" << tableModel->rowCount();

   //ok = sqlQuery.exec(QLatin1String("INSERT INTO Table1
                (Details) VALUES ('item added by query');"));
   ok = tableModel->insertRow(0, QModelIndex());

   Q_ASSERT(ok);

   // retrieve inserted record that is empty
   QSqlRecord record = tableModel->record(0);
   record.setValue(3,
     QLatin1String("item added by insertRow and setRecord"));

   // record is no longer empty
   ok = tableModel->setRecord(0, record);
   Q_ASSERT(ok);
   ok = tableModel->submitAll();
   Q_ASSERT(ok);
   qDebug() << "tableModel not yet updated, row count still"
            << tableModel->rowCount();
   ok = tableModel->select();
   Q_ASSERT(ok);
   qDebug() << "after tableModel->select(), but row count still"
            << tableModel->rowCount();
   tableModel->setTable(QLatin1String("Table1"));
   ok = tableModel->select();
   Q_ASSERT(ok);
   qDebug() << "row count only now increased"
            << tableModel->rowCount();
   exit(1);*/

    //   tableModel->setFilter(QLatin1String("Identifier = 3"));

    // how to insert rows, see http://www.qtcentre.org/archive/index.php/t-16085.html

    // to test tree proxy using QSqlQueryModel as source: non-editable model
    /*   QSqlQueryModel* tableModel = new QSqlQueryModel(this);
   tableModel->setQuery(QLatin1String("SELECT * FROM Table1"));*/

    tableView->setModel(tableModel);
    tableView->resizeColumnsToContents();

    tableView->setSelectionMode (QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior (QAbstractItemView::SelectItems);
#if TABLEMODEL==QSQLRELATIONALTABLEMODEL
    qDebug() << "11---------0012 delegate";
    QSqlRelationalDelegate* tableDelegate = new QSqlRelationalDelegate(tableView);
    Q_ASSERT(tableDelegate);
    tableView->setItemDelegate(tableDelegate);
#endif
    //  qDebug() << "11---------0013 treemodel";
    QXTreeProxyModel* treeModel = new QXTreeProxyModel(this);
    //   qDebug() << "11---------00131 setsourcemodel";
    treeModel->setSourceModel(tableModel);
    ok = treeModel->setIdCol(0);
    Q_ASSERT(ok);
    ok = treeModel->setParentCol(1);
    Q_ASSERT(ok);
    QList<QVariant> defaultValues;
    defaultValues << 1;
    treeModel->setDefaultValues(defaultValues);

#ifdef MODEL_TEST
    //   (void) new ModelTest(treeModel, this);
#endif
    // qDebug() << "11---------00132 setmodel- treemodel";
    treeView->setModel(treeModel);
    treeView->resizeColumnToContents(2);
    treeView->setSelectionMode (QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior (QAbstractItemView::SelectItems);
#if TABLEMODEL==QSQLRELATIONALTABLEMODEL
    QSqlRelationalDelegate* treeDelegate = new mySqlRelationalDelegate(treeView);
    Q_ASSERT(treeDelegate);
    treeView->setItemDelegate(treeDelegate);
#endif
    // qDebug() << "11----------testdialog constructor -------ended----";
    // qDebug() << "111111111111111111111111111111111111111111111111111111----";
}

void TestDialog::on_removeButton_clicked(){
    QItemSelectionModel* selections = treeView->selectionModel();
    qDebug() << "remove rows, index count =" << selections->selectedIndexes().count();
    if (selections->selectedIndexes().isEmpty()) return;
    QModelIndex parentIndex = selections->selectedIndexes().first().parent();
    QMap<int, QModelIndex> selectedRows;
    foreach (QModelIndex index, selections->selectedIndexes()) {
        selectedRows.insert(index.row(), index);
        Q_ASSERT_X(index.parent() == parentIndex, "limited test design", "only to remove branches within single parent");}
    int firstRow = selectedRows.keys().first();
    int lastRow(selectedRows.keys().last());
    Q_ASSERT_X(selectedRows.count() == (lastRow - firstRow + 1), "limited test design", "slected branches must be contiguous");
    qDebug() << "   rows" << firstRow << "to" << lastRow << "from parent" << parentIndex;
    bool ok = treeView->model()->removeRows(firstRow, lastRow - firstRow + 1, parentIndex);
    Q_ASSERT(ok);
    qDebug() << "   rows removed";
}

void TestDialog::on_insertButton_clicked(){
    QItemSelectionModel* selections = treeView->selectionModel();
    Q_ASSERT(selections);
    qDebug() << "TestDialog insert rows, count =" << selections->selectedIndexes().count();
    QModelIndex firstSelected;
    int rowCount;
    if (selections->selectedIndexes().isEmpty()){
        firstSelected = QModelIndex();
        rowCount = 1;}
    else {
        QMap<int, QModelIndex> selectedRows;
        foreach (QModelIndex index, selections->selectedIndexes()) selectedRows.insert(index.row(), index);
        rowCount = selectedRows.count();
        firstSelected = selectedRows.values().first();}
    bool ok(true);
    /* Alternative method to provide unique id, but only works for single row insertion (i.e., not to drag and drop multiple entries).
#if (TABLEMODEL==QSTANDARDITEMMODEL)
   static int nextRowId(2000);
   for (int r(0); r < rowCount && ok; ++r){
      QList<QVariant> defaultValues;
      defaultValues << 1 << ++nextRowId;
      qobject_cast<QXTreeProxyModel*>(treeView->model())->setDefaultValues(defaultValues);
      ok = treeView->model()->insertRow(firstSelected.row(), firstSelected);}
#else */
    ok = treeView->model()->insertRows(firstSelected.row(),
                                       rowCount, firstSelected);
    //#endif
    Q_ASSERT(ok);}

void TestDialog::on_addColButton_clicked(){
    QItemSelectionModel* selections = treeView->selectionModel();
    qDebug() << "TestDialog insert column";
    QModelIndex firstSelected;
    int col;
    if (selections->selectedIndexes().isEmpty())
        col = treeView->model()->columnCount(QModelIndex());
    else
        col = selections->selectedIndexes().at(0).column();
    treeView->model()->insertColumn(col, QModelIndex());}

void TestDialog::on_buttonBox_clicked(QAbstractButton* button){
    QSqlTableModel* sqlModel = qobject_cast<QSqlTableModel*>(qobject_cast<QAbstractProxyModel*>(treeView->model())->sourceModel());
    if (!sqlModel) return;
    QDialogButtonBox::ButtonRole buttonRole = buttonBox->buttonRole(button);
    qDebug() << "action for" << sqlModel << "is" << buttonRole;
    if (buttonRole == QDialogButtonBox::ApplyRole) sqlModel->submitAll();
    if (buttonRole == QDialogButtonBox::ResetRole) sqlModel->revertAll();}







#ifndef AUTOINCREMENT
void TestDialog::table1PrimeInsert(int row, QSqlRecord& record)
{
    qDebug() << "--------------oo1---------------------------------------------";
    qDebug() << "table1PrimeInsert" << record;
    for(int i(0); i < record.count(); ++i) qDebug() << "   before" << record.value(i);
    Q_UNUSED(row);
    static int lastId(1000);
    record.setValue(QLatin1String("Identifier"), ++lastId);
    for(int i(0); i < record.count(); ++i)
        qDebug() << "   after" << record.value(i);
    //  qDebug() << "--------------end oo1------------------------------------------";
}
#endif
