#include <switch-controller.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Start Switch-Controller");

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons[i].attach( BUTTON_PINS[i], INPUT_PULLUP );
        buttons[i].interval(25);

        DCwaiting[i] = false;
        DConUp[i] = false;
        singleOK[i] = true;
        downTime[i] = false;
        upTime[i] = -1;
        ignoreUp[i] = false;
        waitForUp[i] = false;
        holdEventPast[i] = false;
        longHoldEventPast[i] = false;
    }
}

void loop()
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        checkButton(i);
    }
}

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
    switch (getEvent(buttonNr)) {
        case EVENT_CLICK: clickEvent(buttonNr); break;
        case EVENT_DOUBLECLICK: doubleClickEvent(buttonNr); break;
        case EVENT_HOLD: holdEvent(buttonNr); break;
        case EVENT_LONGHOLD: longHoldEvent(buttonNr); break;
    }
}

int getEvent(int buttonNr)
{
    int event = 0;
    buttons[buttonNr].update();
    int buttonVal = buttons[buttonNr].read();
    if (buttons[buttonNr].fell())
    {
        downTime[buttonNr] = millis();
        ignoreUp[buttonNr] = false;
        waitForUp[buttonNr] = false;
        singleOK[buttonNr] = true;
        holdEventPast[buttonNr] = false;
        longHoldEventPast[buttonNr] = false;
        if ((millis()-upTime[buttonNr]) < DC_GAP && DConUp[buttonNr] == false && DCwaiting[buttonNr] == true)
        {
            DConUp[buttonNr] = true;
        }
        else
        {
            DConUp[buttonNr] = false;
        }
        DCwaiting[buttonNr] = false;
    }
    else if(buttons[buttonNr].rose())
    {
        if (not ignoreUp[buttonNr])
        {
            upTime[buttonNr] = millis();
            if (DConUp[buttonNr] == false)
            {
                DCwaiting[buttonNr] = true;
            }
            else
            {
                event = EVENT_DOUBLECLICK;
                DConUp[buttonNr] = false;
                DCwaiting[buttonNr] = false;
                singleOK[buttonNr] = false;
            }
        }
    }

    if (buttonVal == HIGH && (millis()-upTime[buttonNr]) >= DC_GAP && DCwaiting[buttonNr] == true && DConUp[buttonNr] == false && singleOK[buttonNr] == true)
    {
        event = EVENT_CLICK;
        DCwaiting[buttonNr] = false;
    }

    if (buttonVal == LOW && (millis() - downTime[buttonNr]) >= HOLDTIME)
    {
        // Trigger "normal" hold
        if (not holdEventPast[buttonNr])
        {
            event = EVENT_HOLD;
            waitForUp[buttonNr] = true;
            ignoreUp[buttonNr] = true;
            DConUp[buttonNr] = false;
            DCwaiting[buttonNr] = false;
            //downTime[buttonNr] = millis();
            holdEventPast[buttonNr] = true;
        }
        // Trigger "long" hold
        if ((millis() - downTime[buttonNr]) >= LONGHOLDTIME)
        {
            if (not longHoldEventPast[buttonNr]) {
                event = EVENT_LONGHOLD;
                longHoldEventPast[buttonNr] = true;
            }
        }
    }

    return event;

}