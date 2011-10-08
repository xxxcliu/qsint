TEMPLATE = app

include(../src/Core/Core.pri)

LIBS += -L../../lib -l$$LIBNAME

win32 {

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../lib/$$LIBNAME
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../lib/$$LIBNAME
}

}

