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

#include "userinfohelper.h"
#include "language.h"

#include <QtCore/QStringList>

UserInfoHelper::UserInfoHelper(QObject *parent) :
    QObject(parent)
{
    m_user = 0;
}

QFB::User * UserInfoHelper::user() const
{
    return m_user;
}

QString UserInfoHelper::formattedInformations() const
{
    return m_formattedInformations;
}

QString UserInfoHelper::bio() const
{
    return m_bio;
}

QString UserInfoHelper::quotes() const
{
    return m_quotes;
}

void UserInfoHelper::setUser(QFB::User *user)
{
    if (m_user != user) {
        m_user = user;
        createText();
        emit userChanged();
    }
}

void UserInfoHelper::createText()
{
    if (!m_user) {
        return;
    }

    QString formattedInformations;

    // Add gender (and interested in)
    if (!m_user->gender() == QFB::User::Unknown) {
        QString gender;
        switch(m_user->gender()) {
        case QFB::User::Male:
            gender = tr("Male");
            break;
        case QFB::User::Female:
            gender = tr("Female");
            break;
        default:
            break;
        }

        formattedInformations += QString("<b>%1</b>: %2\n").arg(tr("Gender"), gender);
    }

    formattedInformations += "\n";

    // Add birthday
    QDate birthday = m_user->birthday();
    if (birthday.isValid()) {
        QString birthdayString;
        if (birthday.year() == 1900) {
            birthdayString = birthday.toString("dd/MM");
        } else {
            birthdayString = birthday.toString("dd/MM/yyyy");
        }
        formattedInformations += QString("<b>%1</b>: %2\n").arg(tr("Birthday"), birthdayString);
    }

    formattedInformations += "\n";

    // Add languages
    if (!m_user->languages().isEmpty()) {
        QStringList languagesList;
        foreach (QFB::Language * language, m_user->languages()) {
            languagesList.append(language->name());
        }
        QString languageString = languagesList.join(", ");
        formattedInformations += QString("<b>%1</b>: %2\n").arg(tr("Language"), languageString);
    }

    formattedInformations += "\n";

    // Religion and political view
    if (!m_user->religion().isEmpty()) {
        formattedInformations += QString("<b>%1</b>: %2\n").arg(tr("Religion"), m_user->religion());
    }
    if (!m_user->political().isEmpty()) {
        formattedInformations += QString("<b>%1</b>: %2\n").arg(tr("Political view"),
                                                                m_user->political());
    }


    formattedInformations = formattedInformations.trimmed();
    formattedInformations = formattedInformations.replace("\n", "<br/>");


    if (m_formattedInformations != formattedInformations) {
        m_formattedInformations = formattedInformations;
        emit formattedInformationsChanged();
    }

    QString bio = m_user->bio();
    if (m_bio != bio) {
        m_bio = bio;
        emit bioChanged();
    }

    QString quotes = m_user->quotes();
    if (m_quotes != quotes) {
        m_quotes = quotes;
        emit quotesChanged();
    }
}
