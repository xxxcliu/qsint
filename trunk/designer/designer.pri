TEMPLATE = app

include(../src/Core/Core.pri)

LIBS += -L../../lib -l$$LIBNAME

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../lib/QSCore.lib
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../lib/QSCored.lib
}

