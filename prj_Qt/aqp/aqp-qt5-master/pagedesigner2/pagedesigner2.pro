#The following four lines are commented out for Qt5:
#IS_GE_QT_46 = $$find(QT_VERSION, "^4\\.[6-9]\\.*")
#isEmpty(IS_GE_QT_46) {
#    error(Cannot build this example since it needs Qt 4.6 or higher)
#}
CONFIG	     += console debug
QT	     += svg printsupport
HEADERS	     += ../aqp/alt_key.hpp
SOURCES	     += ../aqp/alt_key.cpp
HEADERS	     += ../aqp/kuhn_munkres.hpp
SOURCES	     += ../aqp/kuhn_munkres.cpp
HEADERS	     += ../aqp/aqp.hpp
SOURCES	     += ../aqp/aqp.cpp
INCLUDEPATH  += ../aqp
HEADERS	     += ../textedit/textedit.hpp
SOURCES	     += ../textedit/textedit.cpp
RESOURCES    += ../textedit/textedit.qrc
INCLUDEPATH  += ../textedit
HEADERS	     += ../pagedesigner1/global.hpp
SOURCES	     += ../pagedesigner1/global.cpp
HEADERS	     += ../pagedesigner1/swatch.hpp
SOURCES	     += ../pagedesigner1/swatch.cpp
HEADERS	     += ../pagedesigner1/itemtypes.hpp
HEADERS	     += ../pagedesigner1/boxitem.hpp
SOURCES	     += ../pagedesigner1/boxitem.cpp
HEADERS	     += ../pagedesigner1/smileyitem.hpp
SOURCES	     += ../pagedesigner1/smileyitem.cpp
HEADERS	     += ../pagedesigner1/textitem.hpp
SOURCES	     += ../pagedesigner1/textitem.cpp
HEADERS	     += ../pagedesigner1/textitemdialog.hpp
SOURCES	     += ../pagedesigner1/textitemdialog.cpp
HEADERS	     += ../pagedesigner1/transformwidget.hpp
SOURCES	     += ../pagedesigner1/transformwidget.cpp
HEADERS	     += ../pagedesigner1/brushwidget.hpp
SOURCES	     += ../pagedesigner1/brushwidget.cpp
HEADERS	     += ../pagedesigner1/penwidget.hpp
SOURCES	     += ../pagedesigner1/penwidget.cpp
HEADERS	     += ../pagedesigner1/graphicsview.hpp
HEADERS	     += ../pagedesigner1/mainwindow.hpp
SOURCES	     += ../pagedesigner1/mainwindow.cpp
SOURCES	     += ../pagedesigner1/main.cpp
RESOURCES    += ../pagedesigner1/pagedesigner.qrc
INCLUDEPATH  += ../pagedesigner1
DEFINES	     += ANIMATE_ALIGNMENT
DEFINES	     += ANIMATE_IN_PARALLEL
DEFINES	     += NO_DYNAMIC_CAST
#DEFINES	     += SCREENSHOTS
DEFINES	     += ALTERNATIVE_RESIZING
win32 { INCLUDEPATH += . }
