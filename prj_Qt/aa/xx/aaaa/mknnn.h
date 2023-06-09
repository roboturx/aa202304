#ifndef MKNNN_H
#define MKNNN_H

#include "main/globals.h"


QT_BEGIN_NAMESPACE
class QComboBox;
class QDataWidgetMapper;
class QItemSelectionModel;
class QLabel;
class QLineEdit;
class QPushButton;
class QSqlRelationalTableModel;
class QStandardItemModel;
class QStringListModel;
class QTextEdit;
QT_END_NAMESPACE

//! [Window definition]




class mknnn : public QWidget
{
    Q_OBJECT

public:
    mknnn(QWidget *parent = nullptr);

private slots:
    void updateButtons(int row);

private:

    QTreeView * tree {};

    void setupModel();

    QLabel *nameLabel;
    QLabel *addressLabel;
    QLabel *typeLabel;
    QLineEdit *nameEdit;
    QTextEdit *addressEdit;
    QComboBox *typeComboBox;
    QPushButton *nextButton;
    QPushButton *previousButton;

    QSqlRelationalTableModel *model{};
    QItemSelectionModel *selectionModel{};
    QDataWidgetMapper *mapper;
    int typeIndex{};
};
//! [Window definition]

#endif
