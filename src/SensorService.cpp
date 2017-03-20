#include "SensorService.h"

SensorService SensorService::sensorService = SensorService();


SensorService SensorService::getInstance() {
  return sensorService;
}

void SensorService::setupSensor() {
#if defined(TEMPERATURE)
  dht.begin();
#elif defined(SOILMOISTURE)
  pinMode(MOISTURE_PIN, INPUT);
  analogWrite(MOISTURE_PIN, 0);
#elif defined(MOTION)
  pinMode(MOTION_PIN, INPUT);
#endif

#if defined(REACTIVE)
  attachInterrupt(digitalPinToInterrupt(REACTIVE_PIN), onReactiveChange, CHANGE);
#endif
}

int SensorService::getReading(device_data *buffer) {

#if defined(TEMPERATURE)
  device_data datas[2] = {
      {dht.readTemperature(), "temperature"},
      {dht.readHumidity(),    "humidity"}
  };
  memcpy(buffer, datas, sizeof(datas));
  return 2;

#elif defined(SOILMOISTURE)
  device_data data[1] = {
    {100 - (analogRead(MOISTURE_PIN) / 10.24), "soilmoisture"}
  };
  memcpy(buffer, data, sizeof(data));
  return 1;

#elif defined(MOTION)
  device_data data[1] = {
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




