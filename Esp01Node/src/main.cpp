#include <Arduino.h>
#include <ArduinoLog.h>
/******************************************************************************
* Do some tricks with ESP01 Nodes 
* 
*
* Libs
*
* https://github.com/jandrassy/ArduinoOTA
* https://github.com/hideakitai/MQTTPubSubClient Use Version 0.1.3 this is smaller when your have ota problems
* 
*
* Licence: AGPL3
* Author: S. Fambach
* Website: http://Fambach.net
*******************************************************************************/

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

#include "node_wifi.h"


void setup() {
 
  Serial.begin(SERIAL_BOUD);
  Log.begin   (LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);
  Log.traceln("Start setup");

  Log.traceln("Init WLAN");
  node_wifi_setup();
  
}

void loop() {
  

  node_wifi_loop();

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}