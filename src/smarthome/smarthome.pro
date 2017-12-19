QT += network qml quick quickcontrols2

CONFIG += c++11

SOURCES += main.cpp \
    clientcontroller.cpp \
    clientworker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    clientcontroller.h \
    clientworker.h
