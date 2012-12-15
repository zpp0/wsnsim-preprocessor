include(../wsnsim.pri)

TEMPLATE = app
TARGET = projectEditor
QT += gui core xml
INCLUDEPATH += . ../libs/projectData
DEPENDPATH += . model tools ui view widgets/modulesInfo widgets/params widgets widgets/modules settings editor
INCLUDEPATH += . view widgets/modulesInfo tools ui model widgets/params widgets widgets/modules settings editor

win32 {
    INCLUDEPATH += ../libs/luajit/src
    LIBS += ../../bin/libluajit.a
    LIBS += ../../bin/libprojectData.a
}

unix {
    INCLUDEPATH += . /usr/include/luajit-2.0
    LIBS += -lluajit-5.1
    LIBS += -L../../bin -lprojectData
}

# Input
HEADERS += model/modulesStorage.h \
           model/projectStorage.h \
           model/nodesStorage.h \
           model/errorsStorage.h \
           tools/moduleScanner.h \
           tools/moduleValidator.h \
           tools/moduleInfoFormatter.h \
           settings/settings.h \
           editor/luaEditor.h \
           editor/luaHighlighter.h \
           editor/codeEditor.h \
           view/mainwindow.h \
           view/modulesPage.h \
           view/modulePage.h \
           view/projectPage.h \
           view/simulatorPage.h \
           view/nodeTypePage.h \
           view/nodeTypesPage.h \
           widgets/errorAction.h \
           widgets/errorsPanel.h \
           widgets/modulesInfoDialog.h \
           widgets/renamingNodeTypeDialog.h \
           widgets/checkModule.h \
           widgets/nodeTypeSpinBox.h \
           widgets/interfaceInfo.h \
           widgets/projectTree.h \
           widgets/modulesInfo/modulesInfo.h \
           widgets/modules/infoWidget.h \
           widgets/modules/eventsWidget.h \
           widgets/modules/paramsWidget.h \
           widgets/modules/dependenciesWidget.h \
           widgets/params/generalParam.h \
           widgets/params/doubleParam.h \
           widgets/params/intParam.h \
           widgets/params/uintParam.h \
           widgets/params/stringParam.h \
           widgets/params/boolParam.h \
           widgets/params/nodesParam.h \
           widgets/params/timeParam.h \
           widgets/params/fileParam.h \
           widgets/params/tableParam.h \
           tools/modulesData.h \
           tools/modulesParams.h
FORMS += view/mainwindow.ui \
         view/modulesPage.ui \
         view/modulePage.ui \
         view/projectPage.ui \
         view/simulatorPage.ui \
         view/nodeTypePage.ui \
         view/nodeTypesPage.ui \
         editor/luaEditor.ui \
         settings/settings.ui \
         widgets/errorsPanel.ui \
         widgets/modulesInfoDialog.ui \
         widgets/renamingNodeTypeDialog.ui \
         widgets/modules/infoWidget.ui \
         widgets/modules/eventsWidget.ui \
         widgets/modules/paramsWidget.ui \
         widgets/modules/dependenciesWidget.ui \
         widgets/params/doubleParam.ui \
         widgets/params/intParam.ui \
         widgets/params/stringParam.ui \
         widgets/params/boolParam.ui \
         widgets/params/nodesParam.ui \
         widgets/params/tableParam.ui \
         widgets/params/timeParam.ui \
         widgets/params/fileParam.ui \
         widgets/interfaceInfo.ui
SOURCES += main.cpp \
           model/modulesStorage.cpp \
           model/projectStorage.cpp \
           model/nodesStorage.cpp \
           model/errorsStorage.cpp \
           tools/moduleScanner.cpp \
           tools/moduleValidator.cpp \
           tools/moduleInfoFormatter.cpp \
           editor/luaEditor.cpp \
           editor/luaHighlighter.cpp \
           editor/codeEditor.cpp \
           settings/settings.cpp \
           view/mainwindow.cpp \
           view/modulesPage.cpp \
           view/modulePage.cpp \
           view/projectPage.cpp \
           view/simulatorPage.cpp \
           view/nodeTypePage.cpp \
           view/nodeTypesPage.cpp \
           widgets/modules/infoWidget.cpp \
           widgets/modules/eventsWidget.cpp \
           widgets/modules/paramsWidget.cpp \
           widgets/modules/dependenciesWidget.cpp \
           widgets/modulesInfoDialog.cpp \
           widgets/renamingNodeTypeDialog.cpp \
           widgets/checkModule.cpp \
           widgets/errorAction.cpp \
           widgets/errorsPanel.cpp \
           widgets/nodeTypeSpinBox.cpp \
           widgets/interfaceInfo.cpp \
           widgets/projectTree.cpp \
           widgets/modulesInfo/modulesInfo.cpp \
           widgets/params/generalParam.cpp \
           widgets/params/doubleParam.cpp \
           widgets/params/intParam.cpp \
           widgets/params/uintParam.cpp \
           widgets/params/stringParam.cpp \
           widgets/params/boolParam.cpp \
           widgets/params/nodesParam.cpp \
           widgets/params/tableParam.cpp \
           widgets/params/timeParam.cpp \
           widgets/params/fileParam.cpp \
           tools/modulesData.cpp
RESOURCES += res/preprocessor.qrc
TRANSLATIONS = res/languages/preprocessor_en.ts \
               res/languages/preprocessor_ru.ts \
               res/languages/qt_en.ts \
               res/languages/qt_ru.ts
tr.commands = lrelease $$_PRO_FILE_
QMAKE_EXTRA_TARGETS += tr
POST_TARGETDEPS += tr
