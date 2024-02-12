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
  String textData = "";
  
  if(ledState == HIGH){
    
    textData = "LED is ON. Sending signal '1' to TTN.";
    ttn.sendBytes(const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(textData.c_str())), textData.length());

    Serial.println(textData);

    delay(5000);
    digitalWrite(ledPin, LOW);
  }
  else{

    textData = "LED is OFF. Sending signal '2' to TTN.";
    ttn.sendBytes(const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(textData.c_str())), textData.length());

    Serial.println(textData);
    
    delay(5000);
    digitalWrite(ledPin, HIGH);
  }


  delay(30000);
}
