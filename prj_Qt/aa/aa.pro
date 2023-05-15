#-------------------------------------------------
# Project created by Murat BALCI 2018-03-05T12:00:50
#-------------------------------------------------

# Modules controlled by DEFINES
#DEFINES += LINUX
DEFINES	+= CUSTOM_MODEL
DEFINES += MAIN
DEFINES += ADRS
DEFINES += HSAP
#DEFINES += OTHR

DEFINES += LINUX

DISTFILES += aaaprogram.txt \
    renk.qss


# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui sql widgets

TARGET = aa
TEMPLATE = app
CONFIG  += C++latest

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0



contains(DEFINES, MAIN) {

HEADERS  +=    \
main/cw_hkk.h  \
main/dbase.h   \
main/main.h \
main/mainwindow.h \
main/dialog.h \
libs/alt_key.h   \
libs/aqp.h     \
libs/cm_helptreexml.h \
libs/globals.h \
libs/hc_.h     \
libs/hc_helptree.h \
libs/hc_textedit.h \
libs/helpitem.h \
libs/kuhn_munkres.h \
libs/tamamla.h\
libs/VTKontrol.h \
libs/VTKontTekkere.h \
libs/VTTekton.h



SOURCES +=       \
main/cw_hkk.cpp  \
main/dbase.cpp   \
main/main.cpp    \
main/mainwindow.cpp \
main/dialog.cpp \
libs/alt_key.cpp \
libs/aqp.cpp     \
libs/cm_helptreexml.cpp \
libs/hc_.cpp     \
libs/hc_helptree.cpp \
libs/helpitem.cpp \
libs/hc_textedit.cpp \
libs/kuhn_munkres.cpp \
libs/tamamla.cpp \
libs/VTKontrol.cpp


#main/mw_main.cpp \
#main/login.cpp   \

#main/mw_main.h \
 #FORMS    += \
#main/login.h   \
}
contains(DEFINES, ADRS) {

SOURCES +=    \
adrs/clsn.cpp \
adrs/frm.cpp  \
adrs/ftr.cpp

HEADERS  +=  \
adrs/clsn.h  \
adrs/frm.h   \
adrs/ftr.h

 #FORMS    += \

}


contains(DEFINES, HSAP) {


HEADERS += \
hsap/cm_dlg_cb_htur.h \
hsap/cm_dlg_le_richtxt.h \
hsap/cm_dlg_richtxt.h \
hsap/cw_dlg_options.cpp \
hsap/hc_hdty_filter_wgt.h \
hsap/hc_hdty_prxy_model.h \
hsap/hc_hdty.h \
    hsap/hsp_add.h \
    hsap/hsp_cb_turu.h \
    hsap/hsp_filter_wgt.h \
    hsap/hsp_prxy_model.h \
    hsap/hsp_tree_model_xml.h \
    hsap/hsp_tree_view.h \
hsap/hesapitem.h

SOURCES += \
hsap/cm_dlg_cb_htur.cpp \
hsap/cm_dlg_le_richtxt.cpp \
hsap/cm_dlg_richtxt.cpp \
hsap/cw_dlg_options.cpp \
hsap/hc_hdty_filter_wgt.cpp \
hsap/hc_hdty_prxy_model.cpp \
hsap/hc_hdty.cpp \
    hsap/hsp_add.cpp \
    hsap/hsp_cb_turu.cpp \
    hsap/hsp_filter_wgt.cpp \
    hsap/hsp_prxy_model.cpp \
    hsap/hsp_tree_model_xml.cpp \
    hsap/hsp_tree_view.cpp \
hsap/hesapitem.cpp



}

# kısaltmalar
# cm - class model
# cw - class widget
# cb - combobox
# dlg - dialog
# dlG - delegate
# le - lineedit




contains(DEFINES, OTHR) {

SOURCES +=       \
    mchn/mkn.cpp \
    mchn/mkn_cinsi.cpp  \
    mchn/mkn_marka.cpp  \
    mchn/mkn_modeli.cpp \
    mlzm/mlzm.cpp    \
    mlzm/mlzm_gc.cpp \
    ie/ie.cpp    \
    ie/iedet.cpp \
    ie/tsnr.cpp  \
    ie/sclk.cpp  \
    grph/sortingbox.cpp \
    grph/shapeitem.cpp


HEADERS  +=    \
    mchn/mkn.h \
    mchn/mkn_cinsi.h  \
    mchn/mkn_marka.h  \
    mchn/mkn_modeli.h \
    mlzm/mlzm.h    \
    mlzm/mlzm_gc.h \
    ie/ie.h    \
    ie/iedet.h \
    ie/tsnr.h  \
    ie/sclk.h  \
    grph/sortingbox.h \
    grph/shapeitem.h

 #FORMS    += \

}

FORMS    +=     \
    wd_login.ui \
    cw_hkk.ui  \
    mn_navi.ui \
    login.ui   \
    dbase.ui


RESOURCES += src.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \libs

DISTFILES += \ libs/mime.types
   # hesap/main/images/0.png \
   # hesap/main/images/1.png \
   #hesap/main/images/2.png \
   # hesap/main/images/3.png \
   # hesap/main/images/4.png \
   # hesap/main/images/editadd.png \
   # hesap/main/images/editcut.png \
   # hesap/main/images/editdelete.png \
   # hesap/main/images/editdemote.png \
   # hesap/main/images/editdown.png \
   # hesap/main/images/editpaste.png \
   # hesap/main/images/editpromote.png \
   # hesap/main/images/editup.png \
   # hesap/main/images/filenew.png \
   # hesap/main/images/fileopen.png \
   # hesap/main/images/filequit.png \
   # hesap/main/images/filesave.png \
    # hesap/main/images/icon.png

HEADERS += \
    hsap/dlg/dlg_date.h \
    hsap/dlg/dlg_hlist.h \
    hsap/dlg/dlg_r.h \
    hsap/hsp_list.h

SOURCES += \
    hsap/dlg/dlg_date.cpp \
    hsap/dlg/dlg_hlist.cpp \
    hsap/dlg/dlg_r.cpp \
    hsap/hsp_list.cpp


