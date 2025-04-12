import QtQuick

Window {
    id: window
    visible: true
    title: "Lab7"
    width: 400
    height: 400

    Rectangle {
        id: topLeft
        width: 150
        height: 150
        color: "#800000"
        anchors.top: parent.top
        anchors.left: parent.left

        Text {
            anchors.centerIn: parent
            text: `color: ${parent.color}`
            color: "black"
            font.pointSize: 10
        }
    }

    Rectangle {
        id: topRight
        width: 150
        height: 150
        color: "#FF0000"
        anchors.top: parent.top
        anchors.right: parent.right

        Text {
            anchors.centerIn: parent
            text: `color: ${parent.color}`
            color: "black"
            font.pointSize: 10
        }
    }

    Rectangle {
        id: bottomLeft
        width: 150
        height: 150
        color: "#00FF00"
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Text {
            anchors.centerIn: parent
            text: `color: ${parent.color}`
            color: "black"
            font.pointSize: 10
        }
    }

    Rectangle {
        id: bottomRight
        width: 150
        height: 150
        color: "#008800"
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Text {
            anchors.centerIn: parent
            text: `color: ${parent.color}`
            color: "black"
            font.pointSize: 10
        }
    }

    Rectangle {
        id: center
        width: 150
        height: 150
        color: "royalBlue"
        anchors.centerIn: parent
        radius: 25
        rotation: -45

        Text {
            anchors.centerIn: parent
            text: `color: ${parent.color}\nradius: ${parent.radius}\nrotation: ${parent.rotation}`
            color: "black"
            font.pointSize: 10
        }
    }

    Row {
        id: palette
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60

        Repeater {
            model: ["red", "orange", "yellow", "green", "skyBlue", "blue", "purple"]

            Rectangle {
                width: 15
                height: 15
                color: modelData
                border.color: "black"

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: mouse => {
                        const color = Qt.color(modelData);
                        switch (mouse.button) {
                            case Qt.LeftButton:
                                center.color = color;
                                break;

                            case Qt.RightButton:
                                center.color = Qt.rgba(
                                    Math.min(color.r + 0.2, 1),
                                    Math.min(color.g + 0.2, 1),
                                    Math.min(color.b + 0.2, 1),
                                    color.a
                                );
                                break;
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        width: 100
        height: 30
        color: "lightGray"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        radius: 5
        border.color: "gray"

        Text {
            anchors.centerIn: parent
            text: "Вихід"
            color: "black"
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor

            onClicked: Qt.quit()
        }
    }
}
