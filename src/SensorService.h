#ifndef HOMEWIRE_HARDWARE_SENSORSERVICE_H
#define HOMEWIRE_HARDWARE_SENSORSERVICE_H

#include <DHT.h>

#define DHT_PIN 3
#define DHT_TYPE DHT22

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
    SensorService() = default;
    static SensorService sensorService;

#if TEMPERATURE
    DHT dht = DHT(DHT_PIN, DHT_TYPE);
#elif MOTION

#endif

};




#endif //HOMEWIRE_HARDWARE_SENSORSERVICE_H
