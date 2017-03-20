#include "Arduino.h"
#include <printf.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "NetworkService.h"
#include "SensorService.h"
#include "ActorService.h"
#include "HardwareIdentification.h"

#ifndef NODE_ID
#define NODE_ID 2
#endif

/*--- Global variables ---*/
NetworkService networkService = NetworkService::getInstance();

#if defined(SENSOR)
SensorService sensorService = SensorService::getInstance();
#elif defined(ACTOR)
ActorService actorService = ActorService::getInstance();
#endif

device_data dataBuffer[5];
device_command commandBuffer[5];

/*--- Methods ---*/

void setup() {
  Serial.begin(115200);
  printf_begin();

  networkService.setupNetwork(NODE_ID);

#if defined(SENSOR)
  sensorService.setupSensor();
#elif defined(ACTOR)
  actorService.setupActor();
#endif
}

void loop() {
  networkService.update();

  bool success = true;

#if defined(SENSOR)
  debugLogln("Reading sensor...")
  int dataNum = sensorService.getReading(dataBuffer);

  debugLogln("Sending data...");
  for (int i = 0; i < dataNum; ++i) {
    debugLog("#");
    debugLog(i);
    debugLog(": ");
    if (networkService.send('S', &dataBuffer[i], sizeof(device_data))) {
      networkService.disconnect();
      debugLogln("success");
    } else {
      debugLogln("FAILED");
      success = false;
    }
  }

#elif defined(ACTOR)
  debugLogln("Received radio interrupt...");
  uint8_t commandNum = networkService.read(commandBuffer);

  debugLog("Received command num: ");
  debugLogln(commandNum);

  for (int i = 0; i < commandNum; ++i) {
    debugLog("Set state to ");
    debugLogln(commandBuffer[i].targetState);

    actorService.setState(commandBuffer[i].targetState != 0);
  }

  if (commandNum > 0) {
    debugLogln("Sending state...");
    bool currentState = actorService.getState();

    device_data actorData{currentState, "relay"};

    if (networkService.send('A', &actorData, sizeof(device_data))) {
      debugLogln("success");
    } else {
      debugLogln("FAILED");
      success = false;
    }
  }

#endif

  if (success) {
    delay(100);
    // disable ADC
    ADCSRA = 0;

#if defined(SENSOR) && !defined(REACTIVE)
    // clear various "reset" flags
    MCUSR = 0;
    // allow changes, disable reset
    WDTCSR = bit (WDCE) | bit (WDE);
    // set interrupt mode and an interval
    WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0);    // set WDIE, and 8 second delay
    wdt_reset();  // pat the dog
#endif

    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    noInterrupts ();           // timed sequence follows
    sleep_enable();

    // turn off brown-out enable in software
    MCUCR = bit (BODS) | bit (BODSE);
    MCUCR = bit (BODS);
    interrupts ();             // guarantees next instruction executed
    sleep_cpu ();

    // cancel sleep as a precaution
    sleep_disable();
  }

}

// watchdog interrupt
ISR (WDT_vect)
{
  wdt_disable();  // disable watchdog
}
