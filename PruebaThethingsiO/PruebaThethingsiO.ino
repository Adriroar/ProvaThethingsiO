#include <SPI.h>
#include <Ethernet.h>
#include <thethingsiO.h>
#include <thethingsiOEthernet.h>

#define TOKEN "lURZi1TESc4McQbr6pizAI60t-GfSyPIa-JuEiLsy1Y"

thethingsiOEthernet thing(TOKEN);

void startEthernet() {
    Serial.println("Connecting Arduino to network...");

    // Local Network Settings
    byte mac[] = { 0xE0, 0xDB, 0x55, 0xA1, 0x46, 0x41 }; // Must be unique on local network

    // Connect to network amd obtain an IP address using DHCP
    while (Ethernet.begin(mac) == 0)
        Serial.println("DHCP Failed, retrying");
    Serial.println("Arduino connected to network using DHCP");
}

int sensorValue = 0;
int value = 0;
String key = "A0";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startEthernet();
}

void loop() {
  Ethernet.maintain();
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);
  if (sensorValue != 0){
    value++;
    thing.addValue(key,value);
    thing.send();
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(", ");
    Serial.print("Value: ");
    Serial.println(value);
    delay(1000);
  }
}
