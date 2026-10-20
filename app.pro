TARGET = app
TEMPLATE = app
QT += core widgets gui
CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/model.cpp \
    src/center.cpp \
    src/edge.cpp \
    src/point.cpp \
    src/model_draw.cpp \
    src/file.cpp \
    src/exit_code.cpp \
    src/cmd_manager.cpp \
    src/actions.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/mainwindow.h \
    include/model_draw.h \
    include/model.h \
    include/center.h \
    include/edge.h \
    include/point.h \
    include/file.h \
    include/exit_code.h \
    include/cmd_manager.h \
    include/actions.h

FORMS += \
    ui/mainwindow.ui

INCLUDEPATH += include

DESTDIR = bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui