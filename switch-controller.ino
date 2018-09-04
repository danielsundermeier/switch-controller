#include <switch-controller.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Switch-Controller");

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        switches[i].setPin(BUTTON_PINS[i]);
    }

    mqttClient.setServer(MQTT_SERVER, 1883);
    mqttClient.setCallback(messageReceived);

    Ethernet.begin(mac, controllerIp);
    delay(1500);
    Serial.println(Ethernet.localIP());

}

void loop()
{
    if (! mqttClient.connected())
    {
        reconnect();
    }
    mqttClient.loop();

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        switches[i].check();
    }
}

boolean reconnect() {
    if (mqttClient.connect("switch-controller-1", MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("MQTT verbunden");
    }
    return mqttClient.connected();
}

void messageReceived(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

/*
void clickEvent(int buttonNr)
{
    Serial.println("Button " + String(BUTTON_PINS[buttonNr]) + " clickEvent");
}

void doubleClickEvent(int buttonNr)
{
    Serial.println("Button " + String(BUTTON_PINS[buttonNr]) + " doubleClickEvent");
}

void holdEvent(int buttonNr)
{
    Serial.println("Button " + String(BUTTON_PINS[buttonNr]) + " holdEvent");
}

void longHoldEvent(int buttonNr)
{
    Serial.println("Button " + String(BUTTON_PINS[buttonNr]) + " longHoldEvent");
}

void checkButton(int buttonNr)
{
    switch (switches[buttonNr].getEvent()) {
        case EVENT_CLICK: clickEvent(buttonNr); break;
        case EVENT_DOUBLECLICK: doubleClickEvent(buttonNr); break;
        case EVENT_HOLD: holdEvent(buttonNr); break;
        case EVENT_LONGHOLD: longHoldEvent(buttonNr); break;
    }
}
*/