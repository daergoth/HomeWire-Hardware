#include "NetworkService.h"
#include "ActorService.h"

NetworkService NetworkService::networkService = NetworkService();
RF24 NetworkService::radio = RF24(RF24_CE_PIN, RF24_CS_PIN);
RF24Network NetworkService::network = RF24Network(radio);
RF24Mesh NetworkService::mesh = RF24Mesh(radio, network);

void NetworkService::setupNetwork(uint8_t h_id) {
    debugLogln("Starting Mesh setup...");
    mesh.setNodeID(h_id);
    mesh.setChild(false);
    debugLogln("Initializing Mesh...");
    mesh.begin(NETWORK_CHANNEL_NUM, RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.maskIRQ(false, false, true);
    radio.printDetails();
}

bool NetworkService::send(uint8_t msg_type, const void *data, size_t size, uint8_t nodeID) {
    if (!mesh.checkConnection()) {
        mesh.renewAddress();
    }

    if (mesh.write(data, msg_type, size, nodeID)) {
        delay(10);
        mesh.releaseAddress();
        return true;
    } else {
        debugLogln("Write failure!");

        if (!mesh.checkConnection()) {
            debugLogln("Renewing Address");
            mesh.renewAddress();
        } else {
            debugLogln("Send fail, Test OK");
        }
        return false;
    }
}

uint8_t NetworkService::read(void *data) {
    if (!mesh.checkConnection()) {
        mesh.renewAddress();
    }

    uint8_t dataCount = 0;

    while(network.available()) {
        RF24NetworkHeader header;
        network.peek(header);

        switch(header.type) {
            case 'A': {
                actor_command dat;

                network.read(header,&dat,sizeof(dat));

                printf("Rcv actor command: target state:%d \n", dat.targetState);

                memcpy(data + dataCount * sizeof(actor_command), &dat, sizeof(dat));

                dataCount++;
                }
            break;

            default:
                network.read(header,0,0);
                printf("Rcv bad type\n");
            break;
        }

    }

    return dataCount;
}

NetworkService NetworkService::getInstance() {
    return networkService;
}

void NetworkService::update() {
    mesh.update();
}
