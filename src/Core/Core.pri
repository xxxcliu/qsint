CONFIG(release,debug|release){
    LIBNAME = QSCore
}

CONFIG(debug,debug|release){
    LIBNAME = QSCored
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
