/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#ifndef QFB_LOGINMANAGER_H
#define QFB_LOGINMANAGER_H

/**
 * @file loginmanager.h
 * @short Definition of QFB::LoginManager
 */


#include "login_global.h"
#include <QtCore/QObject>

class QUrl;
namespace QFB
{

class LoginManagerPrivate;
/**
 * @brief Manages OAuth login to Facebook
 *
 * This class is a helper class that is used to
 * perform a login operation using OAuth 2. Since
 * Facebook requires a WebView to display their
 * dialogs, this class only provides helpful
 * methods to perform the login with the help
 * of a WebView.
 *
 * In order to use that class you will need to
 * - Connect urlChanged() from the WebView to checkUrl().
 * - Connect urlRequested() from this class to set the URL of the WebView.
 * - Connect loginSucceeded() and loginFailed().
 * - Perform the login with login().
 *
 * This class will then manage the WebView, redirect
 * the user if he/she is clicking on links that are
 * not related to login, and extract the token if the
 * login is successful.
 */
class QFBLOGIN_EXPORT LoginManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(UiType)
    Q_ENUMS(Permission)
    /**
     * @short Client ID
     */
    Q_PROPERTY(QString clientId READ clientId WRITE setClientId NOTIFY clientIdChanged)
    /**
     * @short Permissions
     */
    Q_PROPERTY(Permissions permissions READ permissions WRITE setPermissions
               NOTIFY permissionsChanged)
    /**
     * @short UI type
     */
    Q_PROPERTY(UiType uiType READ uiType WRITE setUiType NOTIFY uiTypeChanged)
public:
    /**
     * @brief Type of UI to be used for login
     */
    enum UiType {
        /**
         * @short Desktop UI
         */
        Desktop,
        /**
         * @short Mobile UI
         */
        Mobile
    };
    /**
     * @brief Permissions
     *
     * This enumeration provides a list of permissions
     * that can be combined as flags.
     */
    enum Permission {
        /**
         * @short Provides \e read_friendlists
         *
         * Provides access to any friend lists the user created. All user's friends are
         * provided as part of basic data, this extended permission grants access to the
         * lists of friends a user has created, and should only be requested if your
         * application utilizes lists of friends.
         */
        ReadFriendList = 0x00000001,
        /**
         * @short Provides \e read_insights
         *
         * Provides read access to the Insights data for pages, applications, and domains
         * the user owns.
         */
        ReadInsights = 0x00000002,
        /**
         * @short Provides \e read_mailbox
         *
         * Provides the ability to read from a user's Facebook Inbox.
         */
        ReadMailbox = 0x00000004,
        /**
         * @short Provides \e read_requests
         *
         * Provides read access to the user's friend requests.
         */
        ReadRequests = 0x00000008,
        /**
         * @short Provides \e read_stream
         *
         * Provides access to all the posts in the user's News Feed and enables your
         * application to perform searches against the user's News Feed.
         */
        ReadStream = 0x00000010,
        /**
         * @short Provides \e xmpp_login
         *
         * Provides applications that integrate with Facebook Chat the ability to log
         * in users.
         */
        XmppLogin = 0x00000020,
        /**
         * @short Provides \e ads_management
         *
         * Provides the ability to manage ads and call the Facebook Ads API on behalf
         * of a user.
         */
        AdsManagement = 0x00000040,
        /**
         * @short Provides \e create_event
         *
         * Enables your application to create and modify events on the user's behalf.
         */
        CreateEvent = 0x00000080,
        /**
         * @short Provides \e manage_friendlists
         *
         * Enables your app to create and edit the user's friend lists.
         */
        ManageFriendList = 0x00000100,
        /**
         * @short Provides \e manage_notifications
         *
         * Enables your app to read notifications and mark them as read.
         * <b>Intended usage</b>: This permission should be used to let users read and act on
         * their notifications; it should not be used to for the purposes of modeling
         * user behavior or data mining. Apps that misuse this permission may be banned
         * from requesting it.
         */
        ManageNotifications = 0x00000200,
        /**
         * @short Provides \e user_online_presence
         *
         * Provides access to the user's online/offline presence.
         */
        UserOnlinePresence = 0x00000400,
        /**
         * @short Provides \e friends_online_presence
         *
         * Provides access to the user's friend's online/offline presence.
         */
        FriendsOnlinePresence = 0x00000800,
        /**
         * @short Provides \e publish_checkins
         *
         * Enables your app to perform checkins on behalf of the user.
         */
        PublishCheckins = 0x00001000,
        /**
         * @short Provides \e publish_stream
         *
         * Enables your app to post content, comments, and likes to a user's stream and to
         * the streams of the user's friends. This is a superset publishing permission which
         * also includes \e publish_actions. However, please note that Facebook recommends a
         * user-initiated sharing model. Please read the Platform Policies to ensure you
         * understand how to properly use this permission. Note, you do not need to request
         * the \e publish_stream permission in order to use the Feed Dialog, the Requests Dialog
         * or the Send Dialog.
         */
        PublishStream = 0x00002000,
        /**
         * @short Provides \e rsvp_event
         *
         * Enables your application to RSVP to events on the user's behalf.
         */
        RsvpEvent = 0x00004000
    };
    Q_DECLARE_FLAGS(Permissions, Permission)
    Q_FLAGS(Permissions)

    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit LoginManager(QObject *parent = 0);
    /**
     * @brief Overloaded constructor
     * @param clientId client ID.
     * @param parent parent object.
     */
    explicit LoginManager(const QString &clientId, QObject *parent = 0);
    /**
     * @brief Overloaded constructor
     * @param clientId client ID.
     * @param permissions permissions.
     * @param parent parent object.
     */
    explicit LoginManager(const QString &clientId, Permissions permissions, QObject *parent = 0);
    /**
     * @brief Overloaded constructor
     * @param clientId client ID.
     * @param uiType UI type.
     * @param parent parent object.
     */
    explicit LoginManager(const QString &clientId, UiType uiType, QObject *parent = 0);
    /**
     * @brief Overloaded constructor
     * @param clientId client ID.
     * @param permissions permissions.
     * @param uiType UI type.
     * @param parent parent object.
     */
    explicit LoginManager(const QString &clientId, Permissions permissions, UiType uiType,
                          QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~LoginManager();
    /**
     * @brief Client ID
     * @return client ID.
     */
    QString clientId() const;
    /**
     * @brief Permissions
     * @return permissions.
     */
    Permissions permissions() const;
    /**
     * @brief Get the UI type
     * @return UI type.
     */
    UiType uiType() const;
public Q_SLOTS:
    /**
     * @brief Set the client ID
     * @param clientId client ID to set.
     */
    void setClientId(const QString &clientId);
    /**
     * @brief Set permissions
     * @param permissions permissions to set.
     */
    void setPermissions(Permissions permissions);
    /**
     * @brief Set the UI type
     * @param uiType UI type to set.
     */
    void setUiType(UiType uiType);
    /**
     * @brief Start the login operation
     */
    void login();
    /**
     * @brief Check URL
     *
     * This method is used to check the URL of the WebView
     * that is performing the login operation. If the URL
     * is wrong, meaning that the user is clicking on links
     * unrelated to login, this class will then automatically
     * emit corrected URL.
     *
     * This method also handle the token extraction if the
     * login is successful.
     *
     * @param url URL to check.
     */
    void checkUrl(const QUrl &url);
Q_SIGNALS:
    /**
     * @brief Client ID changed
     */
    void clientIdChanged();
    /**
     * @brief Permissions changed
     */
    void permissionsChanged();
    /**
     * @brief UI type changed
     */
    void uiTypeChanged();
    /**
     * @brief URL request
     *
     * This signal is emitted when the URL of the WebView
     * perfomring the login operation should be set to a given
     * URL.
     *
     * @param url URL to be set.
     */
    void urlRequested(const QUrl &url);
    /**
     * @brief The login is successful
     * @param token access token.
     */
    void loginSucceeded(const QString &token);
    /**
     * @brief The login failed
     */
    void loginFailed();
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<LoginManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(LoginManager)
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(QFB::LoginManager::Permissions)

#endif // QFB_LOGINMANAGER_H
