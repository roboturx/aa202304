#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QTextEdit>
#include "ui_mw.h"
#include "database.h"
class DataManager;
///////////////////////////////////////////////////////
class MW : public QMainWindow
{
    Q_OBJECT
public:
    MW();
    ~MW();

    //debuq
    static QTextEdit * s_textEdit;

private slots:
    void updateButtons();

    void on_addCompany_clicked();
    void on_addProject_clicked();
    void on_editProject_clicked();
    void on_removeProject_clicked();
    void on_addPerson_clicked();
    void on_editPerson_clicked();
    void on_removePerson_clicked();
    void on_addMember_clicked();

private:
    void fillSampleData();

private:
  Ui::MW m_ui;

    DataManager* m_manager;
    DataBase *Db;

    int m_companyId;
    int m_projectId;
    int m_memberId;
    int m_personId;
};
#endif // MW_H
