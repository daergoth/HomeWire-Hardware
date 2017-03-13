#include "SensorService.h"

SensorService SensorService::sensorService = SensorService();


SensorService SensorService::getInstance() {
  return sensorService;
}

void SensorService::setupSensor() {
#if def(TEMPERATURE)
  dht.begin();
#elif def(SOILMOISTURE)
  pinMode(MOISTURE_PIN, INPUT);
  analogWrite(MOISTURE_PIN, 0);
#endif

#if def(REACTIVE)
  attachInterrupt(digitalPinToInterrupt(REACTIVE_PIN), onReactiveChange, CHANGE);
#endif
}

int SensorService::getReading(sensor_data *buffer) {

#if def(TEMPERATURE)
  sensor_data datas[2] = {
      {dht.readTemperature(), "temperature"},
      {dht.readHumidity(),    "humidity"}
  };
  memcpy(buffer, datas, sizeof(datas));
  return 2;

#elif def(SOILMOISTURE)
  sensor_data data[1] = {
    {100 - (analogRead(MOISTURE_PIN) / 10.24), "soilmoisture"}
  };
  memcpy(buffer, data, sizeof(data));
  return 1;

#elif def(MOTION)
  sensor_data data[1] = {
    {digitalRead(MOTION_PIN), "motion"}
  };
  memcpy(buffer, data, sizeof(data));
  return 1;

#else
  return 0;

#endif
}

void SensorService::onReactiveChange() {
  // Only needed to wake up CPU from power down mode
}




