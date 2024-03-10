#include "entity.h"

#define DEBOUNCER_INTERVAL 50
#define RELAY_ON 1
#define RELAY_OFF 0

Entity::Entity(byte childId, byte buttonPin, byte relayPin) {
    _childId = childId;
    _buttonPin = buttonPin;
    _relayPin = relayPin;
    _relayState = false;
    _lastButtonState = false;
    _debouncer = Bounce();
    _msg = MyMessage(childId, V_LIGHT);
}

void Entity::init() {
    pinMode(_buttonPin, INPUT_PULLUP);

    _debouncer.attach(_buttonPin);
    _debouncer.interval(DEBOUNCER_INTERVAL);

    digitalWrite(_relayPin, RELAY_OFF);
    pinMode(_relayPin, OUTPUT);

    _relayState = loadState(_childId);
    digitalWrite(_relayPin, !_relayState);
};

void Entity::updateDebouncer() {
    _debouncer.update();
};

void Entity::toggleRelayState() {
    _relayState = !_relayState;
    _msg.set(_relayState);
}

byte Entity::getChildId() {
    return _childId;
};

byte Entity::getRelayPin() {
    return _relayPin;
}

bool Entity::getRelayState() {
    return _relayState;
}

bool Entity::getLastButtonState() {
    return _lastButtonState;
}

bool Entity::getButtonState() {
    return _debouncer.read();
};

MyMessage& Entity::getMessage() {
    return _msg;
}

void Entity::setState(bool state) {
    _relayState = state;
}

void Entity::setLastButtonState(bool state) {
    _lastButtonState = state;
}