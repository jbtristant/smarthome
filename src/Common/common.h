#ifndef COMMON_H
#define COMMON_H

#include <QObject>


class Rooms: public QObject
{
    Q_OBJECT
public:
    Rooms() : QObject() {}

    enum Room { Salon, SalleDeBain, Cuisine, Hall, Chambre };
    Q_ENUM(Room)
};

#endif // COMMON_H
