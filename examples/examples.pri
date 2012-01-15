TEMPLATE = app

include(../src/Core/Core.pri)

INCLUDEPATH = ../../../include

LIBS += -L../../../lib -l$$LIBNAME

#message("examples.pri:")
#message($$CONFIG)
#message($$LIBNAME)

#CONFIG(release,debug|release){
 #   PRE_TARGETDEPS += ../../../lib/$$LIBNAME.$$LIB_SUFFIX
#}

#CONFIG(debug,debug|release){
#    PRE_TARGETDEPS += ../../../lib/$$LIBNAME.$$LIB_SUFFIX
#}

