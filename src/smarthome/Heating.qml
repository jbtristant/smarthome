import QtQuick 2.4
import RoomsEnums 1.0

HeatingForm {
    id: heating

    Connections {
        target: homeController
        onTemperatureChanged: {
            switch (room) {
            case Rooms.Salon:
                progressBarActualLRTemperatureValue = value
                lblLRActualText = value + "°"
                break;
            case Rooms.SalleDeBain:
                progressBarActualBRTemperatureValue = value
                lblBRActualTemperatureText = value + "°"
                break;
            case Rooms.Hall:
                lblHallActualTemperatureText = value + "°"
            break;
            case Rooms.Chambre:
                lblChambreActualTemperatureText = value + "°"
                break;
            default:
            }
        }
        onHumidityChanged: {
            switch (room) {
            case Rooms.SalleDeBain:
                lblBRActualHumidityText = value + " %"
                break;
            case Rooms.Hall:
                lblHAallActualHumidityText= value + " %"
                break;
            case Rooms.Chambre:
                lblChambreActualHumidityText = value + " %"
                break;
            default:
            }
        }
    }
}
