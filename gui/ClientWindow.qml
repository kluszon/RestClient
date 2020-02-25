import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: root
    color: "#8c8686"
    Item{
        id: rctBody
        anchors.fill: parent
        anchors.margins: 20

        Item{
            id: gridButtons
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            ComboBox{
                id: cbRequestType
                currentIndex: 0
                model: [ "GET", "POST"]
                height: 50
                width: 120
                anchors.left: parent.left
                anchors.top: parent.top
            }
            TextField{
                id: tfUrl
                width: 510
                height: 50
                text: ""
                anchors.top: parent.top
                anchors.left: cbRequestType.right
            }
            Button{
                height: 50
                width: 120
                text: "Send"
                onReleased: restClient.post(tfUrl.text)
                anchors.top: parent.top
                anchors.left: tfUrl.right
                anchors.leftMargin: 10
            }
        }
        Rectangle{
            id: rctBodyList
            anchors.top: gridButtons.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            height: 200
            border.color: "grey"
            Component{
                id: listDelegate
                Rectangle{
                    width: lvBodyList.width
                    height: 50
                    color: "#e6dbdb"
                    border.color: lvBodyList.currentIndex == index ? "blue" : "grey"
                    border.width: 2
                    Row{
                        id: row
                        anchors.fill: parent
                        spacing: 2
                        TextField
                        {
                            id: tfKey
                            width: lvBodyList.width/2 - row.spacing/2
                            height: 50
                            text: key
                            placeholderText: "key"
                            background: Rectangle {
                                implicitWidth: tfKey.width
                                implicitHeight: tfKey.height
                                color: "transparent"
                                border.width: 0
                            }
                            onPressed: {
                                lvBodyList.currentIndex = index
                            }
                        }
                        TextField
                        {
                            width: lvBodyList.width/2 - row.spacing/2
                            height: 50
                            text: value
                            placeholderText: "value"
                            background: Rectangle {
                                implicitWidth: tfKey.width
                                implicitHeight: tfKey.height
                                color: "transparent"
                                border.width: 0
                            }
                            onPressed: {
                                lvBodyList.currentIndex = index
                                console.log(index)
                            }
                        }
                    }
                }
            }
            ListView{
                id: lvBodyList
                anchors.fill: parent
                model: requestBodyModel
                clip: true
                delegate: listDelegate
                header:
                    Rectangle{
                        width: lvBodyList.width
                        height: 50
                        color: "#736d6d"
                        Row{
                            id: row
                            anchors.fill: parent
                            spacing: 2
                            Label
                            {
                                id: tfKey
                                width: lvBodyList.width/2 - row.spacing/2
                                height: 50
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment:  Text.AlignVCenter
                                text: "Key"
                                color: "white"
                                font.pointSize: 15
                            }
                            Label
                            {
                                width: lvBodyList.width/2 - row.spacing/2
                                height: 50
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment:  Text.AlignVCenter
                                text: "Value"
                                color: "white"
                                font.pointSize: 15
                            }
                        }
                    }
                }
        }
        Item{
            id: gridListButtons
            anchors.top: rctBodyList.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            Button{
                id: btnAdd
                anchors.top: parent.top
                anchors.right: btnRemove.left
                anchors.rightMargin: 20
                height: 50
                width: 120
                text: "Add Row"
                onReleased: requestBodyModel.addRow("1","2")
            }
            Button{
                id: btnRemove
                anchors.top: parent.top
                anchors.right: parent.right
                height: 50
                width: 120
                text: "Remove Row"
                enabled: lvBodyList.count > 0 ? true : false
                onReleased: requestBodyModel.removeRow(lvBodyList.currentIndex)

            }
        }
        Flickable{
            anchors.top: gridListButtons.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            contentWidth: control.width;
            contentHeight: control.contentHeight
            ScrollBar.vertical: ScrollBar { }
            TextArea{
                id: control
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: window.height/2
                width: window.width - rctBody.anchors.margins * 2
                text: restClient.response

                background: Rectangle {
                        implicitWidth: rctBody.width
                        implicitHeight: rctBody.height/2
                        color: "white"
                        border.color: "grey"
                    }
            }
        }
    }
}