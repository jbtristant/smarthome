import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground {
    id: pageBackground1
    width: 824
    height: 552

    GridLayout {
        x: 124
        y: 20
        anchors.horizontalCenterOffset: -10
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 2

        GroupBox {
            id: groupBox1
            title: qsTr("Living Room")

            GridLayout {
                rows: 4
                columns: 2

                RadioButton {
                    id: radioButton1
                    text: qsTr("Smoke Detector")
                }

                Button {
                    id: button1
                    text: qsTr("Test")
                }

                RadioButton {
                    id: radioButton2
                    text: qsTr("Movement Detector")
                }

                Button {
                    id: button2
                    text: qsTr("Test")
                }

                Switch {
                    id: switch1
                    text: qsTr("Window 01")
                }

                Label {
                    id: label1
                    text: switch1.checked ? "Open" : "Closed"
                }

                Switch {
                    id: switch2
                    text: qsTr("Window 02")
                }

                Label {
                    id: label2
                    text: switch2.checked ? "Open" : "Closed"
                }
            }
        }
    }
}
