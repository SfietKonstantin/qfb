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

#ifndef QFB_ALBUMLISTPROCESSOR_H
#define QFB_ALBUMLISTPROCESSOR_H

/**
 * @file albumlistprocessor.h
 * @brief Definition of QFB::AlbumListProcessor
 */

#include "abstractpagingprocessor.h"

namespace QFB
{

class Album;
class AlbumListProcessorPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASE_EXPORT AlbumListProcessor: public AbstractPagingProcessor
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit AlbumListProcessor(QObject *parent = 0);
    /**
     * @brief Album list
     * @return album list.
     */
    QList<Album *> albumList() const;
protected:
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(AlbumListProcessor)
};

}

#endif // QFB_ALBUMLISTPROCESSOR_H