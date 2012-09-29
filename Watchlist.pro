SOURCES += src/main.cpp \
    src/tvshowdata.cpp \
    src/tvshow.cpp \
    src/controller.cpp \
    src/database.cpp \
    src/cursorshapearea.cpp \
    src/mainview.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    res/res.qrc

HEADERS += \
    src/tvshowdata.h \
    src/tvshow.h \
    src/controller.h \
    src/database.h \
    src/cursorshapearea.h \
    src/mainview.h


OTHER_FILES += \
    qml/Watchlist/main.qml \
    res/qml/Scrollbar.qml \
    res/qml/main.qml \
    res/qml/FlipTile.qml \
    res/qml/AddScreen.qml \
    res/qml/SplashScreen.qml \
    res/qml/PlusButtonLight.qml \
    res/qml/PlusButtonDark.qml \
    res/qml/MinusButtonDark .qml \
    res/qml/MinusButtonDark .qml \
    res/qml/MinusButtonDark.qml \
    res/qml/RightButton.qml \
    res/qml/LeftButton.qml \
    icons.rc \
    res/qml/CloseScreenButton.qml \
    res/qml/ShutdownButton.qml

QT           += sql

#Mac Icons
ICON = res/icons/icns/icon.icns
#Windows Icons
RC_FILE = icons.rc
