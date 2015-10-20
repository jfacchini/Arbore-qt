import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0

Rectangle {
    color: "#7b7c7e"

    ListView {
        id: menuList
        anchors.topMargin: 10
        interactive: false
        anchors.fill: parent

        highlight: Rectangle {
            color: "#7b7c7e"

            Rectangle {
                id: rectangle1
                color: "#4b4b4d"
                anchors.fill: parent
                anchors.leftMargin: 30

                Rectangle {
                    width: parent.height
                    height: parent.height
                    color: "#4b4b4d"
                    radius: 25
                    z: -1
                    anchors.horizontalCenter: parent.left
                }
            }
        }
        focus: true

        model: ListModel {
            ListElement {
                name: "Share list"
                image: "qrc:/images/dl"
                element: 3
                filter: "FilterType.ShareList"
            }
            ListElement {
                name: "Inbox"
                image: "qrc:/images/inbox"
                element: 8
                filter: "FilterType.Inbox"
            }
            ListElement {
                name: "My shares"
                image: "qrc:/images/ul"
                element: 3
                filter: "FilterType.MyShares"
            }
            ListElement {
                name: "Active shares"
                image: "qrc:/images/infos"
                filter: "FilterType.ActiveShares"
            }
            ListElement {
                name: "Starred"
                image: "qrc:/images/fav"
                filter: "FilterType.Starred"
            }
        }

        delegate: Text {
            id: menuLabel
            width: parent.width
            height: 40
            font.pointSize: 15
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    menuList.currentIndex = index;
                    shareModel.setFilterType(filter);
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10

                Image {
                    id: icon
                    width: 30
                    height: 30
                    source: image
                }

                Text {
                    text: name
                    font.weight: Font.Normal
                    font.family: ralewayblack.name
                    font.pointSize: 12
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    color: "#ffffff"
                    text: element
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true

                    font.family: ralewayblack.name
                    font.pointSize: 12
                    anchors.verticalCenter: parent.verticalCenter

                    visible: element > 0

                    Rectangle {
                        color: '#fa4f00'
                        radius: 20
                        height: 20
                        width: 20
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        z: -1
                    }
                }
            }
        }
    }
}

