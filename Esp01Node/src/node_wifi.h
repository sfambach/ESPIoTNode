#ifndef NODE_WIFI_H
#define NODE_WIFI_H
#include <ArduinoLog.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>




#elif defined(ESP32)


#endif
WiFiEventHandler handler;
void onStaConnect(const WiFiEventStationModeConnected & con){
    Log.traceln("WiFi connected to SSID %s", con.ssid);
}

void node_wifi_setup(){
    
    WiFi.setHostname(HOST_NAME_PREFIX);
    Log.trace("Connect to SSID: %s ",WLAN_SSID );
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Log.trace(".");
    }

    Log.traceln("connected %s", WiFi.localIP().toString().c_str());

    handler = WiFi.onStationModeConnected(&onStaConnect);

}


void node_wifi_loop(){
    

}




#endif // NODE_WIFI_H
