#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "switches.h"
#include "led.h"
#include "stateMachine.h"

char switch_state_down, switch_state_changed, val_1, val_2, val_3, val_4;


static char
switch_update_interrupt_sense() {
  char p1val = P2IN;
  P2IES |= (p1val & SWITCHES);
  P2IES &= (p1val | ~SWITCHES);
  return p1val;
}

void
switch_init() {
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  switch_interrupt_handler();
}

void
switch_interrupt_handler() {
  char p1val = switch_update_interrupt_sense();

  //Identifies if each button is pressed
  val_1 = (p1val & SW1) ? 0 : 1;
  val_2 = (p1val & SW2) ? 0 : 1;
  val_3 = (p1val & SW3) ? 0 : 1;
  val_4 = (p1val & SW4) ? 0 : 1;
  
  //Depending on which button is pressed (or not pressed), a certain song will play and pattern will occur
  if(val_1) {
    switch_state_down = val_1;
    switch_state_changed = 1;
    original();
  }
  
  else if(val_2) {
    switch_state_down = val_2;
    switch_state_changed = 1;
    left_for_dead();
  }
  
  else if(val_3) {
    switch_state_down = val_3;
    switch_state_changed = 1;
    teen_titans();
  }
  
  else if(val_4) {
    switch_state_down = val_4;
    switch_state_changed = 1;
    r_on();
    r_on();
    test();
  }
  else {
    switch_state_down = 0;
    switch_state_changed = 1;
    buzzer_set_period(0);
  }
 }
