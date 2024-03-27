#ifndef NODE_WIFI_H
#define NODE_WIFI_H
#include <ArduinoLog.h>

#ifdef ESP8266

#include <ESP8266WiFi.h>
WiFiEventHandler connectHandler;
WiFiEventHandler gotIPHandler;
WiFiEventHandler scanCompleted;

void on_station_connect(const WiFiEventStationModeConnected & ev){
    Log.traceln("WiFi connected to SSID %s ", ev.ssid);
}

void on_station_got_ip(const WiFiEventStationModeGotIP& ev){
    Log.traceln("Got IP %s", ev.ip.toString().c_str());
}




#elif defined(ESP32)
#include<WiFi.h>

#endif


/*******************************************************************************/

static long wifi_scan_time_ms = WIFI_SCAN_TIME; // Every Second
static long wifi_scan_time_ts_ms = 0; // Every Second
static bool wifi_scan_initial = true;

char* scan_print_format = "%3d | %18s | %30s | %2d ";
char buffer[100];
bool wifi_auto_scan = true;
bool wifi_scan_print_enable = false;
String node_wifi_host_name;

void wifi_scan_auto(bool b){
    wifi_auto_scan = b;
}

void wifi_scan_print(){
    
    sprintf(buffer,"%3s | %18s | %30s | %2s ", "#", "MAC", "SSID", "dB"  );
    Log.traceln(buffer);
    Log.traceln(F("----------------------------------------------------------------"));

    if(WiFi.scanComplete() < 1){
        Log.traceln(F("no scan result"));
        return;
    }
    
    for(int i = 0; i < WiFi.scanComplete(); i++){
        sprintf(buffer, scan_print_format,i+1, WiFi.BSSIDstr(i).c_str(), WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        Serial.println(buffer);
    }

    Log.traceln(F("----------------------------------------------------------------"));
}

/** 
 * If scan is completed use the gained information
*/
void on_scan_completed(int count){
    if(wifi_auto_scan && wifi_scan_print_enable){
        wifi_scan_print();
    }
}



/**
 *  scan network, uses  timer to not scan to often 
 */
void node_wifi_scan_network(){
    //Log.traceln ("wifi scan: called");
    // check timer
    long current_millis = millis();
    if((wifi_scan_time_ts_ms + wifi_scan_time_ms) < current_millis || wifi_scan_initial){

        Log.traceln ("wifi scan: timer is over");
        if(WiFi.scanComplete() !=  WIFI_SCAN_RUNNING){
            Log.traceln ("wifi scan: Init new");
            WiFi.scanNetworksAsync(&on_scan_completed);
            wifi_scan_time_ts_ms = current_millis;
        }
        wifi_scan_initial = false;
   }
}




/*******************************************************************************/

void node_wifi_setup(char* ssid, char* password){


    
    
#ifdef ESP8266
    connectHandler = WiFi.onStationModeConnected(&on_station_connect);
    gotIPHandler = WiFi.onStationModeGotIP(&on_station_got_ip);
#endif

    Log.trace("Connect to SSID: %s ",ssid );
    
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Log.trace(".");
    }

    String mac = WiFi.macAddress(); 
    mac.replace(":","-");
    node_wifi_host_name = String(HOST_NAME_PREFIX) + mac;
    WiFi.setHostname(node_wifi_host_name.c_str());
    Log.trace("Set host name  %s ", WiFi.getHostname());
    

    

}


void node_wifi_loop(){
    node_wifi_scan_network();
}


bool node_wifi_is_connected(){
    return ( WiFi.status() == WL_CONNECTED );
}


#endif // NODE_WIFI_H
