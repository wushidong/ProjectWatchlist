import QtQuick 1.1


Item {

    property string toolTip
    property bool showToolTip: false

    anchors.fill: parent

    Rectangle {

        id: toolTipRectangle
        anchors.left:parent.left
        anchors.leftMargin:20
        anchors.top: parent.top
        anchors.topMargin: -40
        width: toolTipText.width + 10
        height: toolTipText.height + 10
        z: 800

        opacity: toolTip != "" && showToolTip ? 1 : 0

        color: mainWindow.tileBackground
        border.color: mainWindow.textColor

        Text {

            id: toolTipText
            text: toolTip
            color: mainWindow.textColor3
            anchors.centerIn: parent
        }

        Behavior on opacity {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
                duration: 250
            }
        }
    }

    MouseArea {

        id: mouseArea
        anchors.fill: parent
        onEntered: showTimer.start()
        onExited: { showToolTip = false; showTimer.stop(); }
        hoverEnabled: true

    }

    Timer {

        id: showTimer
        interval: 250
        onTriggered: showToolTip = true;

    }
}
