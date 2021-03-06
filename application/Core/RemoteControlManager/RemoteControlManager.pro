# -------------------------------------------------
# Project created by QtCreator 2009-10-05T21:08:20
# -------------------------------------------------
QT += network
QT -= gui
TARGET = RemoteControlManager

TEMPLATE = lib

include(../../Common/common.pri)
include(../../Libs/protobuf.pri)

CONFIG += staticlib \
   link_prl \
   create_prl
INCLUDEPATH += . \
   ../..

DEFINES += REMOTECONTROLMANAGER_LIBRARY
SOURCES += priv/RemoteControlManager.cpp \
    priv/RemoteConnection.cpp \
    priv/Builder.cpp \
    ../../Protos/gui_protocol.pb.cc \
    ../../Protos/common.pb.cc \
    priv/Log.cpp
HEADERS += IRemoteControlManager.h \
    priv/RemoteControlManager.h \
    priv/RemoteConnection.h \
    Builder.h \
    priv/Log.h \
    ../../Protos/common.pb.h \
    ../../Protos/gui_protocol.pb.h
