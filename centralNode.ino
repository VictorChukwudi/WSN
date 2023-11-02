#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 10
#define LORA_RST_PIN 9
#define LORA_DIO0_PIN 2

void setup() {
  Serial.begin(9600);
  // pinMode(5, OUTPUT);
  while (!Serial);

  Serial.println("LoRa Receiver");
  
  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(5, OUTPUT);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming="";
    // received a packet
    Serial.println("Received packet '");

    // read packet
    while (LoRa.available()) {
      char received=(char)LoRa.read();
      incoming+=received;
    }
    if(incoming){
        Serial.println(incoming);
        digitalWrite(5, HIGH);
        delay(5000);
        digitalWrite(5, LOW);                     
      }
  }
}
