/*
 * catapult for my docs
 * dedicated to my dad
 * 
 * Long story short : my dad suffers from a movement limiting illness.
 * The day I learnt about my dad's illness I made a green house.
 * Two days later I lost my job as a DevOps. 
 * Then I got a new job without even applying. 
 * 
 * So this is dedicated to my friends, my colleagues and my dad.
 *
 * I promise that will have the schematics for this project.
 * 
 * Requirements : 
 * - Arduino UNO, Mega or Nano.
 * - 5V 2A USB transformer or equivalent
 * - 2 servos with high torque, above 4 kgs
 * - two arcade buttons
 * - one button with led included (those are awesome)
 * - LCD with serial backpack or equivalent
 * 
 * If you find this code useful, have a nice cold beer on me.
 * If you find some errors, please point them to <jci@codemonkey.cl>
 * 
 */


#include <Servo.h>

// enum helpouts, i am an old fuck
enum machinestate
{
INITIAL,
ARMING,
ARMINGW,
ARMED,
ARMEDW,
DISARMING,
DISARMINGW,
DISARMED,
SHOOT,
ABORT
};

enum ledstate 
{
  LEDOFF,
  LEDBLINK,
  LEDON
};

enum lcdstate
{
  LCDPRINT,
  LCDOFF
};


// pinout definition for buttons

const int buttonARM=2;
const int buttonSHOOT=3;
const int buttonDISARM=4; // fuck, I have to overcome this :(

/* why the <sadface.jpg>?
  Before going into this project, I just barely made a funcioning prototype for rhis module, but
  never ever read about the arduino limitations. After watching a youtube video, one guy said that UNO/Nano have
  only two interrupt pins. That freaking sucks, so I have to read all the time the voltage level of pin 4 to disarm
  the catapult. Freaking sucks. :(

  by the way, the youtube channel is https://www.youtube.com/channel/UCxqx59koIGfGRRGeEm5qzjQ (educat8s.tv).
  Nice one if you're newb to ardus and stuff
*/

// pinout definition for all servos
const int servoARM = A1;
const int servoLOCK = A2;

// pinout definition for LCD
const int lcdSDA = 8;
const int lcdSCL = 9;

// pinout definition for button led
volatile boolean ledD = false;
const int ledDISARM = 13;
int ledVALUE =0;

// global variables
machinestate thismachinestate;
ledstate thisledstate;
lcdstate thislcdstate;
char * thislcdstring;

void setstate(machinestate state)
{
  if (transition(state))
    thismachinestate = state;
}

bool transition(machinestate state)
{

  // if possible, return true 
  // else, return false

  if (thismachinestate == ABORT) 
    return false;
    
  if (thismachinestate == INITIAL && state == ARMING)
        return true;

  if (thismachinestate == ARMING && state == ARMED)
    return true;

  if (thismachinestate == ARMED && state == ARMED) 
    return true;

  if (thismachinestate == ARMED && state == DISARMING)
    return true;

  if (thismachinestate == DISARMING && state == DISARMED)
    return true;

  if (thismachinestate == DISARMED && state == ARMING)
    return true;
 
  // failsafe
 
  return false; 
}


void setlcdmessage()
{
  // set the LCD message with the current status
  switch(thismachinestate)
  {
    case ARMING:
      thislcdstring = "ARMING";
      break;
    case ARMED:
      thislcdstring = "ARMED";
      break;
    case DISARMING:
      thislcdstring = "DISARMING";
      break;
    case SHOOT:
      thislcdstring = "SHOOTING";
      break;
    default:
      thislcdstring = "I HAVE NO IDEA WHAT I AM DOING";
      break;
  }
}


void setledstate()
{
  if (thismachinestate == ARMED)
  {
    // call the fixed led method  
  }
  if (thismachinestate == ARMING)
  {
    // call the blinking method
  }
}



void setservostate()
{
  
}

void setup() {
  // put your setup code here, to run once:

  thismachinestate == INITIAL;
  thisledstate == LEDOFF;
  thislcdstring = "Booting...";
  setlcdmessage();

  // attach all servos
  // set all servos to position 0
  // start the LCD 
  // print booting message

  // attach all button interrupts
  attachInterrupt(0, transition, ARMING);
  attachInterrupt(1, transition, SHOOT);
  // attachInterrupt();


  // finish printing the boot message
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (thismachinestate != ABORT)
  {
      setlcdmessage();
      setledstate();
      setservostate();
  }
  
}
