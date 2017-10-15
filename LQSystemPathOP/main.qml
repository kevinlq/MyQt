import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4

import L.Qt.SystemPathInfo 1.0

Window {
    visible: true
    width: 680
    height: 420
    color: "#E4E4ED"
    title: qsTr("系统环境变量配置工具")

    property int txtWidth: 100

    SystemPathInfo {
        id:sysObj
    }

    Label {
        text: "当前系统:"
        width: txtWidth
        height: 30
        x: 4; y: 4
        font.pixelSize: 20
    }
    Label {
        text: "windows7"
        width: 120; height: 30
        x: 4 + txtWidth; y: 4
        font.pixelSize: 20
    }

    Button{
        id: showId
        text: qsTr("显示")
        width: 80; height:30
        x: 4 + txtWidth * 2; y: 4

        onClicked: {
            sysObj.slotOnSend();
        }
    }

    TextEdit{
        id: tetInfo
        width: parent.width
        height: parent.height - 40
        x:4; y: 30 *2 + 4
        font.family: "Helvetica"
        font.pointSize: 16
        text: qsTr("system")
        focus: true
        color: "blue"
        wrapMode: TextEdit.Wrap
    }

    Connections {
        target: sysObj
        onPathChanged:{
            tetInfo.text = strPath
        }
    }

}
