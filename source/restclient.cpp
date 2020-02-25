#include "restclient.h"

RestClient::RestClient() :
    m_response("")
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

void RestClient::post(QString url)
{
    QMap<QString,QString> keyAndValue;
    keyAndValue.insert("", "");

    serviceUrl = QUrl(url);

    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");

    QByteArray postData;

    for(auto i = 0; i < keyAndValue.size(); i++){
        qDebug() << keyAndValue.keys()[i];
        qDebug() << keyAndValue.values()[i];
        postData.append(keyAndValue.keys()[i] + "=" + keyAndValue.values()[i]);
    }

    networkManager->post(request, postData);
}

void RestClient::reConnect()
{
    networkManager->deleteLater();
    networkManager = new QNetworkAccessManager();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getSslError(QNetworkReply*,QList<QSslError>)));
}

QString RestClient::response() const
{
    return m_response;
}

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

void RestClient::getSslError(QNetworkReply *replay, QList<QSslError> errorList)
{
    appendResponse("SSL error");
    foreach (QSslError error, errorList) {
        appendResponse(error.errorString());
    }
}

void RestClient::setResponse(QString response)
{
    if (m_response == response)
        return;

    m_response = response;
    emit responseChanged(m_response);
}

void RestClient::appendResponse(QString response)
{
    m_response.append(response + "\n");
    emit responseChanged(m_response);
}
