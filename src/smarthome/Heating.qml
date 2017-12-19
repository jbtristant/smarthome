import QtQuick 2.4

HeatingForm {
    id: heating

    Connections {
        target: homeController
        onTemperatureChanged: {
            progressBarActualTemperatureValue = value
            lblActualText = value + "°"
        }
    }
}
