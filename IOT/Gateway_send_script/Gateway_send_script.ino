#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0004A30B001BE174";
const char *appKey = "5af1e02fdbf28bb3ebe0b05603ed0df7";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

const int ledPin = LED_BUILTIN;

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup() {
  // put your setup code here, to run once:
  debugSerial.begin(9600);
  loraSerial.begin(57600);
  
  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
  
  while (!debugSerial) {
    ;
  }
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  debugSerial.println("-- LOOP");

  int ledState = digitalRead(ledPin);
  
  if(ledState == HIGH){
    ttn.sendBytes((byte *)"1", 1);

    Serial.println("LED is ON. Sending signal '1' to TTN.");
  }
  else{
    ttn.sendBytes((byte *)"0", 1);

    Serial.println("LED is OFF. Sending signal '2' to TTN.");
  }


  if(ledState == HIGH){
    digitalWrite(ledPin, LOW);
  }
  else{
    digitalWrite(ledPin, HIGH);
  }

  delay(30000);
}
