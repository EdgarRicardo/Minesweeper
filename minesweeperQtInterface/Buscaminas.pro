QT += widgets
QT += charts
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
        main.cpp \
    menu.cpp \
    buscaminasmatriz.cpp \
    datosbuscaminas.cpp \
    juego.cpp

HEADERS += \
    menu.h \
    headerqt.h \
    buscaminasmatriz.h \
    datosbuscaminas.h \
    juego.h
