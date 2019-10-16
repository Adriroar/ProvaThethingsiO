#include <SPI.h>
#include <Ethernet.h>
#include <thethingsiO.h>
#include <thethingsiOEthernet.h>

#define TOKEN "lURZi1TESc4McQbr6pizAI60t-GfSyPIa-JuEiLsy1Y"

thethingsiOEthernet thing(TOKEN);

void startEthernet() {
    Serial.println("Connecting Arduino to network...");

    // Local Network Settings
    byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Must be unique on local network

    // Connect to network amd obtain an IP address using DHCP
    //while (Ethernet.begin(mac) == 0)
        Serial.println("DHCP Failed, retrying");
    Serial.println("Arduino connected to network using DHCP");
}

int sensorValue = 0;
int seconds = 0;
String key = "A0";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startEthernet();
}

void loop() {
  Ethernet.maintain();
  // put your main code here, to run repeatedly:
  while (analogRead(A0) != 0){
    Serial.println("Pulsado");
    seconds++;
    delay(1000);
  }
  if(seconds != 0){
    Serial.println("Se ha dejado de pulsar");
    thing.addValue(key,seconds);
    thing.send();
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(", ");
    Serial.print("seconds: ");
    Serial.println(seconds);
    seconds = 0;
  }
}
