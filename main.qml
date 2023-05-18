import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "gui"

ApplicationWindow{
    id: window
    visible: true
    width: 800
    height: 640
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    title: qsTr("Rest client") + " " + Qt.application.version
    ClientWindow{
        anchors.fill: parent
    }
}
