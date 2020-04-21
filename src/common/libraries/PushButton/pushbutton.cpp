/*
  Created by Jean-Benoit Tristant, Avril 23, 2017.
*/

#include "pushbutton.h"

PushButton::PushButton(int pin, int name)
{
#ifndef QT_CORE_LIB
  pinMode(pin, INPUT_PULLUP);
#endif
  m_pin = pin;
  m_name = name;
  m_state = 1;
  m_lastState = 1;
  m_time = 0;
}

void PushButton::read()
{
#ifndef QT_CORE_LIB
  if (m_time + 50 < millis()) {
    m_state = digitalRead(m_pin);
    if (m_state == 0 && m_lastState == 1) {
      _pushButtonCallbackClicked(m_name);
    }
    m_lastState = m_state;
    m_time = millis();
  }
#endif
}

void PushButton::setCallbackClicked(void (*pushButtonCallbackClicked)(int))
{
  _pushButtonCallbackClicked = pushButtonCallbackClicked;
}

void PushButton::setCallbackLongClicked(void (*pushButtonCallbackLongClicked)(int, int))
{
  _pushButtonCallbackLongClicked = pushButtonCallbackLongClicked;
}

