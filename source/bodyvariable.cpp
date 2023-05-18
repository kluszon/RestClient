#include "bodyvariable.h"

/*!
 * \brief BodyVariable::BodyVariable
 */

BodyVariable::BodyVariable() :
    m_key(""),
    m_value("")
{

}

/*!
 * \brief BodyVariable::BodyVariable
 * \param key - new key
 * \param value - new variable
 */

BodyVariable::BodyVariable(QString key, QString value) :
    m_key(key),
    m_value(value)
{

}

QString BodyVariable::key() const
{
    return m_key;
}

void BodyVariable::setKey(const QString &key)
{
    m_key = key;
}

QString BodyVariable::value() const
{
    return m_value;
}

void BodyVariable::setValue(const QString &value)
{
    m_value = value;
}
