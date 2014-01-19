include (../Apps.pri)

TARGET = simpleapp

HEADERS += \
    testmenucontroller.h \
    mainwidget.h

SOURCES += \
    mainwidget.cpp \
    testmenucontroller.cpp \
    main.cpp

RESOURCES += \
    res/local.qrc \
    ../../../src/Apps/res/CommonIcons/CommonIcons.qrc \
    ../../../src/Apps/res/FileFormats/FileFormats.qrc
