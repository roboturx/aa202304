#ifndef CW_hkk_H
#define CW_hkk_H

#include <QDialog>

namespace Ui {
class CW_hkk;
}

class CW_hkk : public QDialog
{
    Q_OBJECT

public:
    explicit CW_hkk(QWidget *parent = nullptr);
    ~CW_hkk();

private slots:
    void onbtnOK_clicked();
    void on_btnOK_2_clicked();

private:
    Ui::CW_hkk *ui;
};

#endif // CW_hkk_H
