#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "0004A30B001BE174";
const char *appKey = "5af1e02fdbf28bb3ebe0b05603ed0df7";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

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
}

void loop() {
  // put your main code here, to run repeatedly:

}
