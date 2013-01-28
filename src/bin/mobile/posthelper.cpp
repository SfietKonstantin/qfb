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

#include "posthelper.h"
#include "objects/namedobject.h"

#include <QtCore/QDebug>

static const char *RICH_TEXT_NAME
    = "<a style=\"text-decoration:none; color:#0057AE\" href=\"%1-%2\">%3</a>";

PostHelper::PostHelper(QObject *parent) :
    QObject(parent)
{
    m_post = 0;
    m_to = 0;
}

QFB::Post * PostHelper::post() const
{
    return m_post;
}

QFB::NamedObject * PostHelper::to() const
{
    return m_to;
}

QString PostHelper::header() const
{
    return m_header;
}

QString PostHelper::message() const
{
    return m_message;
}

void PostHelper::setPost(QFB::Post *post)
{
    if (m_post != post) {
        m_post = post;
        createPost();
        emit postChanged();
    }
}

void PostHelper::createPost()
{
    // Extract the to

    QString message;
    if (!m_post->message().isEmpty()) {
        message = m_post->message();
    }

    if (m_post->message().isEmpty() && !m_post->story().isEmpty()) {
        message = m_post->story();
    }

    if (m_message != message) {
        m_message = message;
        emit messageChanged();
    }

    QFB::NamedObject *from = m_post->from();
    QFB::NamedObject *to = 0;
    if (m_post->to().count() == 1) {
        to = m_post->to().first();
    }
    QString toHeader = RICH_TEXT_NAME;
    if (to) {
        QString elidedTo = elideText(to->name(), 20);
        toHeader = toHeader.arg(to->facebookId(), elidedTo, elidedTo);
    }
    QString elidedFrom;
    if (to) {
        elidedFrom = elideText(from->name(), 20);
    } else {
        elidedFrom = elideText(from->name(), 40);
    }
    QString header = RICH_TEXT_NAME;
    header = header.arg(from->facebookId(), elidedFrom, elidedFrom);

    if (to) {
        header.append(" &gt; ");
        header.append(toHeader);
    }

    if (m_to != to) {
        m_to = to;
        emit toChanged();
    }
    if (m_header != header) {
        m_header = header;
        emit headerChanged();
    }
}

QString PostHelper::elideText(const QString &text, int count)
{
    if (text.size() <= count) {
        return text;
    }
    QString elidedText = text.left(count - 2);
    elidedText.append(QString::fromUtf8(" …"));
    return elidedText;
}
