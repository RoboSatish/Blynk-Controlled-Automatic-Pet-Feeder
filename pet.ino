
#define BLYNK_TEMPLATE_ID "TMPLrKGv1gYp"
#define BLYNK_DEVICE_NAME "Pet Feeder"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial

#define APP_DEBUG
#include "BlynkEdgent.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const long utcOffsetInSeconds = 19800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);
int HH, MM,final_time;
int time_blynk, data;

#define motor D0
BLYNK_WRITE(V0)
{
data = param.asInt();
}
BLYNK_WRITE(V1)
{
time_blynk = param.asInt();
Serial.print(time_blynk);

}
void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
 
  timeClient.begin();
}
void loop() {
  timeClient.update();
  HH = timeClient.getHours();
 
  int hours = HH;    
    if (hours == 0) hours = 12;  // Midnight
    if (hours > 12) hours = hours - 12;

  MM = timeClient.getMinutes();
 
  final_time = 3600*hours + 60*MM;

  if (time_blynk == final_time){
    digitalWrite(motor, LOW);
    delay(3000);
    digitalWrite(motor,HIGH); 
  }
  if (data == 1){
  digitalWrite(motor, HIGH);
  delay(5000);
  digitalWrite(motor,LOW);
  Serial.print("Opening");
}  
  delay(6000);
  BlynkEdgent.run();
}