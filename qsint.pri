CONFIG(release,debug|release){
    UI_DIR = release
}

CONFIG(debug,debug|release){
    UI_DIR = debug
}

win32 {
    LIB_SUFFIX = lib
}

unix {
    LIB_SUFFIX = so
}

