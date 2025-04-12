import QtQuick

Window {
    id: window
    visible: true
    title: "Lab6"
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
            color: "white"
            font.pointSize: 10
        }
    }
}
