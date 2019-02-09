import QtQuick 2.4
import QtQuick.Dialogs 1.2
import RoomsEnums 1.0
import HeatingRolesEnums 1.0

SideBarForm {
    id: sideBar
        //["Normal", "Vacances", "Fête", "Absent"]

    comboBoxHeating.onCurrentIndexChanged: {
        homeController.setHeatingState(heatingListModel.get(comboBoxHeating.currentIndex).id)
    }

    btnConfigure.onClicked: {
        dialog.open()
    }

    MessageDialog {
        id: dialog
        title: qsTr("May I have your attention, please?")
        text: qsTr("May I have your attention, please?")

        function show(caption) {
            dialog.text = caption;
            dialog.open();
        }
    }

    function timeChanged() {
        var date = new Date;
        lblTimeText = Qt.formatDateTime(date, "HH:mm");
        lblDateText = Qt.formatDateTime(date, "dd MMMM yyyy")
        lblDayText = Qt.formatDateTime(date, "dddd")
    }

    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered: timeChanged()
    }

    Connections {
        target: homeController
        onTemperatureChanged: {
            if (room === Rooms.Salon) lblTemperatureText = value + "°"
        }
        onHumidityChanged: {
            if (room === Rooms.Salon) lblHumidityText = value + " %"
        }
        onHeatChanged: {
            if (room === Rooms.Salon) lblHeatText = value + "°"
        }
        onHeatingStateChanged: {
            comboBoxHeating.currentIndex = heatingListModel.indexFromId(id)
        }
    }

    switchLumieres.onClicked: {
        homeController.setRelay(1, 0, switchLumieres.checked)
        homeController.setRelay(1, 1, switchLumieres.checked)
        homeController.setRelay(1, 2, switchLumieres.checked)
        homeController.setRelay(1, 3, switchLumieres.checked)
        homeController.setRelay(1, 4, switchLumieres.checked)
        homeController.setRelay(1, 5, switchLumieres.checked)
        homeController.setRelay(1, 6, switchLumieres.checked)
        homeController.setRelay(1, 7, switchLumieres.checked)
        homeController.setRelay(1, 8, switchLumieres.checked)
        homeController.setRelay(1, 9, switchLumieres.checked)
        homeController.setRelay(1, 10, switchLumieres.checked)
        homeController.setRelay(1, 11, switchLumieres.checked)
        homeController.setRelay(1, 12, switchLumieres.checked)
        homeController.setRelay(1, 13, switchLumieres.checked)
        homeController.setRelay(1, 14, switchLumieres.checked)
        homeController.setRelay(1, 15, switchLumieres.checked)
        homeController.setRelay(1, 16, switchLumieres.checked)
        homeController.setRelay(1, 17, switchLumieres.checked)
        homeController.setRelay(1, 18, switchLumieres.checked)
        homeController.setRelay(1, 19 , switchLumieres.checked)
        homeController.setRelay(1, 20, switchLumieres.checked)
        homeController.setRelay(1, 21, switchLumieres.checked)
        homeController.setRelay(1, 22, switchLumieres.checked)
        homeController.setRelay(1, 23, switchLumieres.checked)
        homeController.setRelay(1, 24, switchLumieres.checked)
        homeController.setRelay(1, 25, switchLumieres.checked)
    }


}
