include(../../src/Apps/Apps.pri)

LIBS += -L../../../../lib -l$$LIBNAME

include(../examples.pri)


win32 {

CONFIG(release,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSApps.lib
}

CONFIG(debug,debug|release){
    PRE_TARGETDEPS += ../../../lib/QSAppsd.lib
}

}
