#include <Bounce2.h>
#include <Switch.h>

#define NUM_BUTTONS 3

Switch * switches = new Switch[NUM_BUTTONS];

const uint8_t BUTTON_PINS[NUM_BUTTONS] = { 10, 11, 12 };