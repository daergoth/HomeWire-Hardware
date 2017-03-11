#ifndef HOMEWIRE_ARDUINO_LOGGINGCONFIG_H
#define HOMEWIRE_ARDUINO_LOGGINGCONFIG_H

// Comment out to disable debug mode
#define DEBUG_MODE

#ifdef DEBUG_MODE

#define debugLog(x) Serial.print(x);
#define debugLogln(x) Serial.println(x);

#else

#define debugLog(x)
#define debugLogln(x)

#endif

#endif //HOMEWIRE_ARDUINO_LOGGINGCONFIG_H
