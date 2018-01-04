import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 1024
    height: 600
    title: qsTr("Smart Home")
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange

    StackLayout {
        id: swipeView
        anchors.left: sideBar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        currentIndex: tabBar.currentIndex

        Light {

        }

        Heating {
            id: heating

        }

        Security {

        }
    }

    TabBar {
        id: tabBar
        height: 48
        anchors.bottom: parent.bottom
        anchors.left: sideBar.right
        anchors.right: parent.right
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Lumières")
        }
        TabButton {
            text: qsTr("Chauffage")
        }
        TabButton {
            text: qsTr("Alarme")
        }
    }

    SideBar {
        id: sideBar
    }

}
