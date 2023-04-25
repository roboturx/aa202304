#ifndef HC_HDTY_FILTER_WGT_H
#define HC_HDTY_FILTER_WGT_H

#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
QT_END_NAMESPACE

class hC_hDty_filter_wgt : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(Qt::CaseSensitivity caseSensitivity READ caseSensitivity
                   WRITE setCaseSensitivity)
    Q_PROPERTY(PatternSyntax patternSyntax READ patternSyntax
                   WRITE setPatternSyntax)
public:
    explicit hC_hDty_filter_wgt(QWidget *parent = nullptr);

    Qt::CaseSensitivity caseSensitivity() const;
    void setCaseSensitivity(Qt::CaseSensitivity);

    enum PatternSyntax {
        RegularExpression,
        Wildcard,
        FixedString
    };
    Q_ENUM(PatternSyntax)

    PatternSyntax patternSyntax() const;
    void setPatternSyntax(PatternSyntax);

signals:
    void filterChanged();

private:
    QAction *m_caseSensitivityAction;
    QActionGroup *m_patternGroup;
};


#endif // HC_HDTY_FILTER_WGT_H
