#ifndef SMARTHOME_H
#define SMARTHOME_H

#ifdef QT_CORE_LIB
#include <QObject>
#else
#include "Arduino.h"
#endif

#ifdef QT_CORE_LIB
class SmartHome : public QObject
        #else
class SmartHome
        #endif
{

#ifdef QT_CORE_LIB
    Q_OBJECT
#endif
public:
#ifdef QT_CORE_LIB
    explicit SmartHome(QObject *parent = nullptr);
#else
    SmartHome();
#endif

private:
    Relay relays[] = {
        {
            Relay(Salon,                22),
            Relay(HallBas,              23),
            Relay(CuisineCentral,       24),
            Relay(CuisinePlanDeTravail, 25),
            Relay(ExterieurJardin,      26),
            Relay(ExterieurGarage,      27),
            Relay(Cave,                 28)
            Relay(ChambreJBGauche,       4),
            Relay(ChambreJBDroite,       5),
            Relay(Toilette,              6),
            Relay(ChambreAmiGauche,      7),
            Relay(ChambeAmiDroite,       8),
            Relay(SalleDeDoucheMirroir,  9),
            Relay(SalleDeDoucheDouche,  10),
            Relay(Bureau,               11),
            Relay(Dressing,             12),
            Relay(Grenier,              13),
            Relay(Vestiaire,            22),
            Relay(Garage,               23),
            Relay(HallHaut,             24),
            Relay(Buanderie,            25)
        }
    };
};

#endif // SMARTHOME_H
