import QtQuick 2.4

LightForm {

    switchSalonTous.onClicked: {
        homeController.setRelay(1, 0, switchSalonTous.checked)
        homeController.setRelay(1, 1, switchSalonTous.checked)
        homeController.setRelay(1, 2, switchSalonTous.checked)
    }
    switchSalonDevant.onClicked: {
        homeController.setRelay(1, 0, switchSalonDevant.checked)
    }
    switchSalonMilieu.onClicked: {
        homeController.setRelay(1, 1, switchSalonMilieu.checked)
    }
    switchSalonArriere.onClicked: {
        homeController.setRelay(1, 2, switchSalonArriere.checked)
    }

    switchHallTous.onClicked: {
        homeController.setRelay(1, 3, switchHallTous.checked)
        homeController.setRelay(1, 4, switchHallTous.checked)
        homeController.setRelay(1, 5, switchHallTous.checked)
    }
    switchHallBas.onClicked: {
        homeController.setRelay(1, 3, switchHallBas.checked)
    }
    switchHallEntree.onClicked: {
        homeController.setRelay(1, 4, switchHallEntree.checked)
    }
    switchHallVestiaire.onClicked: {
        homeController.setRelay(1, 5, switchHallVestiaire.checked)
    }

    switchCuisineTous.onClicked: {
        homeController.setRelay(1, 6, switchCuisineTous.checked)
        homeController.setRelay(1, 7, switchCuisineTous.checked)
        homeController.setRelay(1, 8, switchCuisineTous.checked)
    }
    switchCuisineCentral.onClicked: {
        homeController.setRelay(1, 6, switchCuisineCentral.checked)
    }
    switchCuisinePlanDeTravail.onClicked: {
        homeController.setRelay(1, 7, switchCuisinePlanDeTravail.checked)
    }
    switchCuisinePlaqueDeCuisson.onClicked: {
        homeController.setRelay(1, 8, switchCuisinePlaqueDeCuisson.checked)
    }
    switchBuanderie.onClicked: {
        homeController.setRelay(1, 9, switchBuanderie.checked)
    }
    switchToilette.onClicked: {
        homeController.setRelay(1, 10, switchToilette.checked)
    }

    switchExterieurTous.onClicked: {
        homeController.setRelay(1, 11, switchExterieurTous.checked)
        homeController.setRelay(1, 12, switchExterieurTous.checked)
        homeController.setRelay(1, 13, switchExterieurTous.checked)
        homeController.setRelay(1, 14, switchExterieurTous.checked)
        homeController.setRelay(1, 15, switchExterieurTous.checked)
    }
    switchExterieurCheminAvant.onClicked: {
        homeController.setRelay(1, 11, switchExterieurCheminAvant.checked)
    }
    switchExterieurCheminArriere.onClicked: {
        homeController.setRelay(1, 12, switchExterieurCheminArriere.checked)
    }
    switchExterieurArriere.onClicked: {
        homeController.setRelay(1, 13, switchExterieurArriere.checked)
    }
    switchExterieurGarageArriere.onClicked: {
        homeController.setRelay(1, 14, switchExterieurGarageArriere.checked)
    }
    switchExterieurGarageAvant.onClicked: {
        homeController.setRelay(1, 15, switchExterieurGarageAvant.checked)
    }

    switchChambre.onClicked: {
        homeController.setRelay(1, 16, switchChambre.checked)
    }
    switchSalleDeDoucheTous.onClicked: {
        homeController.setRelay(1, 17, switchSalleDeDoucheTous.checked)
        homeController.setRelay(1, 18, switchSalleDeDoucheTous.checked)
        homeController.setRelay(1, 19, switchSalleDeDoucheTous.checked)
    }
    switchSalleDeDoucheMirroir.onClicked: {
        homeController.setRelay(1, 17, switchSalleDeDoucheMirroir.checked)
    }
    switchSalleDeDoucheDouche.onClicked: {
        homeController.setRelay(1, 18, switchSalleDeDoucheDouche.checked)
    }
    switchSalleDeDoucheCentral.onClicked: {
        homeController.setRelay(1, 19, switchSalleDeDoucheCentral.checked)
    }
    switchSalleDeDoucheVentillation.onClicked: {
        homeController.setRelay(1, 20, switchSalleDeDoucheVentillation.checked)
    }
    switchChambreAmi.onClicked: {
        homeController.setRelay(1, 21, switchChambreAmi.checked)
    }
    switchBureau.onClicked: {
        homeController.setRelay(1, 22, switchBureau.checked)
    }
    switchDressing.onClicked: {
        homeController.setRelay(1, 23, switchDressing.checked)
    }
    switchGrenier.onClicked: {
        homeController.setRelay(1, 24, switchGrenier.checked)
    }
    switchCave.onClicked: {
        homeController.setRelay(1, 25, switchCave.checked)
    }


    Connections {
        target: homeController
        onRelayChanged: {
            if (relay == 0) switchSalonDevant.checked = relayState
            if (relay == 1) switchSalonMilieu.checked = relayState
            if (relay == 2) switchSalonArriere.checked = relayState
            switchSalonTous.checked = switchSalonDevant.checked && switchSalonMilieu.checked && switchSalonArriere.checked
            if (relay == 3) switchHallBas.checked = relayState
            if (relay == 4) switchHallEntree.checked = relayState
            if (relay == 5) switchHallVestiaire.checked = relayState
            switchHallTous.checked = switchHallBas.checked && switchHallEntree.checked && switchHallVestiaire.checked
            if (relay == 6) switchCuisineCentral.checked = relayState
            if (relay == 7) switchCuisinePlanDeTravail.checked = relayState
            if (relay == 8) switchCuisinePlaqueDeCuisson.checked = relayState
            switchCuisineTous.checked = switchCuisineCentral.checked && switchCuisinePlanDeTravail.checked && switchCuisinePlaqueDeCuisson.checked
            if (relay == 9) switchBuanderie.checked = relayState
            if (relay == 10) switchToilette.checked = relayState
            if (relay == 11) switchExterieurCheminAvant.checked = relayState
            if (relay == 12) switchExterieurCheminArriere.checked = relayState
            if (relay == 13) switchExterieurArriere.checked = relayState
            if (relay == 14) switchExterieurGarageArriere.checked = relayState
            if (relay == 15) switchExterieurGarageAvant.checked = relayState
            switchExterieurTous.checked = switchExterieurCheminAvant.checked && switchExterieurCheminArriere.checked
                    && switchExterieurArriere.checked && switchExterieurGarageArriere.checked && switchExterieurGarageAvant.checked
            if (relay == 16) switchChambre.checked = relayState
            if (relay == 17) switchSalleDeDoucheMirroir.checked = relayState
            if (relay == 18) switchSalleDeDoucheDouche.checked = relayState
            if (relay == 19) switchSalleDeDoucheCentral.checked = relayState
            switchSalleDeDoucheTous.checked = switchSalleDeDoucheMirroir.checked && switchSalleDeDoucheDouche.checked && switchSalleDeDoucheCentral.checked
            if (relay == 20) switchSalleDeDoucheVentillation.checked = relayState
            if (relay == 21) switchChambreAmi.checked = relayState
            if (relay == 22) switchBureau.checked = relayState
            if (relay == 23) switchDressing.checked = relayState
            if (relay == 24) switchGrenier.checked = relayState
            if (relay == 25) switchCave.checked = relayState


            sideBar.switchLumieres.checked = switchSalonDevant.checked || switchSalonMilieu.checked || switchSalonArriere.checked
                    || switchHallBas.checked || switchHallEntree.checked || switchHallVestiaire.checked
                    || switchCuisineCentral.checked || switchCuisinePlanDeTravail.checked || switchCuisinePlaqueDeCuisson.checked
                    || switchBuanderie.checked || switchToilette.checked
                    || switchExterieurCheminAvant.checked || switchExterieurCheminArriere.checked || switchExterieurArriere.checked
                    || switchExterieurGarageArriere.checked || switchExterieurGarageAvant.checked
                    || switchChambre.checked || switchSalleDeDoucheMirroir.checked
                    || switchSalleDeDoucheDouche.checked || switchSalleDeDoucheCentral.checked || switchSalleDeDoucheVentillation.checked
                    || switchChambreAmi.checked || switchBureau.checked
                    || switchDressing.checked || switchGrenier.checked || switchCave.checked
        }
    }
}
