QT       += core gui sql widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbase.cpp \
    hc_treemodel.cpp \
    main.cpp \
    mainwindow.cpp \
    mysqlmodel.cpp

HEADERS += \
    dbase.h \
    hc_treemodel.h \
    mainwindow.h \
    mysqlmodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
