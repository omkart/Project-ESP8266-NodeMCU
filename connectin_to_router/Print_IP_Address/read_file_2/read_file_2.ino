#include "FS.h"

void prepareFile(){
  
  Serial.println("Prepare file system");
  SPIFFS.begin();
  
  File file = SPIFFS.open("/test.txt", "r");
  if (!file) {
    Serial.println("file open failed!");  
  } else{
    Serial.println("file open success:)");

    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("To read separate file in file system");
  prepareFile();
}

void loop() {
  // put your main code here, to run repeatedly:

}
