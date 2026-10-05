// Date:11/12/2025

// I wrote a long time ago but i was so lazyyyyyyyyy to post it........ <3 <3
// I wrote this code for learn how to control home appliances remotely
// Using simple and cheap components as possible
// There will be 4 channels for controlling diffirent devices 
// The range doesn't really matter as long as the esp32 can connect to your home Wifi
// You can uprade this code for me ........
// Thanks for reading <3 <3 <3


#define BLYNK_TEMPLATE_ID "..."                                                //
#define BLYNK_TEMPLATE_NAME "..."                                              // Put your blynk ID to here
#define BLYNK_AUTH_TOKEN "..."                                                 //
                                                                               
#include <WiFi.h>                                                              //
#include <BlynkSimpleEsp32.h>                                                  //    
                              
                                                                               
char ssid[] = "...";                                                           //  Put your Wifi here
char pass[] = "...";                                                           //  Put your Password here


#define RELAY1 4                                                               //       GPIO 4
#define RELAY2 5                                                               //       GPIO 5         you can exchange your GPIO you want here
#define RELAY3 6                                                               //       GPIO 6
#define RELAY4 7                                                               //       GPIO 7 
#define RELAY_ON  HIGH                                                         //
#define RELAY_OFF LOW                                                          //



BlynkTimer timer;                                                              //
BLYNK_WRITE(V4)                                                                //
{                                                                              //
  digitalWrite(RELAY1, param.asInt() ? RELAY_ON : RELAY_OFF);                  //
}                                                                              //
BLYNK_WRITE(V5)                                                                //
{                                                                              //
  digitalWrite(RELAY2, param.asInt() ? RELAY_ON : RELAY_OFF);                  //
}                                                                              //
BLYNK_WRITE(V6)                                                                //
{                                                                              //
  digitalWrite(RELAY3, param.asInt() ? RELAY_ON : RELAY_OFF);                  //
}                                                                              //
BLYNK_WRITE(V7)                                                                //
{                                                                              //
  digitalWrite(RELAY4, param.asInt() ? RELAY_ON : RELAY_OFF);                  //
}                                                                              //




BLYNK_CONNECTED()                                                              // sync state
{                                                                              //
  Blynk.syncVirtual(V4);                                                       //
  Blynk.syncVirtual(V5);                                                       //
  Blynk.syncVirtual(V6);                                                       //
  Blynk.syncVirtual(V7);                                                       //
}                                                                              //

void checkConnection()                                                         // recheck connection
{                                                                              //
  if (WiFi.status() != WL_CONNECTED)                                           //
  {                                                                            //
    WiFi.reconnect();                                                          //
    return;                                                                    //
  }                                                                            //
  if (!Blynk.connected())                                                      //
  {                                                                            //
    Blynk.connect();                                                           //
  }                                                                            //
}                                                                              //
                                                                               


void setup()                                                                   //   
{                                                                              //
  pinMode(RELAY1, OUTPUT);                                                     //
  pinMode(RELAY2, OUTPUT);                                                     //
  pinMode(RELAY3, OUTPUT);                                                     //
  pinMode(RELAY4, OUTPUT);                                                     //                                                               
  digitalWrite(RELAY1, RELAY_OFF);                                             //
  digitalWrite(RELAY2, RELAY_OFF);                                             //
  digitalWrite(RELAY3, RELAY_OFF);                                             //
  digitalWrite(RELAY4, RELAY_OFF);                                             //
  WiFi.mode(WIFI_STA);                                                         // WiFi
  WiFi.setSleep(false);                                                        // boost WiFi
  WiFi.setAutoReconnect(true);                                                 // auto reconnect
  WiFi.persistent(false);                                                      //
  WiFi.setTxPower(WIFI_POWER_8_5dBm);                                          // Set Wifi Power 8.5 dBm       
  WiFi.begin(ssid, pass);                                                      //



  while (WiFi.status() != WL_CONNECTED)                                        //
  {                                                                            //                                                                    
    delay(100);                                                                //
  }                                                                            //
                                                                               // connect to Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);                                              //
                                                                               //
  while (!Blynk.connect())                                                     //
  {                                                                            //
    delay(100);                                                                //
  }                                                                            //
                                                                               // recheck connection after 5 secs
  timer.setInterval(5000L, checkConnection);                                   //
}                                                                              //
                                                                               //
void loop()                                                                    //
{                                                                              //
  Blynk.run();                                                                 //
  timer.run();                                                                 //
}                                                                              //