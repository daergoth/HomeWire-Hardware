#ifndef HOMEWIRE_ARDUINO_NETWORKSERVICE_H
#define HOMEWIRE_ARDUINO_NETWORKSERVICE_H

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Mesh.h>
#include <EEPROM.h>
#include "LoggingConfig.h"

#define NETWORK_CHANNEL_NUM 108

#define RF24_CE_PIN 7
#define RF24_CS_PIN 8

class NetworkService {

public:
    void setupNetwork(uint8_t h_id);

    bool send(uint8_t msg_type, const void *data, size_t size, uint8_t nodeID = 0);

    void update();

    static NetworkService getInstance();

private:
    NetworkService() = default;

    static RF24 radio;
    static RF24Network network;
    static RF24Mesh mesh;
    static NetworkService networkService;
};

#endif //HOMEWIRE_ARDUINO_NETWORKSERVICE_H
