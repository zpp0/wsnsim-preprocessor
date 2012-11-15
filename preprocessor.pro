include(../wsnsim.pri)

TEMPLATE = app
QT += gui
CONFIG += console
INCLUDEPATH += . ../libs/projectData ../libs/moduleData
DEPENDPATH += . model tools ui view view/modulesInfo view/paramsInfo
INCLUDEPATH += . view view/modulesInfo tools ui model view/paramsInfo

# Input
HEADERS += mainwindow.h \
           model/modulesStorage.h \
           model/projectStorage.h \
           tools/checkModule.h \
           tools/moduleScanner.h \
           tools/projectScanner.h \
           tools/projectTree.h \
           tools/types.h \
           view/modulesPage.h \
           view/paramsPage.h \
           view/projectInfo.h \
           view/simulatorParams.h \
           view/modulesInfo/modulesInfo.h \
           view/paramsInfo/generalParam.h \
           view/paramsInfo/doubleParam.h \
           view/paramsInfo/intParam.h \
           view/paramsInfo/uintParam.h \
           view/paramsInfo/stringParam.h \
           view/paramsInfo/boolParam.h \
           view/paramsInfo/nodesParam.h \
           view/paramsInfo/timeParam.h \
           view/paramsInfo/fileParam.h \
           view/paramsInfo/tableParam.h
FORMS += mainwindow.ui \
         view/modulesPage.ui \
         view/paramsPage.ui \
         view/projectInfo.ui \
         view/simulatorParams.ui \
         view/paramsInfo/doubleParam.ui \
         view/paramsInfo/intParam.ui \
         view/paramsInfo/stringParam.ui \
         view/paramsInfo/boolParam.ui \
         view/paramsInfo/nodesParam.ui \
         view/paramsInfo/tableParam.ui \
         view/paramsInfo/timeParam.ui \
         view/paramsInfo/fileParam.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           model/modulesStorage.cpp \
           model/projectStorage.cpp \
           tools/checkModule.cpp \
           tools/moduleScanner.cpp \
           tools/projectScanner.cpp \
           tools/projectTree.cpp \
           view/modulesPage.cpp \
           view/paramsPage.cpp \
           view/projectInfo.cpp \
           view/simulatorParams.cpp \
           view/modulesInfo/modulesInfo.cpp \
           view/paramsInfo/doubleParam.cpp \
           view/paramsInfo/intParam.cpp \
           view/paramsInfo/uintParam.cpp \
           view/paramsInfo/stringParam.cpp \
           view/paramsInfo/boolParam.cpp \
           view/paramsInfo/nodesParam.cpp \
           view/paramsInfo/tableParam.cpp \
           view/paramsInfo/timeParam.cpp \
           view/paramsInfo/fileParam.cpp
