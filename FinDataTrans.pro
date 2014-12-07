#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T21:44:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinDataTrans
TEMPLATE = app


SOURCES += main.cpp\
        datatransfer.cpp

HEADERS  += datatransfer.h

FORMS    += datatransfer.ui



DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP
DEFINES += NOMINMAX

#lib settings for debug
LIBS += -LC:/cpp/DB_Libs -lmyUtilsD
LIBS += -LC:/cpp/DB_Libs -lSQLDatabaseD

LIBS += -LC:/cpp/boost/bin

INCLUDEPATH += C:/cpp/DB_Includes
INCLUDEPATH += C:/cpp/boost/include
