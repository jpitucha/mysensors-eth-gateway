#define MY_GATEWAY_W5100
#define MY_PORT 5003
#define MY_MAC_ADDRESS 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE

#define LAZY_START false
#define LAZY_START_DELAY_MS 250

#include <Ethernet.h>
#include <MySensors.h>
#include "entity.h"

// Entity(CHILD_ID, BUTTON_PIN, RELAY_PIN)

Entity entities[1] = {
  Entity(100, 30, 31)
};

void setup() {
  for (Entity &entity : entities) {
    entity.init();

    if (LAZY_START) {
      delay(LAZY_START_DELAY_MS);
    }
  }
}

void presentation() {
  sendSketchInfo("Relay GW 1", "1.0");
  
  for (Entity &entity : entities) {
    present(entity.getChildId(), S_LIGHT);
  }
}

void loop() {
  for (Entity &entity : entities) {
    entity.updateDebouncer();
    bool buttonState = entity.getButtonState();

    if (buttonState != entity.getLastButtonState() && !buttonState) {
      entity.toggleRelayState();
      send(entity.getMessage(), false);
      digitalWrite(entity.getRelayPin(), !entity.getRelayState()); // My relays are low state activated
      saveState(entity.getChildId(), entity.getRelayState());
    }

    entity.setLastButtonState(buttonState);
  }
}

void receive(const MyMessage &message) {
  if (message.type == V_LIGHT) {
    for (Entity &entity : entities) {
      if (message.sensor == entity.getChildId()) {
        entity.setState(message.getBool());
        digitalWrite(entity.getRelayPin(), !entity.getRelayState()); // My relays are low state activated
        saveState(entity.getChildId(), entity.getRelayState());
      }
    }
  }
}