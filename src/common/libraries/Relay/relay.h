// Relay.h

#ifndef RELAY_h
#define RELAY_h

#ifdef QT_CORE_LIB
#include <QObject>
#else
#include "Arduino.h"
#endif

class Relay
{
public:
    enum RelayEnums {
        SalonEnum                =  0,
        HallBasEnum              =  1,
        CuisineCentralEnum       =  2,
        CuisinePlanDeTravailEnum =  3,
        ExterieurJardinEnum      =  4,
        ExterieurGarageEnum      =  5,
        CaveEnum                 =  6,
        ChambreJBGaucheEnum      =  7,
        ChambreJBDroiteEnum      =  8,
        ToiletteEnum             =  9,
        ChambreAmiGaucheEnum     = 10,
        ChambeAmiDroiteEnum      = 11,
        SalleDeDoucheMirroirEnum = 12,
        SalleDeDoucheDoucheEnum  = 13,
        BureauEnum               = 14,
        DressingEnum             = 15,
        GrenierEnum              = 16,
        VestiaireEnum            = 17,
        GarageEnum               = 18,
        HallHautEnum             = 19,
        BuanderieEnum            = 20,
        RelayNamesEnumSize       = 21
    };

    Relay(int pin);
    Relay(int cardId, int pin, RelayEnums id);
    void begin();
    bool getState();
    void turnOn();
    void turnOff();
    void invertState();

#ifdef QT_CORE_LIB
Q_SIGNALS:
    void stateChanged(int cardId, int pin, RelayEnums id, bool state);
#endif

protected:
    int m_cardId;
    int m_pin;
    RelayEnums m_id;
    bool m_state;

};

#endif
