/*!
 * \class RequestBodyModel
 * \brief Class Update contatins list of BodyVariable pointers.
 *
 * Class contains keys and values for request body.
 *
 * \author Michał Kluska
 * \version 1.0
 * \date 2020/02/25
 * Contact: support@pxm.pl
 */


#ifndef REQUESTBODYMODEL_H
#define REQUESTBODYMODEL_H

#include <QAbstractListModel>
#include <QPair>

#include "bodyvariable.h"

class RequestBodyModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /*!
     * \brief The Roles enum
     */

    enum Roles{
        BODY_KEY,       ///< Key
        BODY_VALUE      ///< Value
    };
    Q_ENUM(Roles)

    explicit RequestBodyModel(QObject *parent = nullptr);
    static RequestBodyModel *getInstance();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void addRow(QString key = "", QString value = "");          ///< Add row
    Q_INVOKABLE void removeRow(int index);                                  ///< Remove row

    QHash<int, QByteArray> roleNames() const;                               ///< Method return role name

private:
    QList<BodyVariable *> m_requestBody;        ///< List of body variable pointer
    static RequestBodyModel *m_instance;
};

#endif // REQUESTBODYMODEL_H
