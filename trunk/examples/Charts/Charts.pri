include(../examples.pri)

include(../../src/Charts/Charts.pri)

LIBS += -L../../../../lib -l$$LIBNAME


CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSCharts.lib
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSChartsd.lib
}

