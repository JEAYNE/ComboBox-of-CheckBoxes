QT      += core gui widgets
CONFIG  += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060800    # disables all the APIs deprecated before Qt 6.8.0
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/mainwindow.h

FORMS   += \
    src/mainwindow.ui
