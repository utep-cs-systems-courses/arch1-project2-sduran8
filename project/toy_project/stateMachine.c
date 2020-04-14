#include <msp430.h>
#include "stateMachine.h"
#include "led.h"

//Dim
extern enum {off=0, dim=1, bright=2} led_mode=0;
extern char count = 0;

//Toggles Red LED, ON if OFF, OFF if ON
char toggle_red() {
  static char state = 1;
  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;
}
//Toggles Green LED, ON if Red is OFF, OFF if Red is ON
char toggle_green() {
  if (red_on) {
    green_on = 0;
  }
  else green_on = 1;
  return 1;
}
//Turns on the Red LED
void r_on() {
  char changed = 0;
  changed = toggle_red(); 
  led_changed = changed;
  led_update();
}
//Turns on the Red & Green LED
void both_on() {
  char changed = 0;
  toggle_green_a();
  changed = toggle_red();
  led_changed = changed;
  led_update();
}
//Advances the LED's to the next state
void state_advance() {
  char changed = 0;
  static enum {R=0, G=1} color = R;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  led_changed = changed;
  led_update();
}
//Advances the LED's to the next state
void state_flip() {
  char changed = 0;
  static enum {R=1, G=1} color = R;
  changed = toggle_red(); color = G; 
  changed = toggle_green_a(); color = R;
  led_changed = changed;
  led_update();
}




//Dim  
void next_state() {
  led_mode = (led_mode + 1) % 3; //moves the state to its next state (off-->bright-->dim-->off)
}

void dim_setting() {
  count = (count + 1) & 3; //controls whether dim occurs in state dim (0 is TRUE 1,2,3... FALSE)
}

//Depending on led_mode & count, will change the dim setting of the Red LED
void update_dim() {
 static unsigned char new_red;
  switch (led_mode) {
  case off:
    new_red = 0; break;
  case dim:
    new_red = (count < 1); break;
  case bright:
    new_red = 1; break;
  }
  if (red_on != new_red) {
    red_on = new_red;
    led_changed = 1;
  }
}
