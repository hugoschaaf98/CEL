/*

  Sujet n°4 de CEL

  Schaaf - Soreil

*/

#define ledPinV 12
#define ledPinJ 11
#define ledPinR 10

#define I1 9

#define BP1 7

#define testPin 5
#define vref 5. // reference voltage 5v
#define resistRef 100000.

#define TIMEOUT 5000000 // 5s timeout in us

bool buttonState = 0;
bool i1State = 0;

void setup() {

  // initialize LEDs as outputs:
  pinMode(ledPinV, OUTPUT);
  pinMode(ledPinJ, OUTPUT);
  pinMode(ledPinR, OUTPUT);

  // initialize SWITCHes as inputs:
  pinMode(I1, INPUT);

  // intialize the pushbutton pin as an input:
  pinMode(BP1, INPUT);

  // initialize test pin
  pinMode(testPin, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

void loop() {
  buttonState = digitalRead(BP1);
  i1State = digitalRead(I1);



  if (i1State == 1)
  {
    digitalWrite(testPin, HIGH);
    digitalWrite(ledPinJ, HIGH);
    digitalWrite(ledPinV, LOW);
    if (buttonState == HIGH)
    {

      digitalWrite(ledPinR, HIGH);
      delay(1000);
      digitalWrite(ledPinR, LOW);

      Serial.println("Test resistance");

      // read the input on analog pin 0:
      int voltageValue = analogRead(A0);

      // Convert the analog reading (which goes from 0 - 1024) to a voltage (0 - 5V):
      float vab = float(voltageValue) * (5.0 / 1024.0);

      // find the resistance value with the voltage extracted before
      float resistValue = (vab * (resistRef + 470.)) / (vref - vab);
      
      Serial.println(String(resistValue)+" Ohms");
    }


  }
  if (i1State == 0)
  {
    digitalWrite(testPin, LOW);
    digitalWrite(ledPinV, HIGH);
    digitalWrite(ledPinJ, LOW);
    if (buttonState == HIGH)
    {
      digitalWrite(ledPinR, HIGH);
      delay(1000);
      digitalWrite(ledPinR, LOW);

      Serial.println("Test condo");
      delay(2000);
      digitalWrite(testPin, HIGH);

      uint32_t startTime = micros();
      uint32_t dt = startTime;
      bool timeOver = false;

      while (analogRead(A0) <= 1014) {
        if (micros() - startTime >= TIMEOUT) {
          timeOver = true;
          break;
        }
      }
      dt = micros() - startTime;
      
      float condoValue = float(dt) / (5. * resistRef);

      if (!timeOver) Serial.println(String(condoValue)+" uF");
      else Serial.println("Aucun composant present");

    }

  }

}
