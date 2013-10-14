TARGET = qsintplugin

include(../designer.pri)

CONFIG      += designer plugin debug_and_release

HEADERS     = scrollpannerplugin.h \
    colorgridplugin.h \
    qsintplugin.h \
    colorbuttonplugin.h \
    actionboxplugin.h \
    actionlabelplugin.h \
    actionpanelplugin.h \
    actiongroupplugin.h \
    pathpickerplugin.h \
    optionsliderplugin.h \
#    multicomboboxplugin.h \
    spinsliderplugin.h

SOURCES     = scrollpannerplugin.cpp \
    colorgridplugin.cpp \
    qsintplugin.cpp \
    colorbuttonplugin.cpp \
    actionboxplugin.cpp \
    actionlabelplugin.cpp \
    actionpanelplugin.cpp \
    actiongroupplugin.cpp \
    pathpickerplugin.cpp \
    optionsliderplugin.cpp \
#    multicomboboxplugin.cpp \
    spinsliderplugin.cpp

RESOURCES   = res/icons.qrc

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target
