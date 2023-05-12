#ifndef HSP_FILTER_WGT_H
#define HSP_FILTER_WGT_H

#include <QLineEdit>



    QT_BEGIN_NAMESPACE
    class QAction;
    class QActionGroup;
    QT_END_NAMESPACE

    class hsp_filter_wgt : public QLineEdit
    {
        Q_OBJECT
        Q_PROPERTY(Qt::CaseSensitivity caseSensitivity READ caseSensitivity
                                                       WRITE setCaseSensitivity)
        Q_PROPERTY(PatternSyntax patternSyntax READ patternSyntax
                                               WRITE setPatternSyntax)
    public:
        explicit hsp_filter_wgt(QWidget *parent = nullptr);

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

#endif // HSP_FILTER_WGT_H
