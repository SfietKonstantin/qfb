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

#ifndef QFB_ARGUMENTPAIR_H
#define QFB_ARGUMENTPAIR_H

/**
 * @file argumentpair.h
 * @brief Definition of QFB::ArgumentPair
 */

#include <QtCore/QString>
#include <QtCore/QPair>

namespace QFB
{

/**
 * @brief Arugment pair
 *
 * This typedef defines a mapping between a pair of strings,
 * that used to identify the key and the value in an URL
 * argument.
 */
typedef QPair<QString, QString> ArgumentPair;

}

#endif // QFB_ARGUMENTPAIR_H
