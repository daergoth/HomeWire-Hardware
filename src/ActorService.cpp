#include "ActorService.h"

ActorService ActorService::actorService = ActorService();

ActorService ActorService::getInstance() {
  return actorService;
}

void ActorService::setupActor() {
  pinMode(RADIO_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RADIO_INTERRUPT_PIN), onCommandReceived, CHANGE);

#if defined(RELAY)
  pinMode(RELAY_PIN, OUTPUT);
#endif
}

void ActorService::setState(bool state) {

#if defined(RELAY)
  digitalWrite(RELAY_PIN, state ? LOW : HIGH);
#endif

}

void ActorService::onCommandReceived() {
  // Only needed for wake up interrupt
}
