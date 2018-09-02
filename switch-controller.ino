#include <switch-controller.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Switch-Controller");

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        switches[i].setPin(BUTTON_PINS[i]);
    }
}

void loop()
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        switches[i].check();
    }
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