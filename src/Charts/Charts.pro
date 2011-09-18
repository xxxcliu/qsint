CONFIG(release,debug|release){
    LIBNAME = QSCharts
}

CONFIG(debug,debug|release){
    LIBNAME = QSChartsd
}

include (../src.pri)


HEADERS += \
    plotterbase.h \
    barchartplotter.h \
    axisbase.h

SOURCES += \
    plotterbase.cpp \
    barchartplotter.cpp \
    axisbase.cpp

INCLUDEPATH += ./

