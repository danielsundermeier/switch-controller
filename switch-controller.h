#include <SPI.h>
#include <Ethernet.h>
#include <Bounce2.h>
#include <credentials.h>
#include <Switch.h>

#define NUM_BUTTONS 3

// MQTT

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress controllerIp(192, 168, 178, 150);
IPAddress relaisControllerIp(192, 168, 178, 151);
IPAddress mqttServerIp(192, 168, 178, 73);
long lastReconnectAttempt = 0;

EthernetClient ethernetClient;
PubSubClient mqttClient(ethernetClient);

void messageReceived(char* topic, byte* payload, unsigned int length);

// Switches
Switch * switches = new Switch[NUM_BUTTONS];

const uint8_t BUTTON_PINS[NUM_BUTTONS] = { 10, 11, 12 };