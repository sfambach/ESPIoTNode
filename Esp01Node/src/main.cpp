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
#include "node_wifi.h"
#include "node_server.h"



#ifdef VM_DEBUG_GDB
#include "GDBStub.h"
#endif

void setup() {
 #ifdef VM_DEBUG_GDB
  gdbstub_init();
  // Add/extend the below delay if you want to debug the setup code
  // delay(3000);
  #endif


  Serial.begin(SERIAL_BOUD);
  Log.begin   (LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);
  Log.traceln(F("Start setup"));

  Log.traceln(F("Init WLAN"));
  node_wifi_setup(WLAN_SSID, WLAN_PASSWORD);
  
  Log.traceln(F("WLAN initialized, "));
  
}

void loop() {
  node_wifi_loop();
  if(node_wifi_is_connected()){
    node_server_loop();
  }

}

