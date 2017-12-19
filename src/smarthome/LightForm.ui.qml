import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

PageBackground {
    id: pageBackgroundLight
    width: 824
    height: 552
    property alias switchSalonTous: switchSalonTous
    property alias switchSalonDevant: switchSalonDevant
    property alias switchSalonMilieu: switchSalonMilieu
    property alias switchSalonArriere: switchSalonArriere
    property alias switchHallTous: switchHallTous
    property alias switchHallBas: switchHallBas
    property alias switchHallEntree: switchHallEntree
    property alias switchHallVestiaire: switchHallVestiaire
    property alias switchCuisineTous: switchCuisineTous
    property alias switchCuisineCentral: switchCuisineCentral
    property alias switchCuisinePlanDeTravail: switchCuisinePlanDeTravail
    property alias switchCuisinePlaqueDeCuisson: switchCuisinePlaqueDeCuisson
    property alias switchBuanderie: switchBuanderie
    property alias switchToilette: switchToilette
    property alias switchExterieurTous: switchExterieurTous
    property alias switchExterieurArriere: switchExterieurArriere
    property alias switchExterieurCheminAvant: switchExterieurCheminAvant
    property alias switchExterieurCheminArriere: switchExterieurCheminArriere
    property alias switchExterieurGarageAvant: switchExterieurGarageAvant
    property alias switchExterieurGarageArriere: switchExterieurGarageArriere

    property alias switchChambre: switchChambre
    property alias switchSalleDeDoucheTous: switchSalleDeDoucheTous
    property alias switchSalleDeDoucheMirroir: switchSalleDeDoucheMirroir
    property alias switchSalleDeDoucheDouche: switchSalleDeDoucheDouche
    property alias switchSalleDeDoucheCentral: switchSalleDeDoucheCentral
    property alias switchSalleDeDoucheVentillation: switchSalleDeDoucheVentillation
    property alias switchChambreAmi: switchChambreAmi
    property alias switchBureau: switchBureau
    property alias switchDressing: switchDressing
    property alias switchGrenier: switchGrenier
    property alias switchCave: switchCave

    StackLayout {
        id: lightStackView
        x: 0
        y: 0
        width: 824
        height: 504
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        currentIndex: lightTabBar.currentIndex

        PageBackground {
            id: paneRez
            x: 0
            y: 0
            width: 824
            height: 504
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            GroupBox {
                id: groupBoxSalon
                x: 8
                y: 8
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Salon")

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchSalonTous
                        text: qsTr("Tous")
                    }

                    Slider {
                        id: slider1
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 180
                        value: 0.5
                    }

                    Switch {
                        id: switchSalonDevant
                        text: qsTr("Devant")
                    }

                    Slider {
                        id: slider2
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 180
                        value: 0.5
                    }

                    Switch {
                        id: switchSalonMilieu
                        text: qsTr("Milieu")
                    }

                    Slider {
                        id: slider3
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 180
                        value: 0.5
                    }

                    Switch {
                        id: switchSalonArriere
                        text: qsTr("Arrière")
                    }

                    Slider {
                        id: slider13
                        Layout.preferredWidth: 180
                        Layout.preferredHeight: 25
                        value: 0.5
                    }
                }
            }

            GroupBox {
                id: groupBoxExterieur
                x: 331
                y: 8
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                GridLayout {
                    Switch {
                        id: switchExterieurTous
                        text: qsTr("Tous")
                    }

                    Switch {
                        id: switchExterieurArriere
                        text: qsTr("Jardin")
                    }

                    Switch {
                        id: switchExterieurCheminAvant
                        text: qsTr("Chemin avant")
                    }

                    Switch {
                        id: switchExterieurGarageArriere
                        text: qsTr("Garage arrière")
                    }

                    Switch {
                        id: switchExterieurCheminArriere
                        text: qsTr("Chamine arrière")
                    }

                    Switch {
                        id: switchExterieurGarageAvant
                        text: qsTr("Garage avant")
                    }
                    columns: 2
                    rows: 3
                }
                title: qsTr("Exterieur")
            }

            GroupBox {
                id: groupBoxCuisine
                x: 331
                y: 215
                width: 349
                height: 148
                padding: 12

                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                GridLayout {
                    Switch {
                        id: switchCuisineTous
                        text: qsTr("Tous")
                    }

                    Switch {
                        id: switchCuisinePlanDeTravail
                        text: qsTr("Plan de travail")
                    }

                    Switch {
                        id: switchCuisineCentral
                        text: qsTr("Central")
                    }

                    Switch {
                        id: switchCuisinePlaqueDeCuisson
                        text: qsTr("Plaque de cuisson")
                    }
                    columns: 2
                    rows: 2
                }
                title: qsTr("Cuisine")
            }

            GroupBox {
                id: groupBoxHall
                x: 8
                y: 268
                width: 317
                height: 148
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                GridLayout {
                    Switch {
                        id: switchHallTous
                        text: qsTr("Tous")
                    }

                    Switch {
                        id: switchHallBas
                        text: qsTr("Bas")
                    }

                    Switch {
                        id: switchHallEntree
                        text: qsTr("Entree")
                    }

                    Switch {
                        id: switchHallVestiaire
                        text: qsTr("Entree")
                    }
                    columns: 2
                    rows: 3
                }
                title: qsTr("Hall")
            }

            GroupBox {
                id: groupBoxBuanderie
                x: 331
                y: 369
                width: 182
                height: 95
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchBuanderie
                        text: qsTr("Buanderie")
                    }
                }

                title: qsTr("Buanderie")
            }

            GroupBox {
                id: groupBoxToilette
                x: 519
                y: 369
                width: 161
                height: 95
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                GridLayout {
                    rows: 3
                    columns: 2
                    Switch {
                        id: switchToilette
                        text: qsTr("Toilette")
                    }
                }
                title: qsTr("Toilette")
            }
        }

        PageBackground {
            id: paneReste
            x: 0
            y: 0
            width: 824
            height: 504
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            GroupBox {
                id: groupBoxChambre
                x: 8
                y: 8
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Chambre")

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchChambre
                        text: qsTr("Chambre")
                    }

                    Slider {
                        id: sliderChambre
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 180
                        value: 0.5
                    }
                }
            }

            GroupBox {
                id: groupBoxSalleDeDouche
                x: 353
                y: 8
                width: 303
                height: 198
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Salle de douche")
                GridLayout {
                    Switch {
                        id: switchSalleDeDoucheTous
                        text: qsTr("Tous")
                    }

                    Switch {
                        id: switchSalleDeDoucheMirroir
                        text: qsTr("Mirroir")
                    }

                    Switch {
                        id: switchSalleDeDoucheDouche
                        text: qsTr("Douche")
                    }

                    Switch {
                        id: switchSalleDeDoucheCentral
                        text: qsTr("Central")
                    }

                    Switch {
                        id: switchSalleDeDoucheVentillation
                        text: qsTr("Ventillation")
                    }

                    columns: 2
                    rows: 2
                }
            }

            GroupBox {
                id: groupBoxChambreAmi
                x: 8
                y: 236
                width: 339
                height: 91
                padding: 12
                title: qsTr("Chambre d'amis")

                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                GridLayout {
                    Switch {
                        id: switchChambreAmi
                        text: qsTr("Chambre d'amis")
                    }

                    columns: 1
                    rows: 1
                }
            }

            GroupBox {
                id: groupBureau
                x: 353
                y: 237
                width: 145
                height: 90
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Bureau")
                GridLayout {
                    Switch {
                        id: switchBureau
                        text: qsTr("Bureau")
                    }

                    columns: 1
                    rows: 1
                }
            }

            GroupBox {
                id: groupBoxDressing
                x: 504
                y: 237
                width: 152
                height: 90
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Dressing")

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchDressing
                        text: qsTr("Dressing")
                    }
                }
            }

            GroupBox {
                id: groupBoxGrenier
                x: 8
                y: 360
                width: 339
                height: 90
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Grenier")

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchGrenier
                        text: qsTr("Grenier")
                    }
                }
            }

            GroupBox {
                id: groupBoxCave
                x: 353
                y: 360
                width: 303
                height: 90
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                title: qsTr("Cave")

                GridLayout {
                    rows: 3
                    columns: 2

                    Switch {
                        id: switchCave
                        text: qsTr("Cave")
                    }
                }
            }

        }

    }

    TabBar {
        id: lightTabBar
        height: 48
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 48
        currentIndex: lightStackView.currentIndex

        TabButton {
            text: qsTr("Rez")
        }

        TabButton {
            text: qsTr("Reste")
        }

//        TabButton {
//            text: qsTr("Grenier")
//        }

//        TabButton {
//            text: qsTr("Cave")
//        }
    }
}
