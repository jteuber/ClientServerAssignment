TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

# for ASIO
LIBS += -pthread

SOURCES += \
        main.cpp \
    TcpServer.cpp \
    Client.cpp

HEADERS += \
    TcpServer.h \
    Client.h
