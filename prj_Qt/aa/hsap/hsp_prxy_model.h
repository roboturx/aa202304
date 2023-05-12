#ifndef hsp_PRXYModel_H
#define hsp_PRXYModel_H

#include <QDate>
#include <QSortFilterProxyModel>

//! [0]
class hsp_PRXYModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit hsp_PRXYModel(QObject *parent = nullptr);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(QDate date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(QDate date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool dateInRange(QDate date) const;

    QDate minDate;
    QDate maxDate;
};

#endif // hsp_PRXYModel_H
