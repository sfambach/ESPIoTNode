#include <WiFiClient.h>

WiFiClient node_server_client;
long node_server_timeout_ms = 20000; 

void node_server_connect(){
    Log.traceln("try to connect to server");
    node_server_client.setTimeout(node_server_timeout_ms);
       
    if( !node_server_client.connect(SERVER_IP, SERVER_PORT) ){
        Log.errorln("Connection to %s:%d not possible", SERVER_IP, SERVER_PORT);
        
    } else {
        Log.traceln("Connected");
        node_server_client.println("HUHU");
    }

}

void node_server_disconnect(){
    
}

void node_server_loop(){

    if(!node_server_client.connected()){
        node_server_connect();
    } else{
        // check for data
        while (node_server_client.available() > 0)
        {
            char c = node_server_client.read();
            Serial.write(c);
        }
   }
}