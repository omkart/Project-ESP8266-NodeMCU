
#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>

#include "FS.h"

#define LED_RED     15
#define LED_GREEN   12
#define LED_BLUE    13

ESP8266WiFiMulti WiFiMulti;

ESP8266WebServer server = ESP8266WebServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);

String html_home;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);

            if(payload[0] == '#') {
                // we get RGB data

                // decode rgb data
                uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);

                analogWrite(LED_RED,    ((rgb >> 16) & 0xFF));
                analogWrite(LED_GREEN,  ((rgb >> 8) & 0xFF));
                analogWrite(LED_BLUE,   ((rgb >> 0) & 0xFF));
            }

            break;
    }

}

void prepareFile(){
  
  Serial.println("Prepare file system");
  SPIFFS.begin();
  
  File file = SPIFFS.open("/home.html", "r");
  if (!file) {
    Serial.println("file open failed");  
  } else{
    Serial.println("file open success");

    html_home = "";
    while (file.available()) {
      //Serial.write(file.read());
      String line = file.readStringUntil('\n');
      html_home += line + "\n";
    }
    file.close();

    Serial.print(html_home);
  }
}

void setup() {
    //Serial.begin(921600);
    Serial.begin(115200);

    //Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_RED, 1);
    digitalWrite(LED_GREEN, 1);
    digitalWrite(LED_BLUE, 1);

    
    prepareFile();

    WiFi.softAP("arduino-er", "12345678");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // start webSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    if(MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    // handle index
    server.on("/", []() {
        // send home.html
        server.send(200, "text/html", html_home);
    });

    server.begin();

    // Add service to MDNS
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);

    digitalWrite(LED_RED, 0);
    digitalWrite(LED_GREEN, 0);
    digitalWrite(LED_BLUE, 0);

    Serial.printf("Server Start\n");

}

void loop() {
    webSocket.loop();
    server.handleClient();
}
