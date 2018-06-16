#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "hns";
const char* password = "helloworld";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
     Serial.print(".");
    delay(1000);
    
  }
  Serial.println("Connected !");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    float dd = analogRead(A0);
    String val = String(dd,6);
    http.begin("http://192.168.1.101/arduino/test2.php?name="+val);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
    Serial.println("Completed updating the database");
 
    http.end();   //Close connection
 
  }
 
  delay(30000);    //Send a request every 30 seconds
 
}
