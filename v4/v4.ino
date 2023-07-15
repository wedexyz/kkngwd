
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#include <FirebaseESP8266.h>
#endif

#define pinrlA 16
#define pinrlB 14
#define pinrlC 12
//efine pinrlD 33

int x   = 0;
#define WIFI_SSID "wifiku"
#define WIFI_PASSWORD "widhiwinata"
#define FIREBASE_HOST "megaboth007.firebaseio.com"
#define FIREBASE_AUTH "DDa47UHXoI0Tn8icpA686fj0OCjOR3SiN16DWjfIS"
FirebaseData fbdo;

void setup()
{
  pinMode(pinrlA, OUTPUT);
  pinMode(pinrlB, OUTPUT);
  pinMode(pinrlC, OUTPUT);
  digitalWrite(pinrlA, 1);
  digitalWrite(pinrlB, 1);
  digitalWrite(pinrlC, 1);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop()
{
  int x = analogRead(A0);
  Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/test/int"), x) ? "ok" : fbdo.errorReason().c_str());
  if(Firebase.getString(fbdo, "/relay1"))
  {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(pinrlA, fbdo.stringData().toInt());
  }else{
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }

  if(Firebase.getString(fbdo, "/relay2"))
  {
    Serial.print("Get int data B success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(pinrlB, fbdo.stringData().toInt());
  }else{
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }

  if(Firebase.getString(fbdo, "/relay3"))
  {
    Serial.print("Get int data C success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(pinrlC, fbdo.stringData().toInt());
  }else{
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
  if (x<20){
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay1"), 1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay2"), 1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay3"), 1) ? "ok" : fbdo.errorReason().c_str());
    //digitalWrite(pinrlA,HIGH);digitalWrite(pinrlB,HIGH);digitalWrite(pinrlA,HIGH);
    }
  else {
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay1"), 0) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay2"), 0) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("/relay3"), 0) ? "ok" : fbdo.errorReason().c_str());
    //digitalWrite(pinrlA,LOW);digitalWrite(pinrlB,LOW);digitalWrite(pinrlA,LOW);
    }
}
/*
void loop() {

int x = analogRead(A0);
Serial.println(x);
if (x<20){digitalWrite(pinrlA,HIGH);digitalWrite(pinrlB,LOW);digitalWrite(pinrlA,LOW);}
if (x<15){digitalWrite(pinrlB,HIGH);digitalWrite(pinrlA,LOW);digitalWrite(pinrlC,LOW);}
if (x<6) {digitalWrite(pinrlC,HIGH);digitalWrite(pinrlA,LOW);digitalWrite(pinrlB,LOW);}
}
*/
