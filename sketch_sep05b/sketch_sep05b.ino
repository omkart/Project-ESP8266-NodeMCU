#include <ESP8266WiFi.h>

const char* ssid = "hns";
const char* password = "helloworld";

const char* host = "http://localhost";


void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  String url="/NodeMCU/add.php?value=hello";
  WiFiClient client;
  String data="value=hello";
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect("192.168.0.102", 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    
    client.print("GET /NodeMCU/add.php?value=hello HTTP/1.1\r\n");
    client.print("Host:192.168.0.102 \r\n");          
    client.print("Connection: close\r\n");
    client.print("Accept: */*\r\n\r\n");
   
    /*client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);        
*/

 Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}
