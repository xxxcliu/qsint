include(../../src/Charts/Charts.pri)

LIBS += -L../../../../lib -l$$LIBNAME

include(../examples.pri)

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../../lib/$$LIBNAME.$$LIB_SUFFIX
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../../lib/$$LIBNAME.$$LIB_SUFFIX
}
