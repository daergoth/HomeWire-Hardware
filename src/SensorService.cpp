#include "SensorService.h"

SensorService SensorService::sensorService = SensorService();


SensorService SensorService::getInstance() {
  return sensorService;
}

void SensorService::setupSensor() {
#if TEMPERATURE
  dht.begin();
#elif MOTION
  pinMode(MOISTURE_PIN, INPUT);
  analogWrite(MOISTURE_PIN, 0);
#endif
}

int SensorService::getReading(sensor_data *buffer) {

#if TEMPERATURE
  sensor_data datas[2] = {
      {dht.readTemperature(), "temperature"},
      {dht.readHumidity(),    "humidity"}
  };
  memcpy(buffer, datas, sizeof(datas));
  return 2;

#elif SOILMOISTURE
  sensor_data data[1] = {
    {100 - (analogRead(MOISTURE_PIN) / 10.24), "soilmoisture"}
  };
  memcpy(buffer, data, sizeof(data));
  return 1;

#endif
}



