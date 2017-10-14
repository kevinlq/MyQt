import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Window {
    visible: true
    width: 680
    height: 420
    color: "#E4E4ED"
    title: qsTr("系统环境变量配置工具")

    ListModel {
        id:tableModel

    }

    TableView {
        id: tableView
        anchors.fill: parent;
        model: tableModel

        TableViewColumn {
            role: "variable"
            title: qsTr("变量")
        }

        TableViewColumn {
            role: "value"
            title: qsTr("值")
        }
    }
}
