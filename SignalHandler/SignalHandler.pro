QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    signalhandler.cpp \
    signalhandlermath.cpp \
    signalsocketmanager.cpp

HEADERS += \
    signalhandler.h \
    signalhandlermath.h \
    signalsocketmanager.h

FORMS += \
    signalhandler.ui

include(for_student/param.pri)

LIBS += -lqwt-qt5
LIBS += -lfftw3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
