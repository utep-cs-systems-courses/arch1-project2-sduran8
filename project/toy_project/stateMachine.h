#ifndef stateMachine_included
#define stateMachine_included

extern unsigned char red_on, green_on, led_changed;


char toggle_red();
char toggle_green();
void r_on();
void both_on();

void state_advance(); //Pattern : OFF->Green_ON->Both_ON->Red_ON->OFF
void state_flip();    //Pattern : Green_ON->Red_ON

//Dim
void next_state();
void dim_setting();
void update_dim();

#endif // included
