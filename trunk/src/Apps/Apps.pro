include (Apps.pri)
include (../src.pri)


INCLUDEPATH += ./ ../Core

HEADERS += \
    windowmenucontroller.h \
    systemopendialog.h \
    qtopendialog.h \
    plaintextdocumentfactory.h \
    plaintextdocument.h \
    opendialogbase.h \
    mainwindow.h \
    hypertextdocumentfactory.h \
    hypertextdocument.h \
    helpmenucontroller.h \
    filemenucontroller.h \
    documentviewcontroller.h \
    documentfactory.h \
    documentcontroller.h \
    document.h \
    createfiledialog.h \
    createdialogbase.h \
    actioncontroller.h \
    aboutdialog.h \
    menuactioncontroller.h \
    documentaction.h

SOURCES += \
    windowmenucontroller.cpp \
    systemopendialog.cpp \
    qtopendialog.cpp \
    plaintextdocumentfactory.cpp \
    plaintextdocument.cpp \
    opendialogbase.cpp \
    mainwindow.cpp \
    hypertextdocumentfactory.cpp \
    hypertextdocument.cpp \
    helpmenucontroller.cpp \
    filemenucontroller.cpp \
    documentviewcontroller.cpp \
    documentfactory.cpp \
    documentcontroller.cpp \
    document.cpp \
    createfiledialog.cpp \
    actioncontroller.cpp \
    aboutdialog.cpp \
    menuactioncontroller.cpp \
    documentaction.cpp

FORMS += \
    createfiledialog.ui \
    aboutdialog.ui

RESOURCES += \
    res/CommonIcons/CommonIcons.qrc \
    res/FileFormats/FileFormats.qrc
