/*!
 * \class GuiEngine
 * \brief Class use as gui engine
 *
 * Class use gui to call functionality.
 *
 * \author Michał Kluska
 * \version 1.0
 * \date 2020/02/26
 * Contact: kluska.mk@gmail.com
 */


#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <QObject>
#include <QUrl>
#include <QJsonDocument>

#include "restclient.h"
#include "requestbodymodel.h"

class GuiEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ response WRITE setResponse NOTIFY responseChanged) ///< Text responce to display on dialogue

public:
    static GuiEngine *getInstance();
    QString response() const;
    Q_INVOKABLE void getRequest(QString url);
    Q_INVOKABLE void postRequest(QString url);

public slots:
    void setResponse(QString response);
    void parseResponse(QString newResponse);

signals:
    void responseChanged(QString response);

private:
    GuiEngine();
    static GuiEngine *m_instance;
    QString m_response;
    RestClient *m_restClient;
    RequestBodyModel *m_requestModel;       ///< Request model
};

#endif // GUIENGINE_H
