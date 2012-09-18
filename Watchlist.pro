
folder_01.source = qml/Watchlist
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
folder_02.source = res
DEPLOYMENTFOLDERS = folder_02

SOURCES += src/main.cpp \
    src/tvshowdata.cpp \
    src/tvshow.cpp \
    src/testclass.cpp \

include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    res/res.qrc

HEADERS += \
    src/tvshowdata.h \
    src/tvshow.h \
    src/testclass.h

OTHER_FILES += \
    qml/Watchlist/main.qml \
    SplashScreen.qml
