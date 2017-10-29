import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: _root
    visible: true
    width: 440
    height: 350

    title: qsTr("SVG操作demo")


    Column {
        spacing: 10
        x: 10; y: 10

        Row {
            spacing: 40
            width: parent.width
            height: parent.height*0.8 > 200 ? 200:parent.height * 0.8
            //原始SVG图片
            Image {
                id: pic_org
                source: "images/we.svg"
                //width: parent.width * 0.5
                height: parent.height
            }

            //改变后的SVG图片
            Image {
                id: pic_aft
                source: "images/we.svg"
                //width: parent.width*0.5
                height: parent.height
            }

        }

        Row {
            spacing: 10
            Text {
                text: "颜色:"
            }
            TextEdit {
                text: "#FFFFFF"
                enabled: true
            }
            Text {
                text: "修改后:"
            }
            TextEdit {
                text: "xxxxx"
            }
        }

        Button {
            text: "确认修改"
        }
    }

}
