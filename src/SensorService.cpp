#include "SensorService.h"
#include "LoggingConfig.h"

SensorService SensorService::sensorService = SensorService();


SensorService SensorService::getInstance() {
  return sensorService;
}

void SensorService::setupSensor() {
#if TEMPERATURE
  dht.begin();
#elif MOTION

#endif
}

int SensorService::getReading(sensor_data *buffer) {

#if TEMPERATURE
  sensor_data datas[2] = {
      {dht.readTemperature(), "temperature"},
      {dht.readHumidity(), "humidity"}
  };
  memcpy(buffer, datas, sizeof(datas));
  return 2;
#elif MOTION



#endif
}



