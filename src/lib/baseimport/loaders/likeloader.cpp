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

#include "likeloader.h"
#include "private/abstractloader_p.h"
#include "processors/confirmationprocessor.h"
#include "querymanager.h"

namespace QFB
{

class LikeLoaderPrivate: public AbstractLoaderPrivate
{
public:
    LikeLoaderPrivate(LikeLoader *q);
    LikeLoader::LikeOperation likeOperation;
};

LikeLoaderPrivate::LikeLoaderPrivate(LikeLoader *q):
    AbstractLoaderPrivate(q)
{
}

////// End of private class //////

LikeLoader::LikeLoader(QObject *parent):
    AbstractGraphLoader(*(new LikeLoaderPrivate(this)), parent)
{
    Q_D(LikeLoader);
    d->likeOperation = Like;
}

LikeLoader::LikeOperation LikeLoader::likeOperation() const
{
    Q_D(const LikeLoader);
    return d->likeOperation;
}

void LikeLoader::setLikeOperation(LikeOperation likeOperation)
{
    Q_D(LikeLoader);
    if (loading()) {
        return;
    }

    if (d->likeOperation != likeOperation) {
        d->likeOperation = likeOperation;
        emit likeOperationChanged();
    }
}

Query LikeLoader::createRequest(const QString &graph, const QString &arguments)
{
    Q_UNUSED(arguments)
    Q_D(LikeLoader);
    if (!queryManager()) {
        return Query();
    }

    switch (d->likeOperation) {
    case Like:
        return queryManager()->queryConfirmedCreate(graph);
        break;
    case Unlike:
        return queryManager()->queryConfirmedDelete(graph);
        break;
    default:
        return Query();
        break;
    }
}

void LikeLoader::handleReply(AbstractProcessor *processor)
{
    ConfirmationProcessor *confirmationProcessor = qobject_cast<ConfirmationProcessor *>(processor);
    if (!confirmationProcessor->ok()) {
        /// @todo better error
        setError(tr("Cannot perform operation"));
    }
}

}
