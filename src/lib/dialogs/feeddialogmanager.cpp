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

#include "feeddialogmanager.h"
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtCore/QUrlQuery>
#endif

namespace QFB
{

class FeedDialogManagerPrivate
{
public:
    QString clientId;
    QString from;
    QString to;
    QUrl link;
    QUrl picture;
    QUrl source;
    QString name;
    QString caption;
    QString description;
    FeedDialogManager::UiType uiType;
};

////// End of private class //////

FeedDialogManager::FeedDialogManager(QObject *parent):
    QObject(parent), d_ptr(new FeedDialogManagerPrivate)
{
}

FeedDialogManager::~FeedDialogManager()
{
}

QString FeedDialogManager::clientId() const
{
    Q_D(const FeedDialogManager);
    return d->clientId;
}

QString FeedDialogManager::from() const
{
    Q_D(const FeedDialogManager);
    return d->from;
}

QString FeedDialogManager::to() const
{
    Q_D(const FeedDialogManager);
    return d->to;
}

QUrl FeedDialogManager::link() const
{
    Q_D(const FeedDialogManager);
    return d->link;
}

QUrl FeedDialogManager::picture() const
{
    Q_D(const FeedDialogManager);
    return d->picture;
}


QUrl FeedDialogManager::source() const
{
    Q_D(const FeedDialogManager);
    return d->source;
}

QString FeedDialogManager::name() const
{
    Q_D(const FeedDialogManager);
    return d->name;
}

QString FeedDialogManager::caption() const
{
    Q_D(const FeedDialogManager);
    return d->caption;
}

QString FeedDialogManager::description() const
{
    Q_D(const FeedDialogManager);
    return d->description;
}

FeedDialogManager::UiType FeedDialogManager::uiType() const
{
    Q_D(const FeedDialogManager);
    return d->uiType;
}

void FeedDialogManager::setClientId(const QString &clientId)
{
    Q_D(FeedDialogManager);
    if (d->clientId != clientId) {
        d->clientId = clientId;
        emit clientIdChanged();
    }
}

void FeedDialogManager::setFrom(const QString &from)
{
    Q_D(FeedDialogManager);
    if (d->from != from) {
        d->from = from;
        emit fromChanged();
    }
}

void FeedDialogManager::setTo(const QString &to)
{
    Q_D(FeedDialogManager);
    if (d->to != to) {
        d->to = to;
        emit toChanged();
    }
}

void FeedDialogManager::setLink(const QUrl &link)
{
    Q_D(FeedDialogManager);
    if (d->link != link) {
        d->link = link;
        emit linkChanged();
    }
}

void FeedDialogManager::setPicture(const QUrl &picture)
{
    Q_D(FeedDialogManager);
    if (d->picture != picture) {
        d->picture = picture;
        emit pictureChanged();
    }
}

void FeedDialogManager::setSource(const QUrl &source)
{
    Q_D(FeedDialogManager);
    if (d->source != source) {
        d->source = source;
        emit sourceChanged();
    }
}

void FeedDialogManager::setName(const QString &name)
{
    Q_D(FeedDialogManager);
    if (d->name != name) {
        d->name = name;
        emit nameChanged();
    }
}

void FeedDialogManager::setCaption(const QString &caption)
{
    Q_D(FeedDialogManager);
    if (d->caption != caption) {
        d->caption = caption;
        emit captionChanged();
    }
}

void FeedDialogManager::setDescription(const QString &description)
{
    Q_D(FeedDialogManager);
    if (d->description != description) {
        d->description = description;
        emit descriptionChanged();
    }
}


void FeedDialogManager::setUiType(UiType uiType)
{
    Q_D(FeedDialogManager);
    if (d->uiType != uiType) {
        d->uiType = uiType;
        emit uiTypeChanged();
    }
}

void FeedDialogManager::displayDialog()
{
    Q_D(FeedDialogManager);
    QStringList otherList;
    if (!d->from.isEmpty()) {
        otherList.append(QString("from=%1").arg(d->from));
    }
    if (!d->to.isEmpty()) {
        otherList.append(QString("to=%1").arg(d->to));
    }
    if (!d->link.isEmpty()) {
        otherList.append(QString("link=%1").arg(d->link.toString()));
    }
    if (!d->picture.isEmpty()) {
        otherList.append(QString("picture=%1").arg(d->picture.toString()));
    }
    if (!d->source.isEmpty()) {
        otherList.append(QString("source=%1").arg(d->source.toString()));
    }
    if (!d->name.isEmpty()) {
        otherList.append(QString("name=%1").arg(d->name));
    }
    if (!d->caption.isEmpty()) {
        otherList.append(QString("caption=%1").arg(d->caption));
    }
    if (!d->description.isEmpty()) {
        otherList.append(QString("description=%1").arg(d->description));
    }

    QString other = otherList.join("&");
    if (!other.isEmpty()) {
        other.prepend("&");
    }


    QString url ("https://www.facebook.com/dialog/feed?display=%1&app_id=%2&\
redirect_uri=https://www.facebook.com/connect/login_success.html%3");
    switch (d->uiType) {
        case Popup:
            url = url.arg("popup", d->clientId, other);
            break;
        case Touch:
            url = url.arg("touch", d->clientId, other);
            break;
        default:
            url = url.arg("page", d->clientId, other);
            break;
    }

    emit urlRequested(QUrl(url));
}

void FeedDialogManager::checkUrl(const QUrl &url)
{
    Q_D(FeedDialogManager);
    if (url.isEmpty()) {
        return;
    }

    QString urlToString = url.toString();
    // Check if the URL is not good
    if (!urlToString.contains(d->clientId)) {
        if (urlToString.contains("https://www.facebook.com/connect/login_success.html")) {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
            QString postId = url.queryItemValue("post_id");
#else
            QUrlQuery urlQuery (url);
            QString postId = urlQuery.queryItemValue("post_id");
#endif
            if (postId.isEmpty()) {
                emit postFailed();
            } else {
                emit postSucceeded(postId);
            }
            return;
        }
        qDebug() << "The user clicked on a wrong link !";
        displayDialog();
    }
}

}
