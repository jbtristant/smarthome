#include <QtDebug>

#include "heatingitem.h"

HeatingItem::HeatingItem(const QString &heatingName, const QString &id, QObject *parent)
    : ListItem(parent), m_heatingName(heatingName), m_id(id)
{
}

QVariant HeatingItem::data(int role) const
{
    switch (role) {
    case HeatingNameRole:
        return heatingName();
    case IdRole:
        return id();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> HeatingItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[HeatingNameRole] = "heating_name";
    names[IdRole] = "id";
    return names;
}

void HeatingListModel::addHeating(const QString &name, const QString &id)
{
    if (find(name) == nullptr) {
        appendRow(new HeatingItem(name, id, this));
    }
}

QString HeatingListModel::serializeList()
{
    QString ret;
    for(int i = 0; i < m_list.size(); ++i) {
        ret.append(static_cast<HeatingItem*>(m_list.at(i))->heatingName()
                   + ";"
                   + static_cast<HeatingItem*>(m_list.at(i))->id());
        if (i < m_list.size() - 1) {
            ret.append("|");
        }
    }
    return ret;
}

void HeatingListModel::askSerialiseList()
{
    emit sendSerializedList(serializeList());
}
