#include "restclient.h"

/*!
 * \brief RestClient::m_instance
 */

RestClient *RestClient::m_instance = nullptr;

/*!
 * \brief RestClient::RestClient
 */

RestClient::RestClient()
{
    networkManager = new QNetworkAccessManager();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

/*!
 * \brief RestClient::get
 * \param url
 */

RestClient *RestClient::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new RestClient();

    return m_instance;
}

/*!
 * \brief RestClient::get
 * \param url
 */

void RestClient::get(QUrl url, QString getData)
{
    url.setUrl(url.toString() + getData);
    serviceUrl = QUrl(url);

    QNetworkRequest request(serviceUrl);

    networkManager->get(request);
}

/*!
 * \brief RestClient::post
 * \param url
 */

void RestClient::post(QUrl url, QByteArray postData)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");

    networkManager->post(request, postData);
}

/*!
 * \brief RestClient::reConnect
 */

void RestClient::reConnect()
{
    networkManager->deleteLater();
    networkManager = new QNetworkAccessManager();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

/*!
 * \brief RestClient::requestFinished
 * \param replay
 */

void RestClient::requestFinished(QNetworkReply *replay)
{
    qDebug() << replay->error();

    if(replay->error() == QNetworkReply::NoError){
        QString newReponse(replay->readAll());

        emit response(newReponse);
    }else{
        emit response(replay->errorString());
    }
}

/*!
 * \brief RestClient::getSslError
 * \param replay
 * \param errorList
 */

void RestClient::getSslError(QNetworkReply *replay, QList<QSslError> errorList)
{
    Q_UNUSED(replay);
    QString errorString("SSL error");

    foreach (QSslError error, errorList) {
        errorString += error.errorString();
    }

    emit response(errorString);
}


