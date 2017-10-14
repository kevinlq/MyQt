import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480

    Rectangle {
        id:inp;
        width: parent.width - 10
        height: 30

        color: "green"

        anchors.centerIn: parent
    }
}
