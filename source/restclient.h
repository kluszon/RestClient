#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QString>

class RestClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString response READ response WRITE setResponse NOTIFY responseChanged)
public:
    RestClient();
    Q_INVOKABLE void post(QString url);
    Q_INVOKABLE void reConnect();

    QString response() const;

public slots:
    void serviceRequestFinished(QNetworkReply *replay);
    void getSslError(QNetworkReply *replay, QList<QSslError> errorList);

    void setResponse(QString response);
    void appendResponse(QString response);

signals:
    void responseChanged(QString response);

private:
    QNetworkAccessManager *networkManager;
    QUrl serviceUrl;
    QString m_response;
};

#endif // RESTCLIENT_H
