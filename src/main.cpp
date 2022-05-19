#include "debouncer.h"
static bool init_ok = false;

#define BUTTON_1 33
#define BUTTON_2 34
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  uint8_t pins[] = {BUTTON_1, BUTTON_2};
  if(debouncer_init(pins, sizeof(pins)) == DEBOUNCER_ERROR_OK)
  {
    init_ok = true;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(init_ok)
  {
    static uint8_t prev_state = HIGH;
    debouncer_update();
    uint8_t state = debouncer_get_state(BUTTON_1);
    if(state != prev_state)
    {
      prev_state = state;
      Serial.printf("State of Button1: %d", state);
    }
  }
}