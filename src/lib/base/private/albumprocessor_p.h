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

#ifndef QFB_ALBUMPROCESSOR_P_H
#define QFB_ALBUMPROCESSOR_P_H

#include "abstractgraphprocessor_p.h"
#include "jsonhelper_p.h"

namespace QFB
{

class Album;
class AlbumProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit AlbumProcessorPrivate();
    static Album * createAlbum(const JsonObject &jsonObject);
    Album *album;
};

}

#endif // QFB_ALBUMPROCESSOR_P_H
