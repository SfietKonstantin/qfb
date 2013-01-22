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

#ifndef QFB_ABSTRACTPROCESSOR_H
#define QFB_ABSTRACTPROCESSOR_H

/**
 * @file abstractprocessor.h
 * @brief Definition of QFB::AbstractProcessor
 */

#include "base_global.h"
#include <QtCore/QObject>
#include <QtCore/QRunnable>
#include <QtCore/QVariantMap>
#include "argumentpair.h"

class QIODevice;
namespace QFB
{

class Query;
class AbstractProcessorPrivate;

/**
 * @brief Base class for a processor
 *
 * A processor is responsible for performing preprocessing
 * on an URL or a graph, as well as doing post processing,
 * that is converting a reply from Facebook, that is basically
 * a QIODevice, to something formatted, like a Facebook object,
 * that takes the form of a QObject.
 *
 * Preprocessing is useful for caching data, or fixing URL.
 * When a preprocessing task is enough to get the information,
 * like with a caching system, loading from the web is not
 * useful anymore, that's why there is a system to tell the
 * processor that there is no need to perform data loading.
 * It is set through setNeedLoading().
 *
 * Subclasses of that class provides specific implementations
 * as well as getter for processed information.
 *
 * This class provides a virtual method that perform post
 * preprocessing. By default, this method do not perform anything.
 * In order to do post data preprocessing, you should reimplement
 * this method.
 *
 * This class do not provide any other preprocessing method. Instead
 * it use the generic preprocess() pure virtual method.
 * AbstractGraphProcessor provides a better method, focusing on the
 * passed graph and arguments.
 *
 * @see AbstractGraphProcessor
 */
class QFBBASE_EXPORT AbstractProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    /**
     * @brief Processing task to perform
     */
    enum ProcessingTask {
        /**
         * @short No processing task
         */
        NoProcessing,
        /**
         * @short Preprocessing task
         */
        Preprocessing,
        /**
         * @short %Post processing task
         */
        PostProcessing
    };
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit AbstractProcessor(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractProcessor();
    /**
     * @brief Query to process
     * @return query to process.
     */
    Query query() const;
    /**
     * @brief Error message
     *
     * The error message should be set with setError().
     * It is only useful when the process failed.
     *
     * @return error message.
     */
    QString errorString() const;
    /**
     * @brief Implementation of QProcess::run()
     */
    void run();
public Q_SLOTS:
    /**
     * @brief Set the query to process
     * @param query query to process.
     */
    void setQuery(const Query &query);
    /**
     * @brief Set the processing task
     * @param processingTask processing task.
     */
    void setProcessingTask(ProcessingTask processingTask);
    /**
     * @brief Set the data source to process
     *
     * This is needed only for post processing.
     *
     * @param dataSource data source to process.
     */
    void setDataSource(QIODevice *dataSource);
Q_SIGNALS:
    /**
     * @brief Process failed
     */
    void error();
    /**
     * @brief Preprocessing finished
     * @param needLoading if data loading from Facebook API is required.
     */
    void preprocessingFinished(bool needLoading);
    /**
     * @brief Post processing finished
     */
    void postProcessingFinished();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractProcessor(AbstractProcessorPrivate &dd, QObject *parent);
    /**
     * @brief Preprocess
     *
     * Reimplement this method in subclasses to perform the
     * preprocessing task.
     *
     * @return if the preprocessing task is successful.
     */
    virtual bool preprocess() = 0;
    /**
     * @brief Process post data
     *
     * This method is used to perform a preprocessing of the data
     * that will be posted. The data is passed through a variant map
     * and should be converted to a byte array that will be posted.
     *
     * By default, this method do not do anything.
     *
     * @param data data to be posted.
     * @return processed data.
     */
    virtual QByteArray processPostData(const QVariantMap &data);
    /**
     * @brief Process data source
     *
     * This method is used to perform post processing. It provides
     * the data source where data from Facebook are stored as a QIODevice.
     *
     * Reimplement this method in subclasses to perform the
     * postprocessing task.
     *
     * @param dataSource data source.
     * @return if the data processing task is successful.
     */
    virtual bool processDataSource(QIODevice *dataSource) = 0;
    /**
     * @brief Set if data loading from Facebook API is required
     * @param needLoading if data loading from Facebook API is required.
     */
    void setNeedLoading(bool needLoading = true);
    /**
     * @brief Set the error message
     * @param error error message.
     */
    void setError(const QString &error);
    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractProcessorPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractProcessor)
};

}

#endif // QFB_ABSTRACTPROCESSOR_H
