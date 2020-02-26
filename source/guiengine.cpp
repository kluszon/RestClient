#include "guiengine.h"

/*!
 * \brief GuiEngine::m_instance
 */

GuiEngine *GuiEngine::m_instance;

/*!
 * \brief GuiEngine::GuiEngine
 */

GuiEngine::GuiEngine() :
    m_response("")
{
    m_restClient = RestClient::getInstance();
    m_requestModel = RequestBodyModel::getInstance();

    connect(m_restClient, SIGNAL(response(QString)), this, SLOT(parseResponse(QString)));
}

/*!
 * \brief RestClient::response
 * \return
 */

GuiEngine *GuiEngine::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new GuiEngine();

    return m_instance;
}

QString GuiEngine::response() const
{
    return m_response;
}

/*!
 * \brief GuiEngine::getRequest
 * \param url
 */

void GuiEngine::getRequest(QString url)
{
    setResponse("");

    QUrl serviceUrl(url);

    QString getData;

    getData.append("?");

    for(auto i = 0; i < m_requestModel->rowCount(); i++){
        QString key = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_KEY).toString();
        QString value = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_VALUE).toString();
        getData.append(key + "=" + value + "&");
    }

    m_restClient->get(serviceUrl, getData);
}

/*!
 * \brief GuiEngine::postRequest
 * \param url
 */

void GuiEngine::postRequest(QString url)
{
    setResponse("");

    QUrl serviceUrl(url);

    QByteArray postData;

    for(auto i = 0; i < m_requestModel->rowCount(); i++){
        QString key = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_KEY).toString();
        QString value = m_requestModel->data(m_requestModel->index(i,0), RequestBodyModel::BODY_VALUE).toString();
        postData.append(key + "=" + value);
    }

    m_restClient->post(serviceUrl, postData);
}

/*!
 * \brief RestClient::setResponse
 * \param response
 */

void GuiEngine::setResponse(QString response)
{
    if (m_response == response)
        return;

    m_response = response;
    emit responseChanged(m_response);
}

/*!
 * \brief GuiEngine::parseResponse
 * \param newResponse
 */

void GuiEngine::parseResponse(QString newResponse)
{
    newResponse.replace(",",",\n");
    newResponse.replace("{", "\n{\n");
    newResponse.replace("}", "\n}");

    setResponse(newResponse);
}
