/*
	Created by Jean-Benoit Tristant, Avril 23, 2017
*/
#ifndef pushbutton_h
#define pushbutton_h

#ifdef QT_CORE_LIB
#include <QObject>
#else
#include "Arduino.h"
#endif

class PushButton
{
  public:
    PushButton(int pin, int name);
    void read();
    void setCallbackClicked(void (*pushButtonCallbackClicked)(int));
    void setCallbackLongClicked(void (*pushButtonCallbackLongClicked)(int, int));

  private:
    void (*_pushButtonCallbackClicked)(int);
    void (*_pushButtonCallbackLongClicked)(int, int);
    int m_pin;
    int m_name;
    int m_state;
    int m_lastState;
    unsigned long m_time;
};

#endif
