#ifndef HOMEWIRE_HARDWARE_SENSORSERVICE_H
#define HOMEWIRE_HARDWARE_SENSORSERVICE_H

#include <DHT.h>
#include "NetworkService.h"

// REACTIVE
#define REACTIVE_PIN 2

// TEMPERATURE
#define DHT_PIN 3
#define DHT_TYPE DHT22

// SOILMOISTURE
#define MOISTURE_PIN A0

// MOTION
#define MOTION_PIN REACTIVE_PIN

class SensorService {
public:
    static SensorService getInstance();

    void setupSensor();

    int getReading(device_data *buffer);

private:
    static SensorService sensorService;

    SensorService() = default;

    static void onReactiveChange();

#ifdef TEMPERATURE
    DHT dht = DHT(DHT_PIN, DHT_TYPE);
#endif

};


#endif //HOMEWIRE_HARDWARE_SENSORSERVICE_H
