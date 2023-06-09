#include "VTKontrol.h"
#include <QObject>
#include "VTTekton.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

VTKontrolEt::VTKontrolEt(QObject* parent): QObject(parent)
{
}

VTKontrolEt* VTKontrolEt::createInstance()
{
    return new VTKontrolEt();
}

VTKontrolEt::~VTKontrolEt()
{
}

VTKontrolEt* VTKontrolEt::instance()
{
    return Tekton<VTKontrolEt>::instance(VTKontrolEt::createInstance);
}

void VTKontrolEt::SetupDB(){
    m_veritaban = QSqlDatabase::addDatabase("QSQLITE");
    m_veritaban.setDatabaseName("dbprdct");
}

bool VTKontrolEt::IsOpen(){
    return m_veritaban.isOpen();
}

bool VTKontrolEt::Connect(){
    return m_veritaban.open();
}

void VTKontrolEt::Disconnect(){
    m_veritaban.close();
}

QString VTKontrolEt::GetError(){
    return m_veritaban.lastError().text();
}

QSqlDatabase VTKontrolEt::GetDB(){
    return m_veritaban;
}
