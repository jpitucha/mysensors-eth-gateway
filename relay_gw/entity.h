#ifndef ENTITY_H
#define ENTITY_H

#include <Arduino.h>
#include <core/MySensorsCore.h>
#include <Bounce2.h>

class Entity {
    public:
        Entity(byte childId, byte buttonPin, byte relayPin);
        void init();
        void updateDebouncer();
        void toggleRelayState();
        byte getChildId();
        byte getRelayPin();
        bool getRelayState();
        bool getLastButtonState();
        bool getButtonState();
        MyMessage& getMessage();
        void setState(bool state);
        void setLastButtonState(bool state);
        
    private:
        byte _childId;
        byte _buttonPin;
        byte _relayPin;
        bool _relayState;
        bool _lastButtonState;
        Bounce _debouncer;
        MyMessage _msg;
};

#endif