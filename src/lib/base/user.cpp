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

/**
 * @file user.cpp
 * @brief Implementation of QFB::User
 */

#include "user.h"
#include "object_p.h"

namespace QFB
{

User::User(QObject *parent) :
    UserBase(parent)
{
}

User::User(const PropertiesMap propertiesMap, QObject *parent):
    UserBase(parent)
{
    Q_D(Object);
    d->propertiesMap = propertiesMap;
}

QString User::firstName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(FirstNameProperty).toString();
}

QString User::middleName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(MiddleNameProperty).toString();
}

QString User::lastName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LastNameProperty).toString();
}

QString User::gender() const
{
    Q_D(const Object);
    return d->propertiesMap.value(GenderProperty).toString();
}

QString User::locale() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LocaleProperty).toString();
}

QList<Language *> User::languages() const
{
    Q_D(const Object);
    QVariantList languagesVariant = d->propertiesMap.value(LanguagesProperty).toList();
    QList<Language *> returnedLanguages;
    foreach (QVariant languageVariant, languagesVariant) {
        returnedLanguages.append(languageVariant.value<Language *>());
    }
    return returnedLanguages;
}

QVariantList User::languagesVariant() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LanguagesProperty).toList();
}

QUrl User::link() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LinkProperty).toUrl();
}

QString User::username() const
{
    Q_D(const Object);
    return d->propertiesMap.value(UsernameProperty).toString();
}

QString User::bio() const
{
    Q_D(const Object);
    return d->propertiesMap.value(BioProperty).toString();
}

QDate User::birthday() const
{
    Q_D(const Object);
    return d->propertiesMap.value(BirthdayProperty).toDate();
}

Cover * User::cover() const
{
    Q_D(const Object);
    return d->propertiesMap.value(CoverProperty).value<Cover *>();
}

QString User::email() const
{
    Q_D(const Object);
    return d->propertiesMap.value(EmailProperty).toString();
}

QString User::political() const
{
    Q_D(const Object);
    return d->propertiesMap.value(PoliticalProperty).toString();
}

QString User::picture() const
{
    Q_D(const Object);
    return d->propertiesMap.value(PictureProperty).toString();
}

QString User::quotes() const
{
    Q_D(const Object);
    return d->propertiesMap.value(QuotesProperty).toString();
}

QString User::relationshipStatus() const
{
    Q_D(const Object);
    return d->propertiesMap.value(RelationshipStatusProperty).toString();
}

QString User::religion() const
{
    Q_D(const Object);
    return d->propertiesMap.value(ReligionProperty).toString();
}

UserBase * User::significantOther() const
{
    Q_D(const Object);
    return d->propertiesMap.value(SignificantOtherProperty).value<UserBase *>();
}

QUrl User::website() const
{
    Q_D(const Object);
    return d->propertiesMap.value(WebsiteProperty).toUrl();
}


}
