include (Charts.pri)
include (../src.pri)

INCLUDEPATH += ./ ../Core


HEADERS += \
    plotterbase.h \
    barchartplotter.h \
    axisbase.h \
    piechart.h \
	ringchart.h \
    paintscheme.h

SOURCES += \
    plotterbase.cpp \
    barchartplotter.cpp \
    axisbase.cpp \
    piechart.cpp \
	ringchart.cpp \
    paintscheme.cpp
