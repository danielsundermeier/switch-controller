#include <Switch.h>

Switch::Switch() {}

Switch::Switch(uint8_t pin)
{
    setPin(pin);
}

void Switch::setPin(uint8_t pin)
{
    _bouncer = Bounce();
    _bouncer.attach(pin, INPUT_PULLUP);
    _bouncer.interval(BOUNCER_INTERVAL);

    _pin = pin;
}

int Switch::getEvent()
{
    int event = 0;
    _bouncer.update();
    int buttonVal = _bouncer.read();
    if (_bouncer.fell())
    {
        downTime = millis();
        ignoreUp = false;
        waitForUp = false;
        singleOK = true;
        holdEventPast = false;
        longHoldEventPast = false;
        if ((millis()-upTime) < DC_GAP && DConUp == false && DCwaiting == true)
        {
            DConUp = true;
        }
        else
        {
            DConUp = false;
        }
        DCwaiting = false;
    }
    else if(_bouncer.rose())
    {
        if (not ignoreUp)
        {
            upTime = millis();
            if (DConUp == false)
            {
                DCwaiting = true;
            }
            else
            {
                event = EVENT_DOUBLECLICK;
                DConUp = false;
                DCwaiting = false;
                singleOK = false;
            }
        }
    }

    if (buttonVal == HIGH && (millis()-upTime) >= DC_GAP && DCwaiting == true && DConUp == false && singleOK == true)
    {
        event = EVENT_CLICK;
        DCwaiting = false;
    }

    if (buttonVal == LOW && (millis() - downTime) >= HOLDTIME)
    {
        // Trigger "normal" hold
        if (not holdEventPast)
        {
            event = EVENT_HOLD;
            waitForUp = true;
            ignoreUp = true;
            DConUp = false;
            DCwaiting = false;
            //downTime = millis();
            holdEventPast = true;
        }
        // Trigger "long" hold
        if ((millis() - downTime) >= LONGHOLDTIME)
        {
            if (not longHoldEventPast) {
                event = EVENT_LONGHOLD;
                longHoldEventPast = true;
            }
        }
    }

    return event;
}

void Switch::check()
{
    switch (getEvent()) {
        case EVENT_CLICK: click(); break;
        case EVENT_DOUBLECLICK: doubleClick(); break;
        case EVENT_HOLD: hold(); break;
        case EVENT_LONGHOLD: longHold(); break;
    }
}

void Switch::click()
{
    Serial.println("Button " + String(_pin) + " clickEvent");
}

void Switch::doubleClick()
{
    Serial.println("Button " + String(_pin) + " doubleClickEvent");
}

void Switch::hold()
{
    Serial.println("Button " + String(_pin) + " holdEvent");
}

void Switch::longHold()
{
    Serial.println("Button " + String(_pin) + " longHoldEvent");
}