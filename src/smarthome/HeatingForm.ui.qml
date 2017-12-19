import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground {
    id: pageBackground1
    width: 824
    height: 552

    GridLayout {
        x: 53
        y: 8
        anchors.horizontalCenterOffset: -57
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 2

        GroupBox {
            id: groupBox1
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.preferredHeight: 280
            Layout.preferredWidth: 318
            title: qsTr("Living Room")

            Label {
                id: label2
                x: 221
                y: 16
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label1
                x: 15
                y: 15
                text: qsTr("Target")
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBar2
                x: 147
                y: 131
                width: 200
                rotation: -90
                value: 0.5
            }

            ProgressBar {
                id: progressBar1
                x: -59
                y: 131
                value: dial.position
                rotation: -90
            }

            Dial {
                id: dial
                x: 107
                y: 114
            }
        }
    }
}
