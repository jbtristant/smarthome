import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground {
    width: 824
    height: 552
    property alias lblActualText: lblActual.text
    property alias progressBarActualTemperatureValue: progressBarActualTemperature.value
    property alias dialTargetTemperatureValue: dialTargetTemperature.value

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
                id: label1
                x: 221
                y: 16
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label2
                x: 15
                y: 15
                text: qsTr("Target")
                font.pointSize: 18
            }

            Label {
                id: lblTarget
                x: 58
                y: 58
                width: 20
                height: 24
                text: Math.round(dialTargetTemperature.value) + "°"
                font.pointSize: 18
            }

            Label {
                id: lblActual
                x: 192
                y: 60
                width: 40
                height: 22
                text: "?°"
                horizontalAlignment: Text.AlignRight
                transformOrigin: Item.Right
                anchors.right: parent.right
                anchors.rightMargin: 62
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBarActualTemperature
                x: 147
                y: 131
                width: 200
                to: 40
                rotation: -90
                value: 0
            }

            ProgressBar {
                id: progressBarTargetTemperature
                x: -59
                y: 131
                value: dialTargetTemperature.value
                to: 40
                rotation: -90
            }

            Dial {
                id: dialTargetTemperature
                x: 107
                y: 114
                from: 10
                value: 22
                stepSize: 1
                to: 30
            }
        }
    }
}
