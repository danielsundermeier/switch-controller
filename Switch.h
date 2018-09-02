#ifndef Switch_h
#define Switch_h

#include "Arduino.h"
#include "Bounce2.h"

#define DC_GAP 250
#define HOLDTIME 2000
#define LONGHOLDTIME 5000

#define EVENT_CLICK 1
#define EVENT_DOUBLECLICK 2
#define EVENT_HOLD 3
#define EVENT_LONGHOLD 4

class Switch
{
    public:
        const int BOUNCER_INTERVAL = 25;
        Switch();
        Switch(uint8_t pin);
        void check();
        void setPin(uint8_t pin);
    private:
        uint8_t _pin;
        Bounce _bouncer;
        boolean DCwaiting = false; // whether we're waiting for a double click (down)
        boolean DConUp = false; // whether to register a double click on next release, or whether to wait and click
        boolean singleOK = true; // whether it's OK to do a single click
        long downTime = -1; // time the button was pressed down
        long upTime = -1; // time the button was released
        boolean ignoreUp = false; // whether to ignore the button release because the click+hold was triggered
        boolean waitForUp = false; // when held, whether to wait for the up event
        boolean holdEventPast = false; // whether or not the hold event happened already
        boolean longHoldEventPast = false;// whether or not the long hold event happened already
        int getEvent();
        void click();
        void doubleClick();
        void hold();
        void longHold();
};

#endif