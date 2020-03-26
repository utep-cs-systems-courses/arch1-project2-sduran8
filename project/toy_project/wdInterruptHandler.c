#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT() {
  static char count = 0;
  if (++count == 200) {
    count = 0;
  }
}
