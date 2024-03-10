# MySensorsEthGateway
Simplified sketch to control relays with monostable buttons and HomeAssistant over TCP

On the Internet you can find many examples with MySensors library, I wanted something simple so I can just have a map of button and relay pins and Arduino will do the rest. This skech is designated to work with monostable switches and relays that are lowstate activated.

Tested on Mega 2560 and W5100 ethernet shield

## How to use?
- open ```relay_gw.ino``` file and fill ```entities``` array like ```Entity(CHILD_ID, BUTTON_PIN, RELAY_PIN)```
- update ```entities``` array size
- compile and upload sketch
- add integration in HomeAssistant for MySensors

## Fetaures
Just one, after power outage when Arduino starts it loads previously saved relays states. If you plan to connect devices that consume much energy then it might be worth to activate ```LAZY_START``` in main file
 
### Remarks
You can adjust ```DEBOUNCER_INTERVAL``` according to your needs in ```entity.cpp``` file

In send() function I disabled sending echo messages, for some reason this didn't wanted to work in my configuration and I decided to handle physical button changes explicitly

I removed comments from sketch about static IP, DHCP lease time, LEDs configuration etc. since I wanted to keep this sketch as simple as possible. Those ```#define``` directives you can always find in examples of MySensors library

I changed MAC address - to avoid network issues if you have Arduino with default MAC address (DE:AD:BE:EF:FE:ED) currently in network

### ⚠️IMPORTANT⚠️ ❗❗❗
Be careful when working with electricity