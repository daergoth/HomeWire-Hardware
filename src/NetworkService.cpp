#include "NetworkService.h"

NetworkService NetworkService::networkService = NetworkService();
RF24 NetworkService::radio = RF24(RF24_CE_PIN, RF24_CS_PIN);
RF24Network NetworkService::network = RF24Network(radio);
RF24Mesh NetworkService::mesh = RF24Mesh(radio, network);

void NetworkService::setupNetwork(uint8_t h_id) {
    logln("Starting Mesh setup...");
    mesh.setNodeID(h_id);
    mesh.setChild(false);
    logln("Initializing Mesh...");
    mesh.begin(NETWORK_CHANNEL_NUM, RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.printDetails();
}

bool NetworkService::send(uint8_t msg_type, const void *data, size_t size, uint8_t nodeID) {
    if (!mesh.checkConnection()) {
        mesh.renewAddress();
    }

    if (mesh.write(data, msg_type, size, nodeID)) {
//        logln("Successful write!");
        delay(10);
        mesh.releaseAddress();
        return true;
    } else {
        logln("Write failure!");

        if (!mesh.checkConnection()) {
            logln("Renewing Address");
            mesh.renewAddress();
        } else {
            logln("Send fail, Test OK");
        }
        return false;
    }
}

NetworkService NetworkService::getInstance() {
    return networkService;
}

void NetworkService::update() {
    mesh.update();
}