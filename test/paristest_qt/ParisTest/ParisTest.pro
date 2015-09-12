#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T14:35:53
#
#-------------------------------------------------

QT       += core gui

DEFINES += "VSCP_QT"

INCLUDEPATH += "$(VSCP_HOME)/src/vscp/common"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParisTest
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    dialogrelaysetup.cpp \
    dialoginterfaceselect.cpp \
    dialogcanalsetup.cpp \
    dialoglevel2drvsetup.cpp \
    dialogselectdriverlevel.cpp \
    vscpinterface.cpp \
    "$(VSCP_HOME)/src/vscp/common/vscphelper.cpp" \
    "$(VSCP_HOME)/src/vscp/common/guid.cpp" \
    vscpworksconfig.cpp

HEADERS  += mainwindow.h \
    dialogrelaysetup.h \
    dialoginterfaceselect.h \
    dialogcanalsetup.h \
    dialoglevel2drvsetup.h \
    dialogselectdriverlevel.h \
    vscpinterface.h \
    "$(VSCP_HOME)/src/vscp/common/vscphelper.h" \
    "$(VSCP_HOME)/src/vscp/common/guid.h" \
    vscpworksconfig.h

FORMS    += mainwindow.ui \
    dialogrelaysetup.ui \
    dialoginterfaceselect.ui \
    dialogcanalsetup.ui \
    dialoglevel2drvsetup.ui \
    dialogselectdriverlevel.ui

RESOURCES += \
    resources.qrc
