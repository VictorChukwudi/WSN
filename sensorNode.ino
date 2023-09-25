// #include <SPI.h>
// #include <LoRa.h>

// #define LORA_SS_PIN 10
// #define LORA_RST_PIN 9
// #define LORA_DIO0_PIN 2
// int MQPIN=A0;

// void setup() {
//   // put your setup code here, to run once:
//    Serial.begin(9600);
//   while (!Serial);

//   Serial.println("LoRa Sender");

//     LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
//   if (!LoRa.begin(433E6)) {
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
 
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   int value=analogRead(MQPIN);
//     Serial.println(value);
//   if(value>200){
//       LoRa.beginPacket();
// LoRa.print(value);
// LoRa.endPacket();
// Serial.println("Value Sent.");
//   }
// // Serial.println(value);
// delay(1000);
// }





















































#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 10
#define LORA_RST_PIN 9
#define LORA_DIO0_PIN 2
int MQPIN = A0;
unsigned long lastTransmissionTime = 0;
unsigned long transmissionInterval = 10000;  // Interval between transmissions in milliseconds

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int value = analogRead(MQPIN);
  Serial.println(value);

  if (value >= 150 && millis() - lastTransmissionTime >= transmissionInterval) {
    LoRa.beginPacket();
    LoRa.print(value);
    LoRa.endPacket(); // This will transmit the data immediately without waiting for LoRa.endPacket()
    
    Serial.println("Value Sent.");
    lastTransmissionTime = millis();
  }

  delay(1500);  // A small delay to prevent rapid looping
}
