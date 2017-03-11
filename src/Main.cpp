#include "Arduino.h"
#include <printf.h>
#include "NetworkService.h"
#include "SensorService.h"

#define DELAY 10000

#ifndef NODE_ID
#define NODE_ID 2
#endif

/*--- Global variables ---*/
NetworkService networkService = NetworkService::getInstance();
SensorService sensorService = SensorService::getInstance();

sensor_data dataBuffer[5];

/*--- Methods ---*/

void setup() {
  Serial.begin(115200);
  printf_begin();

  networkService.setupNetwork(NODE_ID);
  sensorService.setupSensor();
}

void loop() {
  networkService.update();

  debugLogln("Reading sensor...")
  int dataNum = sensorService.getReading(dataBuffer);

  bool successful_send = true;

  debugLogln("Sending data...");
  for (int i = 0; i < dataNum; ++i) {
    debugLog("#");
    debugLog(i);
    debugLog(": ");
    if (networkService.send('S', &dataBuffer[i], sizeof(sensor_data))) {
      debugLogln("success");
    } else {
      debugLogln("FAILED");
      successful_send = false;
    }
  }

  if (successful_send) {
    delay(DELAY);
  }

}
