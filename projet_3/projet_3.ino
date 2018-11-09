#define BP2 4
#define LED2 5
#define P1 A1
#define R1 A2
#define R2 A0
#define REF A3

#define TMIN 2
#define TMAX 5
const uint16_t p1_step = (TMAX-TIMN)/1024;


// interruption
volatile bool bp1_state = false;

void bp1_check(void){
  bp1_state = true;
}


/*** START ***/

void setup() {
 
  Serial.begin(9600);
  pinMode(LED2,OUTPUT);
  pinMode(BP2,INPUT);
  attachInterrupt(INT1,bp1_check,RISING);
}

void loop() {

  uint16_t vref = analogRead(REF);
  uint16_t vr1 = analogRead(R1);
  uint16_t vr2 = analogRead(R2);
  uint16_t vp1 = analogRead(P1);

  

}
