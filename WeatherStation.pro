#-------------------------------------------------
#
# Project created by QtCreator 2013-11-06T22:19:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherStation
TEMPLATE = app


SOURCES += main.cpp\
        weatherstationgui.cpp\
        utilities.cpp

HEADERS  += weatherstationgui.h\
            utilities.h

FORMS    += weatherstationgui.ui

CONFIG   += console

RESOURCES += BCnorthWeatherData.csv
