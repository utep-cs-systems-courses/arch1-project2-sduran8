#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "stateMachine.h"
#include "switches.h"

void buzzer_init() {
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}
void buzzer_set_period(short cycles) {
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

//For all 4 methods:
//The song is defined as an array and then there are 3 while loops
//The first goes through the song, and the next two slow the tempo enough to make the song listenable.
//Each method plays a different song and flashes the LED's in a different pattern
void original() {
  int i = 0;
  int song[] = {4608,0,0,0,5180,2304,4110,3880,0,3456,0,6158,0,
		4608,1295,970,0,1728,0,1540,1295,0,1540,0,970,
		4608,0,0,1540,0,1728,0,1728,0,1540,1396};
  while(i < sizeof(song)) {
    int f_loop = 0;
    while(f_loop < 10) {
      int s_loop = 0;
      while(s_loop < 30000) {
	s_loop++;
      }
      f_loop++;
    }
    buzzer_set_period(song[i]); //Plays the tune
    if(song[i] != 0) both_on(); //Flashes the LED's
    i++;
  }
  
}
void left_for_dead() {
  int i = 0;
  int song[] = {7040,0,7040,0,7040,0,7040,0,7040,0,7040,0,7040,0,
		7040,0,7040,0,7040,0,7040,4186,2793,0,2637,0,
		7040,0,7040,4186,2793,2637,2489,0,7040,0,7040,2637,2489,
		2217,2489,0,7040,0,7040,2489,2217,7458,2093,0,7040,0,
		7040,0,3135,0,2793,0,7040,0,7040,0,1046,0,3951,0,
		7040,0,7040,0,7040,0,3951};
  while(i < sizeof(song)) {
    int f_loop = 0;
    while(f_loop <11) {
      int s_loop = 0;
      while(s_loop < 30000) {
	s_loop++;
      }
      f_loop++;
    }
    buzzer_set_period(song[i]);
    if(song[i] != 0) state_flip();
    i++;
  }
}
void teen_titans() {
  int i = 0;
  int song[] = {2959,0,0,2959,0,2959,0,2489,0,2349,
		0,0,1975,0,0,1975,0,0,2349,0,0,
                2489,0,2959,0,3520,0,2959,0,0,2959,
		0,2959,0,2489,0,2349};
  while(i < sizeof(song)) {
    int f_loop = 0;
    while(f_loop < 5) {
      int s_loop = 0;
      while(s_loop < 30000) {
	s_loop++;
      }
      f_loop++;
    }
    buzzer_set_period(song[i]);
    if(song[i] != 0) state_advance();
    i++;
  }
}
void test() {
  int i = 0;
  int song[] = {10000,9000,8000,7000,6000,5000,4000,3000,2000,
		1000, 900, 800, 700, 600, 500, 400, 300, 200,
		100};
  while(i < sizeof(song)) {
   int s_loop = 0;
   while(s_loop < 30000) {
     s_loop++;
     dim_setting(); //Changed the dim setting
     update_dim();  //Updates the dim
     led_update();
   }
    buzzer_set_period(song[i]);
    next_state(); //Changes the LED state
    i++;
  }
}
