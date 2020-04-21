#include "smarthome.h"

#ifdef QT_CORE_LIB
SmartHome::SmartHome(QObject *parent) : QObject(parent)
#else
SmartHome::SmartHome()
#endif
{

}

