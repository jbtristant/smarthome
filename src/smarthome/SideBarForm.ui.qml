import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

PageBackground {
    width: 200
    height: 600
    property alias lblHeatText: lblHeat.text
    property alias lblHumidityText: lblHumidity.text
    property alias lblTemperatureText: lblTemperature.text
    property alias lblDateText: lblDate.text
    property alias lblDayText: lblDay.text
    property alias lblTimeText: lblTime.text
    property alias btnConfigure: btnConfigure
    property alias comboBox: comboBox
    property alias switchLumieres: switchLumieres

    CustomLabel {
        id: lblTime
        x: 137
        y: 8
        text: "12:23"
        font.pixelSize: 22
    }

    Label {
        id: lblDay
        x: 8
        y: 8
        width: 74
        height: 26
        text: qsTr("Sunday")
        font.capitalization: Font.Capitalize
        font.pixelSize: 22
    }

    CustomLabel {
        id: lblDate
        x: 9
        y: 40
        width: 173
        height: 26
        text: "12 April 2016"
        font.pixelSize: 22
    }

    CustomLabel {
        id: lblTemperature
        x: 70
        y: 92
        text: "18°"
        font.pixelSize: 36
    }

    Label {
        id: label3
        x: 9
        y: 276
        text: qsTr("Power Consumption")
        font.pixelSize: 12
    }

    ProgressBar {
        id: progressBar1
        x: 8
        y: 297
        width: 175
        height: 7
        value: 0.5
    }

    Switch {
        id: switch1
        x: 8
        y: 320
        text: qsTr("Ventilation")
    }

    Switch {
        id: switch2
        x: 8
        y: 401
        text: qsTr("Alarm Active")
    }

    Label {
        id: label4
        x: 9
        y: 474
        text: qsTr("Mode")
        font.pixelSize: 12
    }

    ComboBox {
        id: comboBox
        x: 9
        y: 490
        width: 183
        height: 48
        model: homeController.heatingStateList
        textRole: "name"
    }

    Button {
        id: btnConfigure
        x: 8
        y: 544
        width: 184
        height: 48
        text: qsTr("Configure")
    }

    Label {
        id: label
        x: 9
        y: 154
        text: qsTr("Humidité :")
    }

    CustomLabel {
        id: lblHumidity
        x: 99
        y: 154
        text: "0 %"
    }

    Label {
        id: label1
        x: 9
        y: 177
        text: qsTr("Chaleur :")
    }

    CustomLabel {
        id: lblHeat
        x: 99
        y: 177
        text: "0 %"
    }

    Switch {
        id: switchLumieres
        x: 9
        y: 361
        text: qsTr("Lumières")
    }
}
