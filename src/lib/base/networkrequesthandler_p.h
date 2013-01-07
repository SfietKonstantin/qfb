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

#ifndef QFB_NETWORKREQUESTHANDLER_P_H
#define QFB_NETWORKREQUESTHANDLER_P_H

#include <QtCore/QObject>

class QIODevice;
class QUrl;
namespace QFB
{

class Request;
class NetworkRequestHandlerPrivate;
/// @todo create a queue of requests
class NetworkRequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequestHandler(QObject *parent = 0);
    virtual ~NetworkRequestHandler();
    void get(const Request &request, const QUrl &url);
Q_SIGNALS:
    void error(const QFB::Request &request);
    void finished(const QFB::Request &request, QIODevice *dataSource);
protected:
    QScopedPointer<NetworkRequestHandlerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(NetworkRequestHandler)
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
};

}

#endif // QFB_NETWORKREQUESTHANDLER_P_H
