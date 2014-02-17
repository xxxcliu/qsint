CONFIG(release,debug|release){
    LIBNAME = QSCharts
}

CONFIG(debug,debug|release){
    LIBNAME = QSChartsd
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
