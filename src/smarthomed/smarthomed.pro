QT += core network serialport
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
           daemon.cpp \
	   server.cpp \
	   client.cpp \
           homeworker.cpp \
           homecontroller.cpp

HEADERS += daemon.h \
	   server.h \
	   client.h \
           homeworker.h \
           homecontroller.h
	   
