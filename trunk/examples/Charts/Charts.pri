include(../../src/Charts/Charts.pri)

LIBS += -L../../../../lib -l$$LIBNAME

include(../examples.pri)

win32 {

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSCharts.lib
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSChartsd.lib
}

}
