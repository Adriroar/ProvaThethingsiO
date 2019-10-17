#include <YunClient.h>
#include <Bridge.h>
#include <PubSubClient.h>
#include <Process.h>

#define TOKEN "lURZi1TESc4McQbr6pizAI60t-GfSyPIa-JuEiLsy1Y"

YunClient wificlient;

String topic = "v2/things/" + String(TOKEN);
String message = "";
boolean firstValue = true;


void addValue(String key, int value) {
  if (firstValue == true) {
    firstValue = false;
    message.concat("{\"key\":\"" + key + "\",\"value\":\"" + value+"\"}");
  }
  else {
    message.concat(",{\"key\":\"" + key + "\",\"value\":\"" + value+"\"}");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
    String text = "";
    for (int i = 0; i < length; i++)
        text.concat((char)payload[i]);
    text.replace(" ", "");
    Serial.println(text);
}

PubSubClient mqtt("mqtt.thethings.io", 1883, callback, wificlient);

void publish() {
  String toSend = "{\"values\":[" + message + "]}";
  mqtt.publish((char*)topic.c_str(), (char*)toSend.c_str());
  message= "";
  firstValue = true;
  Serial.println("Published");
}

int seconds = 0;
String key = "A0";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Bridge.begin();
  while (!mqtt.connect("Yunclient"))
    Serial.println("Could not subscribe, retrying...");
  
  Serial.println("Client connected to mqtt broker!");
  mqtt.subscribe((char*)topic.c_str());
}

void loop() {
  /*Process wifiCheck;
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }

  Serial.println();

  delay(000);*/
  
  // put your main code here, to run repeatedly:
  while (analogRead(A0) != 0){
    Serial.println("Pulsado");
    seconds++;
    delay(1000);
  }
  if(seconds != 0){
    Serial.println("Se ha dejado de pulsar");
    addValue(key,seconds);
    publish();
    /*Serial.print("Key: ");
    Serial.print(key);
    Serial.print(", ");
    Serial.print("seconds: ");
    Serial.println(seconds);*/
    seconds = 0;
  }
  mqtt.loop();
}
