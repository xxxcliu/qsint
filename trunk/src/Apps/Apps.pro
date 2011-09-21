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
    aboutdialog.h

SOURCES += \
    windowmenucontroller.moc \
    windowmenucontroller.cpp \
    systemopendialog.cpp \
    qtopendialog.cpp \
    plaintextdocumentfactory.cpp \
    plaintextdocument.moc \
    plaintextdocument.cpp \
    opendialogbase.cpp \
    mainwindow.moc \
    mainwindow.cpp \
    hypertextdocumentfactory.cpp \
    hypertextdocument.moc \
    hypertextdocument.cpp \
    helpmenucontroller.cpp \
    filemenucontroller.moc \
    filemenucontroller.cpp \
    documentviewcontroller.moc \
    documentviewcontroller.cpp \
    documentfactory.cpp \
    documentcontroller.moc \
    documentcontroller.cpp \
    document.cpp \
    createfiledialog.moc \
    createfiledialog.cpp \
    actioncontroller.moc \
    actioncontroller.cpp \
    aboutdialog.moc \
    aboutdialog.cpp

FORMS += \
    createfiledialog.ui \
    aboutdialog.ui

RESOURCES += \
    res/CommonIcons/CommonIcons.qrc \
    res/FileFormats/FileFormats.qrc
