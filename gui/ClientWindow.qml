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
                onReleased: {
                    switch(cbRequestType.currentIndex)
                    {
                        case 0: restClient.get(tfUrl.text)
                        break;
                        case 1: restClient.post(tfUrl.text)
                        break;
                        default:
                    }
                }
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
                            onEditingFinished: {
                                requestBodyModel.setData(requestBodyModel.index(index, 0), tfKey.text, 0)
                            }
                        }
                        TextField
                        {
                            id: tfValue
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
                            onEditingFinished: {
                                requestBodyModel.setData(requestBodyModel.index(index, 0), tfValue.text, 1)
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
                headerPositioning: ListView.OverlayHeader
                header:
                    Rectangle{
                        width: lvBodyList.width
                        height: 50
                        color: "#736d6d"
                        z: 2
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
                onReleased: requestBodyModel.addRow("","")
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            ScrollBar.vertical: ScrollBar { }
            TextArea.flickable:
                TextArea{
                    id: control
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: restClient.response

                    background: Rectangle {
                            implicitWidth: rctBody.width
                            implicitHeight: control.height
                            color: "white"
                            border.color: "grey"
                        }
                }
        }
    }
}
