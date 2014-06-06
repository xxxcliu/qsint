CONFIG(release,debug|release){
    UI_DIR = release
}

CONFIG(debug,debug|release){
    UI_DIR = debug
}

win32 {
    LIB_SUFFIX = lib
}

win32-msvc*{
    QMAKE_CXXFLAGS += /MP /openmp- /fp:fast /arch:SSE2
}

win32-msvc2013{
    QMAKE_CXXFLAGS += /FS
}


unix {
    LIB_SUFFIX = so
}

