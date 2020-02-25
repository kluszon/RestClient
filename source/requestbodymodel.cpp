#include "requestbodymodel.h"
#include <QDebug>

RequestBodyModel *RequestBodyModel::m_instance = nullptr;

/*!
 * \brief RequestBodyModel::RequestBodyModel
 * \param parent
 */

RequestBodyModel::RequestBodyModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

/*!
 * \brief RequestBodyModel::getInstance
 * \return
 */

RequestBodyModel *RequestBodyModel::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new RequestBodyModel();
    }
    return m_instance;
}

/*!
 * \brief RequestBodyModel::rowCount
 * \param parent
 * \return
 */

int RequestBodyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_requestBody.size();
}

/*!
 * \brief RequestBodyModel::data
 * \param index
 * \param role
 * \return
 */

QVariant RequestBodyModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        switch(role)
        {
            case BODY_KEY:
                return  m_requestBody.at(index.row())->key();
            break;
            case BODY_VALUE:
                return m_requestBody.at(index.row())->value();
            break;
            default:
                qDebug() << "Not supposed";
                return QVariant();
        }

    }else{
        qDebug() << "Warning: " << index.row();
        return QVariant();
    }
}

/*!
 * \brief RequestBodyModel::setData
 * \param index
 * \param value
 * \param role
 * \return
 */

bool RequestBodyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(data(index, role) != value)
    {
        switch(role)
        {
            case BODY_KEY:
                m_requestBody.at(index.row())->setKey(value.toString());
            break;
            case BODY_VALUE:
                m_requestBody.at(index.row())->setValue(value.toString());
            break;
            default:
                return false;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

/*!
 * \brief RequestBodyModel::addRow
 * \param key
 * \param value
 */

void RequestBodyModel::addRow(QString key, QString value)
{
    beginInsertRows(QModelIndex(), m_requestBody.size(), m_requestBody.size());

    BodyVariable *variable = new BodyVariable(key, value);
    m_requestBody.append(variable);

    endInsertRows();
}

/*!
 * \brief RequestBodyModel::removeRow
 * \param index
 */

void RequestBodyModel::removeRow(int index)
{
    beginRemoveRows(QModelIndex(), index, index);

    BodyVariable *variableToRemove = m_requestBody.at(index);

    m_requestBody.removeAt(index);

    delete variableToRemove;

    endRemoveRows();
}

/*!
 * \brief RequestBodyModel::roleNames
 * \return
 */

QHash<int, QByteArray> RequestBodyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BODY_KEY] = "key";
    roles[BODY_VALUE] = "value";
    return roles;
}
