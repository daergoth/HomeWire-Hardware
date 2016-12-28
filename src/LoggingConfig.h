#ifndef HOMEWIRE_ARDUINO_LOGGINGCONFIG_H
#define HOMEWIRE_ARDUINO_LOGGINGCONFIG_H

#define DEBUG_MODE 1
#define log(x) if(DEBUG_MODE){Serial.print(x);}
#define logln(x) if(DEBUG_MODE){Serial.println(x);}

#endif //HOMEWIRE_ARDUINO_LOGGINGCONFIG_H
