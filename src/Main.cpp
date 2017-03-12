#include "Arduino.h"
#include <printf.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

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
    delay(100);
    // disable ADC
    ADCSRA = 0;

#ifndef REACTIVE
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
