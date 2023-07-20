!contains(DEFINES, __param__) {
    message("params for signal loaded");

    DEFINES += __param__

    HEADERS +=  $$PWD/parametrs.hpp

    INCLUDEPATH += $$PWD/
}
