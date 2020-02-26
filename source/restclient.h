/*!
 * \class RestClient
 * \brief Class RestClient for manage REST
 *
 * Class manage REST comunication.
 *
 * \author Michał Kluska
 * \version 1.0
 * \date 2020/02/25
 * Contact: support@pxm.pl
 */

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QString>

#include "requestbodymodel.h"

class RestClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString response READ response WRITE setResponse NOTIFY responseChanged) ///< Text responce to display on dialogue

public:
    RestClient();
    Q_INVOKABLE void get(QString url);      ///< GET request
    Q_INVOKABLE void post(QString url);     ///< POST request
    Q_INVOKABLE void reConnect();           ///< Reconnect

    QString response() const;               ///< Request response

public slots:
    void serviceRequestFinished(QNetworkReply *replay);
    void getSslError(QNetworkReply *replay, QList<QSslError> errorList);

    void setResponse(QString response);
    void appendResponse(QString response);

signals:
    void responseChanged(QString response);

private:
    QNetworkAccessManager *networkManager;  ///< Pointer to network manager
    QUrl serviceUrl;                        ///< Service URL
    QString m_response;                     ///< Response
    RequestBodyModel *m_requestModel;       ///< Request model
};

#endif // RESTCLIENT_H
