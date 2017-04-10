/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Sketch generator:           http://examples.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   Note: This requires ESP8266 support package:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "885de601445d415e839f780cd76532cb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TANJX";
char pass[] = "zxcvb24680";
int pin1 = 3;
int sensorPin = A0;

SimpleTimer uploadtimer;
SimpleTimer sensortimer;
SimpleTimer reconnecttimmer;

int a = -1;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void uploadTimerEvent()
{
  if(a>200)
  Blynk.virtualWrite(1, a);
}

void sensorTimerEvent()
{
  a = Serial.parseInt();
  Serial.println(a);
  if(a==0) resetFunc();  //call reset
}

void reconnectBlynk() {
  if (!Blynk.connected()) {
    if(Blynk.connect()) {
      BLYNK_LOG("Reconnected");
    } else {
      BLYNK_LOG("Not reconnected");
    }
  }
}

BLYNK_READ(V2)
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(pin1, INPUT);
  pinMode(sensorPin, INPUT);
  uploadtimer.setInterval(1000L, uploadTimerEvent);
  sensortimer.setInterval(1000L, sensorTimerEvent);
  reconnecttimmer.setInterval(10000, reconnectBlynk);
}

void loop()
{
  if (Blynk.connected()) {
    Blynk.run();
  }
  uploadtimer.run();
  sensortimer.run();
  reconnecttimmer.run();
}

