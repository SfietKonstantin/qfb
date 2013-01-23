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

#ifndef QFB_CONFIRMATIONPROCESSOR_H
#define QFB_CONFIRMATIONPROCESSOR_H

#include "abstractgraphprocessor.h"

namespace QFB
{
class ConfirmationProcessorPrivate;
class QFBBASE_EXPORT ConfirmationProcessor: public AbstractGraphProcessor
{
    Q_OBJECT
public:
    explicit ConfirmationProcessor(QObject *parent = 0);
    bool ok() const;
protected:
    /**
     * @brief Implementation of AbstractProcessor::processDataSource()
     * @param data data to be posted.
     * @return processed data.
     */
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(ConfirmationProcessor)
};

}

#endif // QFB_CONFIRMATIONPROCESSOR_H
