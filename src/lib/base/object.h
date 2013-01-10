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

#ifndef QFB_OBJECT_H
#define QFB_OBJECT_H

/**
 * @file object.h
 * @brief Definition of QFB::Object
 */

#include "base_global.h"
#include "objectbase.h"
#include "qfb.h"

namespace QFB
{

/**
 * @brief An object in Facebook
 *
 * This class represents any entity in Facebook.
 * All Facebook entities provides an id, that can
 * be accessed though the facebookId() property.
 *
 * Facebook entities often have a type, that can
 * be accessed through the objectType() property.
 *
 * @todo provide types when possible in processors
 */
class QFBBASE_EXPORT Object : public ObjectBase
{
    Q_OBJECT
    Q_ENUMS(ObjectType)
    /**
     * @short The object's Facebook ID
     */
    Q_PROPERTY(QString facebookId READ facebookId CONSTANT)
    /**
     * @short The object's type
     */
    Q_PROPERTY(ObjectType objectType READ objectType CONSTANT)
public:
    /**
     * @brief An enumeration describing the different types of Facebook objects
     */
    enum ObjectType {
        /**
         * @short An unknown type
         *
         * This type is provided as a default type for most
         * objects.
         */
        Unknown,
        /**
         * @short The achievement(Instance) object represents the achievement
         * achieved by a user for a particular app.
         */
        Achievement,
        /**
         * @short An album of photos as represented in the Graph API
         */
        Album,
        /**
         * @short An application registered on Facebook Platform as represented in the Graph API
         *
         * Applications a user administers can be retrieved via the /accounts connection on the
         * User object.
         */
        Application,
        /**
         * @short A Checkin represents a single visit to a location
         */
        Checkin,
        /**
         * @short A comment on a Graph API object
         */
        Comment,
        /**
         * @short A web site domain within the Graph API
         */
        Domain,
        /**
         * @short Specifies information about an event
         */
        Event,
        /**
         * @short A Facebook friend list
         */
        FriendList,
        /**
         * @short A Facebook Group
         */
        Group,
        /**
         * @short An object containing statistics about applications, pages, and domains
         */
        Insights,
        /**
         * @short A link shared on a user's wall
         */
        Link,
        /**
         * @short An individual message in the new Facebook messaging system
         */
        Message,
        /**
         * @short A Facebook Note
         */
        Note,
        /**
         * @short An Offer represents an offer that is published by a page
         */
        Offer,
        /**
         * @short You can use the order object to interact with orders created by
         * the application using Facebook Payments to view and update orders as needed.
         */
        Order,
        /**
         * @short A Page in the Graph API
         */
        Page,
        /**
         * @short An individual photo as represented in the Graph API
         */
        Photo,
        /**
         * @short An individual entry in a profile's feed as represented in the Graph API
         */
        Post,
        /**
         * @short A question asked by a user, as represented in the Graph API
         */
        Question,
        /**
         * @short An option allowed as an answer to a Question, as represented in the Graph API
         */
        /// @todo this entry is tricky
        QuestionOption,
        /**
         * @short An object representing a review for an application
         */
        Review,
        /**
         * @short A status message on a user's wall as represented in the Graph API
         */
        Status,
        /**
         * @short A message thread in the new Facebook messaging system as represented in
         * the Graph API.
         */
        Thread,
        /**
         * @short A user profile as represented in the Graph API
         */
        User,
        /**
         * @short An individual Video in the Graph API
         */
        Video
    };
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Object(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties map.
     * @param parent parent object.
     */
    explicit Object(const PropertiesMap &propertiesMap, QObject *parent = 0);
    /**
     * @brief Facebook identifier
     * @return facebook identifier.
     */
    QString facebookId() const;
    /**
     * @brief Object type
     * @return object type.
     */
    ObjectType objectType() const;
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit Object(ObjectBasePrivate &dd, QObject *parent = 0);
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::Object *)

#endif // QFB_OBJECT_H
