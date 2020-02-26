#include "restclient.h"

/*!
 * \brief RestClient::RestClient
 */

RestClient::RestClient() :
    m_response("")
{
    networkManager = new QNetworkAccessManager();
    m_requestModel = RequestBodyModel::getInstance();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

/*!
 * \brief RestClient::get
 * \param url
 */

void RestClient::get(QString url)
{
    setResponse("");

    QString getData;

    getData.append("?");

    for(auto i = 0; i < m_requestModel->rowCount(); i++){
        QString key = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_KEY).toString();
        QString value = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_VALUE).toString();
        getData.append(key + "=" + value + "&");
    }

    url = url + getData;

    serviceUrl = QUrl(url);

    QNetworkRequest request(serviceUrl);

    networkManager->get(request);
}

/*!
 * \brief RestClient::post
 * \param url
 */

void RestClient::post(QString url)
{
    setResponse("");

    serviceUrl = QUrl(url);

    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");

    QByteArray postData;

    for(auto i = 0; i < m_requestModel->rowCount(); i++){
        QString key = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_KEY).toString();
        QString value = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_VALUE).toString();
        postData.append(key + "=" + value);
    }

    networkManager->post(request, postData);
}

/*!
 * \brief RestClient::reConnect
 */

void RestClient::reConnect()
{
    networkManager->deleteLater();
    networkManager = new QNetworkAccessManager();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

/*!
 * \brief RestClient::response
 * \return
 */

QString RestClient::response() const
{
    return m_response;
}

/*!
 * \brief RestClient::serviceRequestFinished
 * \param replay
 */

void RestClient::serviceRequestFinished(QNetworkReply *replay)
{
    qDebug() << replay->error();

    if(replay->error() == QNetworkReply::NoError){
        QString newReponse(replay->readAll());
        newReponse.replace(",",",\n");
        newReponse.replace("{", "\n{\n");
        newReponse.replace("}", "\n}");
        appendResponse(newReponse);
    }else{
        appendResponse(replay->errorString());
    }
}

/*!
 * \brief RestClient::getSslError
 * \param replay
 * \param errorList
 */

void RestClient::getSslError(QNetworkReply *replay, QList<QSslError> errorList)
{
    appendResponse("SSL error");
    foreach (QSslError error, errorList) {
        appendResponse(error.errorString());
    }
}

/*!
 * \brief RestClient::setResponse
 * \param response
 */

void RestClient::setResponse(QString response)
{
    if (m_response == response)
        return;

    m_response = response;
    emit responseChanged(m_response);
}

/*!
 * \brief RestClient::appendResponse
 * \param response
 */

void RestClient::appendResponse(QString response)
{
    m_response.append(response + "\n");
    emit responseChanged(m_response);
}
