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

#ifndef QFB_ABSTRACTPROCESSOR_P_H
#define QFB_ABSTRACTPROCESSOR_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractprocessor_p.h
 * @short Definition of QFB::AbstractProcessorPrivate
 */

#include "request.h"
#include "processors/abstractprocessor.h"

class QIODevice;
class QString;
namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::AbstractProcessor
 */
class AbstractProcessorPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit AbstractProcessorPrivate();
    /**
     * @internal
     * @brief Request
     */
    Request request;
    /**
     * @internal
     * @brief Processing task
     */
    AbstractProcessor::ProcessingTask processingTask;
    /**
     * @internal
     * @brief If data loading from Facebook API is required
     */
    bool needLoading;
    /**
     * @internal
     * @brief Data source
     */
    QIODevice *dataSource;
    /**
     * @internal
     * @brief Error message
     */
    QString error;
};

}

#endif // QFB_ABSTRACTPROCESSOR_P_H
