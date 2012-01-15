TARGET = app

INCLUDEPATH += $(QSINTDIR)/include

include($(QSINTDIR)/src/Apps/Apps.pri)
LIBS += -l$$LIBNAME

include($(QSINTDIR)/src/Core/Core.pri)
LIBS += -l$$LIBNAME
