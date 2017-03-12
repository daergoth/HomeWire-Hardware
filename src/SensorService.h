#ifndef HOMEWIRE_HARDWARE_SENSORSERVICE_H
#define HOMEWIRE_HARDWARE_SENSORSERVICE_H

#include <DHT.h>

#define DHT_PIN 3
#define DHT_TYPE DHT22

#define MOISTURE_PIN A0

#define REACTIVE_PIN 2

struct sensor_data {
    float data;
    char type[15];
};

class SensorService {
public:
    static SensorService getInstance();

    void setupSensor();
    int getReading(sensor_data *buffer);

private:
    static SensorService sensorService;

    SensorService() = default;
    static void onReactiveChange();

#if TEMPERATURE
    DHT dht = DHT(DHT_PIN, DHT_TYPE);
#elif SOILMOISTURE

#endif

};




#endif //HOMEWIRE_HARDWARE_SENSORSERVICE_H
