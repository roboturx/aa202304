
#include "hsap/hsp_prxy_model.h"

#include <QtWidgets>

//! [0]
hsp_PRXYModel::hsp_PRXYModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}
//! [0]

//! [1]
void hsp_PRXYModel::setFilterMinimumDate(QDate date)
{
    minDate = date;
    invalidateFilter();
}
//! [1]

//! [2]
void hsp_PRXYModel::setFilterMaximumDate(QDate date)
{
    maxDate = date;
    invalidateFilter();
}
//! [2]

//! [3]
bool hsp_PRXYModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return (sourceModel()->data(index0).toString().contains(filterRegularExpression())
            || sourceModel()->data(index1).toString().contains(filterRegularExpression()))
           && dateInRange(sourceModel()->data(index2).toDate());
}
//! [3]

//! [4] //! [5]
bool hsp_PRXYModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    //! [4]

    //! [6]
    if (leftData.userType() == QMetaType::QDateTime) {
        return leftData.toDateTime() < rightData.toDateTime();
    } else {
        static const QRegularExpression emailPattern("[\\w\\.]*@[\\w\\.]*");

        QString leftString = leftData.toString();
        if (left.column() == 1) {
            const QRegularExpressionMatch match = emailPattern.match(leftString);
            if (match.hasMatch())
                leftString = match.captured(0);
        }
        QString rightString = rightData.toString();
        if (right.column() == 1) {
            const QRegularExpressionMatch match = emailPattern.match(rightString);
            if (match.hasMatch())
                rightString = match.captured(0);
        }

        return QString::localeAwareCompare(leftString, rightString) < 0;
    }
}
//! [5] //! [6]

//! [7]
bool hsp_PRXYModel::dateInRange(QDate date) const
{
    return (!minDate.isValid() || date > minDate)
           && (!maxDate.isValid() || date < maxDate);
}
//! [7]
