/* projet 2 CEL S4 enib
 * 
 * Créer plusieurs signaux carrés déphasés
 * codé avec le Q.
 *
 * Hugo Schaaf
 * Enib S4-2018
 * license : GPL2
 */


/* standard headers */
#include <math.h>

/* homemade headers */
#include "voltagep2.hpp"

/* buttons */
#define BP1 11
#define BP2 12
int buttonState1 = 0;
int prev_buttonState1 = 0;
int buttonState2 = 0;
int prev_buttonState2 = 0;

/* leds */
#define ledPinV 10
#define ledPinJ 9
#define ledPinR 8
int ledStateV = LOW;
int ledStateJ = LOW;
int ledStateR = LOW;

/* voltages */
#define V1 5
#define V2 6
#define V3 7

/* period in ms */
#define INCREASE_T_STEP 5000 // milliseconds
#define DECREASE_T_STEP 10000 // milliseconds
#define TMIN 20000
#define TMAX 40000
uint32_t period = 30000;// 30ms period by default

// phase in rad
#define PMIN 125
#define PMAX 375
#define PHASE_NO_MIN 0
#define PHASE_NO_MAX 2
#define P_COUNT 3
uint32_t phase_tab[P_COUNT] = {PMIN, 250, PMAX};
uint32_t phase = PMIN;
uint8_t phase_no = 0;

bool increment_bp1 = true;
bool increment_bp2 = true;

// voltages structures
cel::voltage v1 = cel::createVoltage(V1, period);
cel::voltage v2 = cel::createVoltage(V2, period);
cel::voltage v3 = cel::createVoltage(V3, period);

// make the delayMicroseconds longer and precise
void longDelayMicroseconds(uint32_t us){
  for(uint32_t i = 0; i < (us/10); i++) delayMicroseconds(10);
}

/***********************/
/*        START        */
/***********************/

void setup() {
  pinMode(ledPinV, OUTPUT);
  pinMode(ledPinJ, OUTPUT);
  pinMode(ledPinR, OUTPUT);

  pinMode(BP1, INPUT);
  pinMode(BP2, INPUT);

  pinMode(V1, OUTPUT);
  pinMode(V2, OUTPUT);
  pinMode(V3, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  static bool first_start = true;
  
  // new period T set and new phase P set flags
  static bool newT = true;
  static bool newP = true;
  // previous loop buttons states values
  static uint32_t prev_time_bp1 = 0;
  static uint32_t prev_time_bp2 = 0;

  // read the buttons
  buttonState1 = digitalRead(BP1);
  buttonState2 = digitalRead(BP2);

  // get the date of this turn of the loop
  uint32_t c_time = micros();
    
  /* ~~~~~~~~~~~~~~~~~~~~~~ */

  // no double push
  if(buttonState1 && buttonState2){
    buttonState1 = false;
    buttonState2 = false;
  }

  /*** Set the period ***/
  
  // if it's the first time the button is push
  if(buttonState2 && !prev_buttonState2){
    prev_buttonState2 = buttonState2;
    prev_time_bp2 = c_time;
  }
  // if it's not the first push or if the button hasn't been pushed
  //else prev_buttonState2 = buttonState2;
  if(buttonState2){  
    // increase every 800ms
    if(period<TMAX && increment_bp2){
      if(c_time-prev_time_bp2 >= 800000){
        period += INCREASE_T_STEP;
        prev_time_bp2 = c_time;
        newT = true;
      }
    }
    else increment_bp2 = false;
    // decrease 
    if(period>TMIN && !increment_bp2){
      if(c_time-prev_time_bp2 >= 1000000){
        period -= DECREASE_T_STEP;
        prev_time_bp2 = c_time;
        newT= true;
      }
    }
    else increment_bp2 = true;
  }
  else{
    prev_buttonState2 = buttonState2;//reset the buttonState1
    newT = false;
  }
  /*** end set the period ***/


  /* ~~~~~~~~~~~~~~~~~~~~~~ */


  /*** Set the phase ***/
  
  // if it's the first time the button is push
  if(buttonState1 && !prev_buttonState1){
    prev_buttonState1 = buttonState1;
    prev_time_bp1 = c_time;
  }
  if(buttonState1){  

    // every 800ms
    if(c_time-prev_time_bp1 >= 800000){
    // increase
      if(phase_no<PHASE_NO_MAX && increment_bp1){
          phase_no++;
          phase = phase_tab[phase_no];
          prev_time_bp1 = c_time;
          newP = true;
      }
      else increment_bp1 = false;
    // decrease 
      if(phase_no>PHASE_NO_MIN && !increment_bp1){
        phase_no--;
        phase = phase_tab[phase_no];
        prev_time_bp1 = c_time;
        newP = true;
      }
      else increment_bp1 = true;
    }
    else newP = false;
  }
  else{
    prev_buttonState1 = buttonState1;//reset the buttonState1
    newP = false;
  }
  /*** end set the phase***/

  /* ~~~~~~~~~~~~~~~~~~~~~~ */

  /*** switch leds ***/
   
  if(phase == PMIN){
      ledStateV = HIGH;
      ledStateJ = LOW;
      ledStateR = LOW;
  }
  else if(phase == 250){
      ledStateV = LOW;
      ledStateJ = HIGH;
      ledStateR = LOW;
  }
    
  else if(phase == PMAX){
      ledStateV = LOW;
      ledStateJ = LOW;
      ledStateR = HIGH;
  }
  else{
      ledStateV = HIGH;
      ledStateJ = LOW;
      ledStateR = HIGH;
  }

  /* ~~~~~~~~~~~~~~~~~~~~~~ */

  /*** drive the outputs ***/

  // leds
  digitalWrite(ledPinV, ledStateV);
  digitalWrite(ledPinJ, ledStateJ);
  digitalWrite(ledPinR, ledStateR);


  uint32_t phase_us = (uint32_t)((period/1000)*phase);

  if(newT){
    newT = false;
    cel::setPeriod(v1, period);
    cel::setPeriod(v2, period);
    cel::setPeriod(v3, period);
  }

  // if the phase has been updated, delay and adapt current time to keep the phase
  if(newP || first_start){
    newP = false;

    // reset start time
    cel::setTstart(v3, c_time);
    cel::setTstart(v1, c_time+phase_us);
    cel::setTstart(v2, c_time+2*phase_us);
    // v3 is running in advance to v1 and v2 is running late to v1
    cel::generateSig(v3, c_time);
    //longDelayMicroseconds(phase_us);
    if(phase < PMAX){
      delayMicroseconds(phase_us);
    }
    else{
      delay(phase_us/1000);
    }
    cel::generateSig(v1, c_time+phase_us);
    //longDelayMicroseconds(phase_us);
    if(phase < PMAX){
      longDelayMicroseconds(phase_us);
    }
    else{
      delay(phase_us/1000);
    }
    cel::generateSig(v2, c_time+2*phase_us);
  }
  // if phase is unchanged don't delay
  else{
    // v3 is running in advance to v1 and v2 is running late to v1
    cel::generateSig(v3, c_time);
    cel::generateSig(v1, c_time);
    cel::generateSig(v2, c_time);
  }

  if(first_start) first_start = false;
}
