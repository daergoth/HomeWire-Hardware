#include "ActorService.h"

ActorService ActorService::actorService = ActorService();

ActorService ActorService::getInstance() {
  return actorService;
}

void ActorService::setupActor() {
  pinMode(RADIO_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RADIO_INTERRUPT_PIN), onCommandReceived, FALLING);

#if defined(RELAY)
  pinMode(RELAY_PIN, OUTPUT);
#endif
}

float ActorService::getState() {
#if defined(RELAY)
  return !digitalRead(RELAY_PIN);
#else
  return false;
#endif
}


void ActorService::setState(float state) {

#if defined(RELAY)
  digitalWrite(RELAY_PIN, state < 1e-5 ? HIGH : LOW);
#endif

}

void ActorService::onCommandReceived() {
  // Only needed for wake up interrupt
}