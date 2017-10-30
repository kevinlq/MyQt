import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Window {
    id: _root
    visible: true
    width: 440
    height: 350

    title: qsTr("SVG操作demo")

    property string m_strFilePath: ""

    FileDialog {
        id: svgFile
        visible: false
        title: "选择SVG图片"
        nameFilters: [ "Image files (*.svg )" ]
        selectMultiple: false
        onAccepted: {
            m_strFilePath = svgFile.fileUrl
            _nameput.text = m_strFilePath
        }

        Component.onCompleted: {
            svgFile.visible = false
        }
    }


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
                height: parent.height
                fillMode: Image.PreserveAspectFit
                cache: false
            }

            //改变后的SVG图片
            Image {
                id: pic_aft
                source: "images/we.svg"
                height: parent.height
                fillMode: Image.PreserveAspectFit
                cache: false
            }

        }

        Row {
            spacing: 10

            Text {
                id: filePath
                text: "SVG图片:"
            }

            TextField {
                id: _nameput
                style: TextFieldStyle {
                    textColor: "black"
                }
                width: parent.width *0.6

                onTextChanged: {
                    pic_org.source = m_strFilePath
                }
            }
            Button {
                text: "浏览"

                onClicked: {
                    svgFile.visible = true

                }
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

            TextField {
                style: TextFieldStyle {
                    textColor: "black"
                }
            }
        }

        Button {
            text: "确认修改"

            onClicked: {
                pic_org.source = m_strFilePath
            }
        }
    }

}
