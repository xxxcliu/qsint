TEMPLATE = app

include(../src/Core/Core.pri)

INCLUDEPATH = ../../../include

LIBS += -L../../../lib -l$$LIBNAME

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
