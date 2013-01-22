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

/**
 * @file photoinformations.cpp
 * @brief Implementation of QFB::PhotoInformations
 */

#include "photoinformations.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief PHOTOINFORMATIONS_WIDTH_KEY
 */
static const char *PHOTOINFORMATIONS_WIDTH_KEY = "width";
/**
 * @internal
 * @brief PHOTOINFORMATIONS_HEIGHT_KEY
 */
static const char *PHOTOINFORMATIONS_HEIGHT_KEY = "height";
/**
 * @internal
 * @brief PHOTOINFORMATIONS_SOURCE_KEY
 */
static const char *PHOTOINFORMATIONS_SOURCE_KEY = "source";


/**
 * @internal
 * @short Private class for QFB::PhotoInformations
 */
class PhotoInformationsPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit PhotoInformationsPrivate();
};

PhotoInformationsPrivate::PhotoInformationsPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

PhotoInformations::PhotoInformations(QObject *parent):
    ObjectBase(parent)
{
}

PhotoInformations::PhotoInformations(const QVariantMap propertiesMap, QObject *parent):
    ObjectBase(*(new PhotoInformationsPrivate), parent)
{
    Q_D(PhotoInformations);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // <<<<< custom object creation code
}

int PhotoInformations::width() const
{
    Q_D(const PhotoInformations);
    // >>>>> property width
    return d->propertiesMap.value(PHOTOINFORMATIONS_WIDTH_KEY).toString().toInt();
    // <<<<< property width
}

int PhotoInformations::height() const
{
    Q_D(const PhotoInformations);
    // >>>>> property height
    return d->propertiesMap.value(PHOTOINFORMATIONS_HEIGHT_KEY).toString().toInt();
    // <<<<< property height
}

QUrl PhotoInformations::source() const
{
    Q_D(const PhotoInformations);
    // >>>>> property source
    return parseUrl(d->propertiesMap.value(PHOTOINFORMATIONS_SOURCE_KEY).toString());
    // <<<<< property source
}


// >>>>> custom source code
// <<<<< custom source code

}
