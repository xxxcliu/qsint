TARGET = app

INCLUDEPATH += $(QSINTDIR)/include

include($(QSINTDIR)/src/Core/Core.pri)
LIBS += -l$$LIBNAME
