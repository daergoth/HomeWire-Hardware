#ifndef HOMEWIRE_HARDWARE_ACTORSERVICE_H
#define HOMEWIRE_HARDWARE_ACTORSERVICE_H

#include "Arduino.h"

#define RADIO_INTERRUPT_PIN 3

// RELAY
#define RELAY_PIN 2

struct actor_command {
    uint8_t targetState;
};

class ActorService {
public:
    static ActorService getInstance();

    void setupActor();

    bool getState();

    void setState(bool state);

private:
    static ActorService actorService;

    ActorService() = default;

    static void onCommandReceived();

};

#endif //HOMEWIRE_HARDWARE_ACTORSERVICE_H
