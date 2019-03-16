/*

  Sujet n°4 de CEL

  Déterminer la valeur d'un condo
  où d'une résistance.

  c'est codé avec le Q...

  Schaaf - Soreil

*/

//---- pins des leds ----
//
#define ledPinV 12
#define ledPinJ 11
#define ledPinR 10


//---- pins des boutons ----
// switch 1
#define I1 9
// pushbutton 1
#define BP1 7

//---- pin de mesure pour le test ----
#define testPin 5

//---- valeurs de référence -----
#define vref 5. // tension de référence 5v
#define resistRef 100000.
#define TIMEOUT 5000000 // timeout de 5s en us


//---- etat des boutons ----
bool buttonState = 0;
bool i1State = 0;


//-------------------------------------------------
// Setup
//
void setup() {

  // initialisation des pins des leds
  pinMode(ledPinV, OUTPUT);
  pinMode(ledPinJ, OUTPUT);
  pinMode(ledPinR, OUTPUT);

  // initialisation des pins des boutons
  pinMode(I1, INPUT);
  pinMode(BP1, INPUT);

  // initialiser le pin de test
  pinMode(testPin, OUTPUT);

  // initialiser la communication série à 9600 baud
  Serial.begin(9600);

}

//------------------------------------------------
// loop
//
void loop() {

  // etat des boutons
  // bouton poussoir
  buttonState = digitalRead(BP1);
  // switch
  i1State = digitalRead(I1);


  //---- test pour déterminer une valeur de résistance
  //
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

      // lecteur de la tension
      int voltageValue = analogRead(A0);

      // Convert the analog reading (which goes from 0 - 1024) to a voltage (0 - 5V):
      float vab = float(voltageValue) * (5.0 / 1024.0);

      // find the resistance value with the voltage extracted before
      float resistValue = (vab * (resistRef + 470.)) / (vref - vab);
      
      Serial.println(String(resistValue)+" Ohms");
    }
  }

  //---- test pour déterminer la valeur du condo
  //
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
