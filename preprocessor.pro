include(../wsnsim.pri)

TEMPLATE = app
QT += gui
INCLUDEPATH += . ../libs/projectData
INCLUDEPATH += . ../simulator/interfaces/core/

# Input
HEADERS += mainwindow.h paramsPage.h projectInfo.h simulatorParams.h
FORMS += mainwindow.ui paramsPage.ui projectInfo.ui simulatorParams.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           paramsPage.cpp \
           projectInfo.cpp \
           simulatorParams.cpp
