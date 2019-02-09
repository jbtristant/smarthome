#ifndef HEATINGITEM_H
#define HEATINGITEM_H

#include "listmodel.h"

class HeatingItem: public ListItem
{
    Q_OBJECT
public:
    enum HeatingRoles {
        HeatingNameRole = Qt::UserRole + 1,
        IdRole
    };
    Q_ENUM(HeatingRoles)

public:
    HeatingItem(QObject *parent = nullptr): ListItem(parent) {}
    explicit HeatingItem(const QString &heatingName, const QString &id, QObject *parent = nullptr);


    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    inline QString heatingName() const { return m_heatingName; }
    inline QString id() const { return m_id; }

private:
    QString m_heatingName;
    QString m_id;
};

class HeatingListModel : public ListModel {
    Q_OBJECT
public:
    explicit HeatingListModel(QObject *parent = nullptr) : ListModel(new HeatingItem(),  parent) {}

    void addHeating(const QString &name, const QString &id);

    QString serializeList();

signals:
    void sendSerializedList(const QString &serialiseList);
    void heatingStateChanged(const QString &id);

public slots:
    void askSerialiseList();

};


#endif // HEATINGITEM_H
