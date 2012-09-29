import QtQuick 1.1


Rectangle {
    id: mainWindow
    width: 1366
    height: 768
    color: appBackground

    property int topBarSize: 144
    property int barSize: 120
    property int tileMargin: 6
    property int tileHeaderFontSize: mainWindow.height/30
    property int tileInfoFontSize: 20
    property int appHeaderFontSize: 36
    property string appBackground: "#484848"
    property string tileBackground: "#00aaff"
    property string textColor: "white"
    property string uiFont: "Helvetica-Neue"

//Splashscreen
     SplashScreen{
            id:splashScreen
            imageSource: "qrc:///img/SplashScreen.png"
            anchors.fill: mainWindow
            z:1
        }

//Topbar
    Rectangle {
            id: topBar
            anchors.left: leftBar.right
            anchors.top: parent.top
            height: topBarSize
            color: appBackground

        }

//Leftbar
        Rectangle {
            id: leftBar
            x: 0
            y: 0
            anchors.left: parent.left
            anchors.top: parent.top
            width: barSize
            height: parent.height
            color: appBackground
            anchors.leftMargin: 0
            anchors.topMargin: 0
}
//AddButton
        PlusButtonLight {
             id:addButton
             anchors.bottom: leftBar.bottom
             anchors.bottomMargin: 40
             anchors.left: leftBar.left
             anchors.leftMargin: 40
             onClicked: NumberAnimation { target:addScreen; property:"opacity"; to:1; duration: 400}
         }

//GridView
        GridView {
            id: grid
            anchors.left: leftBar.right
            anchors.top: topBar.bottom
            flow: GridView.TopToBottom
            width: parent.width - leftBar.width
            height: parent.height - topBar.height - bottomBar.height
            cellHeight: parseInt(grid.height / 2)
            cellWidth: parseInt(cellHeight * 1.1)
            clip: false
            focus: true
            model: datalist //dataSource
            delegate: FlipTile{}

            states: State {
                when: grid.movingHorizontally
                PropertyChanges { target: horizontalScrollBar; opacity: 1 }
            }

            transitions: Transition {
                NumberAnimation { properties: "opacity"; duration: 400 }
            }
        }

//Bottombar
        Rectangle {
            id: bottomBar
            anchors.top: grid.bottom
            anchors.left: leftBar.right
            width: parent.width - leftBar.width
            height: barSize
            color: appBackground

         ShutdownButton {
         anchors.bottom: parent.bottom
         anchors.bottomMargin: width/2
         anchors.right:parent.right
         anchors.rightMargin: width/2
         onReleased: Qt.quit()}
        }

//Scrollbar
        Scrollbar {
           id: horizontalScrollBar
           width: parent.width; height: 6
           anchors.bottom: parent.bottom
           anchors.left: parent.left
           opacity: 0
           orientation: Qt.Horizontal
           position: grid.visibleArea.xPosition
           pageSize: grid.visibleArea.widthRatio
        }
//AddScreen
        AddScreen {
          id:addScreen
          opacity: 0;
       }

}
