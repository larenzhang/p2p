# -------------------------------------------------
# Project created by QtCreator 2016-10-07T14:24:39
# -------------------------------------------------
QT += network \
    sql
TARGET = chatTimeServer
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    tcpsockserver.cpp \
    tcpconthread.cpp \
    sqlitedb.cpp \
    mysqlquerymodel.cpp
HEADERS += mainwindow.h \
    tcpsockserver.h \
    tcpconthread.h \
    sqlitedb.h \
    mysqlquerymodel.h
FORMS += mainwindow.ui
