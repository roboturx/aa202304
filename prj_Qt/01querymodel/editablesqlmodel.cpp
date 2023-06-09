/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtSql>

#include "editablesqlmodel.h"
enum RelationRoles{
    CodeRole = Qt::UserRole + 1000,
};
EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

//! [0]
Qt::ItemFlags EditableSqlModel::flags(
    const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 1 || index.column() == 2)
        flags |= Qt::ItemIsEditable;
    return flags;
}
//! [0]

//! [1]
bool EditableSqlModel::setData(const QModelIndex &index,
                               const QVariant &value,
                               int   role )
{
    if (index.column() < 1 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok;
    if (index.column() == 1) {
        ok = setFirstName(id, value.toString());
    } else {
        ok = setLastName(id, value.toString());
    }
    refresh();
    return ok;
}
//! [1]

void EditableSqlModel::refresh()
{
    setQuery("select * from dbtb_accounts");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));


}

//! [2]
bool EditableSqlModel::setFirstName(int personId, const QString &firstName)
{
    QSqlQuery query;
    query.prepare("update dbtb_accounts set firstname = ? where id = ?");
    query.addBindValue(firstName);
    query.addBindValue(personId);
    return query.exec();

    /// control last eror
    ///
//    QSqlQueryModel model;
//    model.setQuery("select * from MyTable");
//    if (model.lastError().isValid())
//        qDebug() << model.lastError()


}
//! [2]

bool EditableSqlModel::setLastName(int personId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update dbtb_accounts set lastname = ? where id = ?");
    query.addBindValue(lastName);
    query.addBindValue(personId);
    return query.exec();
}
bool EditableSqlModel::checkAccountName(const QString &AccountName)
{
    QSqlQuery query;
    //query.prepare("select * from dbtb_accounts where AcName = ?");
    query.prepare ("SELECT GroupCode, AcName, ActCod FROM dbtb_accounts "
          "WHERE AcName = ? ");
    query.addBindValue(AccountName);


    query.exec();
    if ( this->lastError ().isValid())
        qDebug() << lastError();

    if (query.isActive())
    {  qDebug()<<"q is active"; }
    else { qDebug()<<"q is NOT active"; return false; }

    const QSqlRecord rec = query.record();


    while (query.next())
    {

        QString AcName = query.value(rec.indexOf("AcName")).toString();
        int GroupCode = query.value(rec.indexOf("GroupCode")).toInt();
        int ActCod = query.value(rec.indexOf("ActCod")).toInt();

        //QStandardItem *it = new QStandardItem(AcName);

        //it->setData(ActCod, RelationRoles::CodeRole);

        /// root item = parent index 0
        if(GroupCode == 0)
        {
            //stdmodel->invisibleRootItem()->appendRow(it);

        }
        else
        {
            QModelIndexList ixs = match(index(0, 0),
                             RelationRoles::CodeRole,
                             GroupCode,
                             1,
                              Qt::MatchExactly| Qt::MatchRecursive);

            if(ixs.size() > 0)
            // match found
            {
                //QStandardItem *parent = stdmodel->itemFromIndex(ixs.first());
               // parent->appendRow(it);
                qDebug()<<"1--- match found"<< AcName ;
            }
        }
    }




}
