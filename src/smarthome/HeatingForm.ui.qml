import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground {
    width: 824
    height: 552
    property alias lblLRTargetText: lblLRTarget.text
    property alias lblLRActualText: lblLRActual.text
    property alias progressBarActualLRTemperatureValue: progressBarActualLRTemperature.value
    property alias dialTargetTemperatureLRValue: dialTargetLRTemperature.value

    property alias lblBRActualTemperatureText: lblBRActualTemperature.text
    property alias lblBRActualHumidityText: lblBRActualHumidity.text
    property alias progressBarActualBRTemperatureValue: progressBarActualBRTemperature.value
    property alias dialTargetBRTemperatureValue: dialTargetBRTemperature.value

    property alias lblHallActualTemperatureText: lblHallActualTemperature.text
    property alias lblHAallActualHumidityText: lblHallActualHumidity.text

    property alias lblChambreActualTemperatureText: lblChambreActualTemperature.text
    property alias lblChambreActualHumidityText: lblChambreActualHumidity.text

    GridLayout {
        id: gridLayoutLivingRoom
        x: 53
        y: 56
        anchors.horizontalCenterOffset: -185
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 2

        GroupBox {
            id: groupBoxLivingRoom
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.preferredHeight: 280
            Layout.preferredWidth: 318
            title: qsTr("Salon")

            Label {
                id: label1
                x: 221
                y: 5
                text: qsTr("Actuel")
                font.pointSize: 18
            }

            Label {
                id: label2
                x: 3
                y: 5
                text: qsTr("Demandé")
                font.pointSize: 18
            }

            Label {
                id: lblLRTarget
                x: 49
                y: 37
                width: 30
                height: 24
                color: "#ff5722"
                text: Math.round(dialTargetLRTemperature.value) + "°"
                font.pointSize: 18
            }

            Label {
                id: lblLRActual
                x: 199
                y: 37
                width: 40
                height: 22
                color: "#ff5722"
                text: "?°"
                horizontalAlignment: Text.AlignRight
                transformOrigin: Item.Right
                anchors.right: parent.right
                anchors.rightMargin: 55
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBarActualLRTemperature
                x: 147
                y: 131
                width: 200
                to: 40
                rotation: -90
                value: 0
            }

            ProgressBar {
                id: progressBarTargetLRTemperature
                x: -59
                y: 131
                value: dialTargetLRTemperature.value
                to: 40
                rotation: -90
            }

            Dial {
                id: dialTargetLRTemperature
                x: 107
                y: 114
                from: 10
                value: 22
                stepSize: 1
                to: 30
            }
        }
    }

    GridLayout {
        id: gridLayoutBathroom
        x: 48
        y: 56
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        anchors.horizontalCenterOffset: 188
        rows: 2
        GroupBox {
            id: groupBoxBathroom
            Label {
                id: label3
                x: 221
                y: 5
                text: qsTr("Actuel")
                font.pointSize: 18
            }

            Label {
                id: label4
                x: 3
                y: 5
                text: qsTr("Demandé")
                font.pointSize: 18
            }

            Label {
                id: lblBRTarget
                x: 49
                y: 34
                width: 20
                height: 24
                color: "#ff5722"
                text: Math.round(dialTargetBRTemperature.value) + "°"
                font.pointSize: 18
            }

            Label {
                id: lblBRActualTemperature
                x: 199
                y: 35
                width: 40
                height: 22
                color: "#ff5722"
                text: "?°"
                anchors.right: parent.right
                transformOrigin: Item.Right
                font.pointSize: 18
                horizontalAlignment: Text.AlignRight
                anchors.rightMargin: 55
            }

            ProgressBar {
                id: progressBarActualBRTemperature
                x: 147
                y: 131
                width: 200
                rotation: -90
                to: 40
                value: 0
            }

            ProgressBar {
                id: progressBarTargetBRTemperature
                x: -59
                y: 131
                rotation: -90
                to: 40
                value: dialTargetBRTemperature.value
            }

            Dial {
                id: dialTargetBRTemperature
                x: 107
                y: 114
                stepSize: 1
                to: 30
                value: 22
                from: 10
            }

            Label {
                id: lblBRActualHumidity
                x: 199
                y: 63
                width: 40
                height: 22
                color: "#ff5722"
                text: "?%"
                anchors.right: parent.right
                transformOrigin: Item.Right
                font.pointSize: 14
                horizontalAlignment: Text.AlignRight
                anchors.rightMargin: 55
            }
            Layout.fillHeight: false
            Layout.preferredHeight: 280
            title: qsTr("Salle de bain")
            Layout.fillWidth: false
            Layout.preferredWidth: 318
        }
    }

    Label {
        id: label5
        x: 68
        y: 397
        text: qsTr("Hall :")
        font.pointSize: 18
    }

    Label {
        id: label6
        x: 68
        y: 425
        text: qsTr("Chambre :")
        font.pointSize: 18
    }

    Label {
        id: lblHallActualTemperature
        x: 158
        y: 397
        width: 48
        height: 22
        color: "#ff5722"
        text: "?°"
        anchors.right: parent.right
        transformOrigin: Item.Right
        font.pointSize: 18
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 618
    }

    Label {
        id: lblChambreActualTemperature
        x: 158
        y: 425
        width: 48
        height: 22
        color: "#ff5722"
        text: "?°"
        anchors.right: parent.right
        font.pointSize: 18
        transformOrigin: Item.Right
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 618
    }

    Label {
        id: lblHallActualHumidity
        x: 212
        y: 397
        width: 48
        height: 22
        color: "#ff5722"
        text: "?%"
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        transformOrigin: Item.Right
        font.pointSize: 14
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 564
    }

    Label {
        id: lblChambreActualHumidity
        x: 212
        y: 425
        width: 48
        height: 22
        color: "#ff5722"
        text: "?%"
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        font.pointSize: 14
        transformOrigin: Item.Right
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 564
    }
}
