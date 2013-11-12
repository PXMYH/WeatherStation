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
        utilities.cpp\
        computation.cpp\
        calculation.cpp

HEADERS  += weatherstationgui.h\
            utilities.h\
            types.h\
            computation.h\
            calculation.h

FORMS    += weatherstationgui.ui

CONFIG   += console

#RESOURCES += BCnorthWeatherData.csv

RESOURCES += \
    BCnorthWeatherData.qrc


