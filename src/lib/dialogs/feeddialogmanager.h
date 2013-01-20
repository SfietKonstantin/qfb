/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef FEEDDIALOGMANAGER_H
#define FEEDDIALOGMANAGER_H

#include "dialogs_global.h"
#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace QFB
{

class FeedDialogManagerPrivate;
class QFBDIALOGS_EXPORT FeedDialogManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString clientId READ clientId WRITE setClientId NOTIFY clientIdChanged)
    Q_PROPERTY(QString from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QString to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(QUrl link READ link WRITE setLink NOTIFY linkChanged)
    Q_PROPERTY(QUrl picture READ picture WRITE setPicture NOTIFY pictureChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    /// @todo properties
    /// @todo actions
    /// @todo ref
    Q_PROPERTY(UiType uiType READ uiType WRITE setUiType NOTIFY uiTypeChanged)
public:
    /**
     * @brief Type of UI to be used for login
     */
    enum UiType {
        /**
         * @short Desktop UI
         */
        Page,
        Popup,
        Touch
    };

    explicit FeedDialogManager(QObject *parent = 0);
    virtual ~FeedDialogManager();
    /**
     * @brief Client ID
     * @return client ID.
     */
    QString clientId() const;
    QString from() const;
    QString to() const;
    QUrl link() const;
    QUrl picture() const;
    QUrl source() const;
    QString name() const;
    QString caption() const;
    QString description() const;
    UiType uiType() const;
public Q_SLOTS:
    /**
     * @brief Set the client ID
     * @param clientId client ID to set.
     */
    void setClientId(const QString &clientId);
    void setFrom(const QString &from);
    void setTo(const QString &to);
    void setLink(const QUrl &link);
    void setPicture(const QUrl &picture);
    void setSource(const QUrl &source);
    void setName(const QString &name);
    void setCaption(const QString &caption);
    void setDescription(const QString &description);
    /**
     * @brief Set the UI type
     * @param uiType UI type to set.
     */
    void setUiType(UiType uiType);
    void displayDialog();
    void checkUrl(const QUrl &url);
Q_SIGNALS:
    /**
     * @brief Client ID changed
     */
    void clientIdChanged();
    void fromChanged();
    void toChanged();
    void linkChanged();
    void pictureChanged();
    void sourceChanged();
    void nameChanged();
    void captionChanged();
    void descriptionChanged();
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
    void postSucceeded(const QString id);
    void postFailed();
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<FeedDialogManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FeedDialogManager)
};

}

#endif // FEEDDIALOGMANAGER_H
