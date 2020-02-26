/*!
 * \class BodyVariable
 * \brief Class BodyVariable contains key and value
 *
 * Class contains key and value for one element of post request body.
 *
 * \author Michał Kluska
 * \version 1.0
 * \date 2020/02/25
 * Contact: kluska.mk@gmail.com
 */

#ifndef BODYVARIABLE_H
#define BODYVARIABLE_H

#include <QString>

class BodyVariable
{
public:
    BodyVariable();
    BodyVariable(QString key, QString value);

    QString key() const;
    void setKey(const QString &key);

    QString value() const;
    void setValue(const QString &value);

private:
    QString m_key;          ///< variable key
    QString m_value;        ///< variable value
};

#endif // BODYVARIABLE_H
