#include "relay.h"

Relay::Relay(int pin)
{
	m_cardId = 0;
	m_pin = pin;
	m_id = 0;
	m_state = false;
}

Relay::Relay(int cardId, int pin, RelayEnums id)
{
    m_cardId = cardId;
    m_pin = pin;
    m_id = id;
    m_state = false;
}

void Relay::begin()
{
#ifndef QT_CORE_LIB
    pinMode(m_pin, OUTPUT);
#endif
}

bool Relay::getState()
{
    return m_state;
}

void Relay::turnOn()
{
    m_state = true;
#ifndef QT_CORE_LIB
    digitalWrite(m_pin, m_state);
#endif
}
void Relay::turnOff()
{
    m_state = false;
#ifndef QT_CORE_LIB
    digitalWrite(m_pin, m_state);
#endif
}

void Relay::invertState()
{
    m_state = !m_state;
#ifndef QT_CORE_LIB
    digitalWrite(m_pin, m_state);
#endif
}
