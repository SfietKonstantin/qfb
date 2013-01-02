import QtQuick 1.1
import com.nokia.meego 1.0
import org.SfietKonstantin.qfb 4.0
import "UiConstants.js" as Ui

Page {
    id: container
    property string facebookId
    property string name

    function load() {
        typeLoader.request(facebookId)
    }

    Row {
        id: loadingIndicator
        anchors.centerIn: parent
        spacing: Ui.MARGIN_DEFAULT

        BusyIndicator {
            running: loadingIndicator.visible
        }

        Label {
            text: qsTr("Loading")
        }
    }

    QFBTypeLoader {
        id: typeLoader
        queryManager: QUERY_MANAGER
        onLoadingChanged: {
            if (!loading) {
                if (object.objectType != QFBObject.User) {
                    PAGE_MANAGEMENT_BRIDGE.pop()
                } else {
                    PAGE_MANAGEMENT_BRIDGE.addUserPage(container.facebookId, container.name)
                }
            }
        }
    }
}
