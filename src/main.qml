import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Grpc Test")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 8
        GroupBox {
            title: "Messages Test"
            GridLayout {
                anchors.fill: parent

                TextField {
                    id: nameTextField
                    text: "Testinator 3000"
                }
                Button {
                    text: "Send Hello"
                    onClicked: {
                        testClient.sendHello(nameTextField.text)
                    }
                }
                Button {
                    text: "Send Goodbye"
                    onClicked: {
                        testClient.sendGoodbye(nameTextField.text)
                    }
                }
            }
        }
        GroupBox {
            title: "Math Test"
            GridLayout {
                anchors.fill: parent
                SpinBox {
                    id: factorA
                    value: 3
                }
                SpinBox {
                    id: factorB
                    value: 5
                }
                Button {
                    text: "Multiply"
                    onClicked: {
                        testClient.sendMultiply(factorA.value, factorB.value)
                    }
                }
            }
        }
        GroupBox {
            title: "Last Server Reply"
            Label {
                text: testClient.lastReply
            }
        }
    }
}
