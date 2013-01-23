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

#include "confirmationprocessor.h"
#include <QtCore/QDebug>
#include "private/abstractgraphprocessor_p.h"

namespace QFB
{

static const char *TRUE_STRING = "true";

class ConfirmationProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit ConfirmationProcessorPrivate();
    bool ok;
};

ConfirmationProcessorPrivate::ConfirmationProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    ok = false;
}

////// End of private class //////

ConfirmationProcessor::ConfirmationProcessor(QObject *parent):
    AbstractGraphProcessor(*(new ConfirmationProcessorPrivate), parent)
{
}

bool ConfirmationProcessor::ok() const
{
    Q_D(const ConfirmationProcessor);
    return d->ok;
}

bool ConfirmationProcessor::processDataSource(QIODevice *dataSource)
{
    /// @todo catch error
    Q_D(ConfirmationProcessor);
    QByteArray data = dataSource->readAll().trimmed();
    qDebug() << data;
    d->ok = (data == TRUE_STRING);
    return true;
}

}
