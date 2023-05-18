/*!
 * \class RestClient
 * \brief Class RestClient for manage REST
 *
 * Class manage REST comunication.
 *
 * \author Michał Kluska
 * \version 1.0
 * \date 2020/02/25
 * Contact: kluska.mk@gmail.com
 */

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QString>

class RestClient : public QObject
{
    Q_OBJECT

public:
    static RestClient *getInstance();
    void get(QUrl url, QString getData);        ///< GET request
    void post(QUrl url, QByteArray postData);   ///< POST request
    void reConnect();                           ///< Reconnect

public slots:
    void requestFinished(QNetworkReply *replay);
    void getSslError(QNetworkReply *replay, QList<QSslError> errorList);

signals:
    void response(QString);

private:
    RestClient();
    static RestClient *m_instance;          ///< Class instance
    QNetworkAccessManager *networkManager;  ///< Pointer to network manager
    QUrl serviceUrl;                        ///< Service URL
};

#endif // RESTCLIENT_H
