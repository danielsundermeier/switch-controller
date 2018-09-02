#include <Bounce2.h>

#define DC_GAP 250
#define HOLDTIME 2000
#define LONGHOLDTIME 5000

#define EVENT_CLICK 1
#define EVENT_DOUBLECLICK 2
#define EVENT_HOLD 3
#define EVENT_LONGHOLD 4

#define NUM_BUTTONS 3

boolean DCwaiting[NUM_BUTTONS]; // whether we're waiting for a double click (down)
boolean DConUp[NUM_BUTTONS]; // whether to register a double click on next release, or whether to wait and click
boolean singleOK[NUM_BUTTONS]; // whether it's OK to do a single click
long downTime[NUM_BUTTONS]; // time the button was pressed down
long upTime[NUM_BUTTONS]; // time the button was released
boolean ignoreUp[NUM_BUTTONS]; // whether to ignore the button release because the click+hold was triggered
boolean waitForUp[NUM_BUTTONS]; // when held, whether to wait for the up event
boolean holdEventPast[NUM_BUTTONS]; // whether or not the hold event happened already
boolean longHoldEventPast[NUM_BUTTONS];// whether or not the long hold event happened already

Bounce * buttons = new Bounce[NUM_BUTTONS];

const uint8_t BUTTON_PINS[NUM_BUTTONS] = { 10, 11, 12 };