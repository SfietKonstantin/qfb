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
#include <QtCore/QRegExp>

static const char *RICH_TEXT_NAME
    = "<a style=\"text-decoration:none; color:#0057AE\" href=\"user----%1----%2\">%3</a>";

static const char *URL_REGEXP = "((http://|https://|www.)[a-zA-Z0-9_\\.\\-~%/#]*)";
static const char *RICH_TEXT_URL
    = "<a style=\"text-decoration:none; color:#0057AE\" href=\"url----%1\">%2</a>";

bool tagLesser(QFB::PostTag *tag1, QFB::PostTag *tag2)
{
    return tag1->offset() < tag2->offset();
}

PostHelper::PostHelper(QObject *parent) :
    QObject(parent)
{
    m_post = 0;
    m_fancy = true;
    m_to = 0;
}

QFB::Post * PostHelper::post() const
{
    return m_post;
}

bool PostHelper::fancy() const
{
    return m_fancy;
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

QString PostHelper::via() const
{
    return m_via;
}

void PostHelper::setPost(QFB::Post *post)
{
    if (m_post != post) {
        m_post = post;
        createPost();
        emit postChanged();
    }
}

void PostHelper::setFancy(bool fancy)
{
    if (m_fancy != fancy) {
        m_fancy = fancy;
        createPost();
        emit fancyChanged();
    }
}

void PostHelper::createPost()
{
    if (!m_post) {
        return;
    }

    // Process message
    QString message;
    if (m_fancy) {
        QString endMessage = m_post->message();
        QList<QFB::PostTag *> messageTags = m_post->messageTags();
        qSort(messageTags.begin(), messageTags.end(), tagLesser);

        int previousOffset = 0;
        foreach (QFB::PostTag *tag, messageTags) {
            message.append(endMessage.left(tag->offset() - previousOffset));
            endMessage = endMessage.remove(0, tag->offset() + tag->length() - previousOffset);
            previousOffset = tag->offset() + tag->length();
            message.append(QString(RICH_TEXT_NAME).arg(tag->facebookId(), tag->name(),
                                                       tag->name()));
        }
        message.append(endMessage);

        // Parse links
        endMessage = message;
        message.clear();

        QRegExp urlRegExp(URL_REGEXP);
        int nextUrlIndex = endMessage.indexOf(urlRegExp);
        while (nextUrlIndex != -1) {
            QString captured = urlRegExp.cap(1);
            QString url = captured;
            if (!url.startsWith("http://")) {
                url.prepend("http://");
            }
            message.append(endMessage.left(nextUrlIndex));
            endMessage = endMessage.remove(0, nextUrlIndex + captured.size());
            message.append(QString(RICH_TEXT_URL).arg(url, captured));
            nextUrlIndex = endMessage.indexOf(urlRegExp);
        }
        message.append(endMessage);
    } else {
        message = m_post->message();
    }
    message.replace("\n", "<br/>");

    if (m_message != message) {
        m_message = message;
        emit messageChanged();
    }

    // Process from and to
    QFB::NamedObject *from = m_post->from();
    QList<QFB::NamedObject *> toList = m_post->to();
    foreach (QFB::PostTag *messageTag, m_post->messageTags()) {
        foreach (QFB::NamedObject *to, toList) {
            if (messageTag->facebookId() == to->facebookId()) {
                toList.removeAll(to);
            }
        }
    }

    QFB::NamedObject *to = 0;
    if (toList.count() == 1) {
        to = toList.first();
    }
    QString toHeader = RICH_TEXT_NAME;
    if (to) {
        QString elidedTo = elideText(to->name(), 30);
        toHeader = toHeader.arg(to->facebookId(), to->name(), elidedTo);
    }
    QString elidedFrom;
    if (to) {
        elidedFrom = elideText(from->name(), 30);
    } else {
        elidedFrom = elideText(from->name(), 60);
    }
    QString header = RICH_TEXT_NAME;
    header = header.arg(from->facebookId(), from->name(), elidedFrom);

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

    // Via
    QString via;
    if (!m_post->application()->name().isEmpty()) {
        via = tr("Via %1").arg(m_post->application()->name());
    }
    if (m_via != via) {
        m_via = via;
        emit viaChanged();
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
