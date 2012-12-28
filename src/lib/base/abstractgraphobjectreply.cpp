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

#include "abstractgraphobjectreply.h"
#include "abstractgraphobjectreply_p.h"

namespace QFB
{

AbstractGraphObjectReplyPrivate::AbstractGraphObjectReplyPrivate(AbstractGraphObjectReply *q):
    AbstractGraphReplyPrivate(q)
{
}

////// End of private class //////

AbstractGraphObjectReply::AbstractGraphObjectReply(QObject *parent):
    AbstractGraphReply(*(new AbstractGraphObjectReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphObjectReply);
    d->networkAccessManager = 0;
    d->running = false;
    d->objectParent = 0;
}

AbstractGraphObjectReply::AbstractGraphObjectReply(QNetworkAccessManager *networkAccessManager,
                                                   QObject *objectParent, QObject *parent):
    AbstractGraphReply(*(new AbstractGraphObjectReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphObjectReply);
    d->networkAccessManager = networkAccessManager;
    d->running = false;
    d->objectParent = objectParent;
}

AbstractGraphObjectReply::AbstractGraphObjectReply(AbstractGraphObjectReplyPrivate &dd,
                                                   QObject *parent):
    AbstractGraphReply(dd, parent)
{
}

QObject * AbstractGraphObjectReply::objectParent() const
{
    Q_D(const AbstractGraphObjectReply);
    return d->objectParent;
}

}
