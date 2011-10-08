TEMPLATE = app

include(../src/Core/Core.pri)

INCLUDEPATH = ../../../include

LIBS += -L../../../lib -l$$LIBNAME

#message("examples.pri:")
#message($$CONFIG)
#message($$LIBNAME)

win32{

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSCore.lib
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSCored.lib
}

}
