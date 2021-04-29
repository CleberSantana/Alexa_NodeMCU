#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include <Switch.h>
#include <UpnpBroadcastResponder.h>
#include <CallbackFunction.h>
#include <Wire.h>
 
//#ifndef UNIT_TEST
#include <Arduino.h>
//#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
 
 
// prototypes
boolean connectWifi();
 
//on/off callbacks
bool ligartv();
bool desligartv();
bool ligarmudo();
bool desligarmudo();
bool ligaryoutube();
bool desligaryoutube();
bool ligarnetflix();
bool deligarnetflix();
bool ligarhdmi3();
bool desligarhdmi3();
bool ligarpausa();
bool desligarpausa();
bool ligarglobo();
bool desligarglobo();
bool ligarrecord();
bool desligarrecord();
bool ligarband();
bool desligarband();
bool ligarsbt();
bool desligarsbt();
 
// Change this before you flash
const char* ssid = "SSID";
const char* password = "PASSWORD";
 
boolean wifiConnected = false;
 
UpnpBroadcastResponder upnpBroadcastResponder;
 
Switch *tv = NULL;
Switch *mudo = NULL;
Switch *youtube = NULL;
Switch *netflix = NULL;
Switch *hdmi3 = NULL;
Switch *pausa = NULL;
Switch *globo = NULL;
Switch *record = NULL;
Switch *band = NULL;
Switch *sbt = NULL;
 
bool istvon = false;
bool ismudoon = false;
bool isyoutubeon = false;
bool isnetflixon = false;
bool ishdmi3on = false;
bool ispausaon = false;
bool isgloboon = false;
bool isrecordon = false;
bool isbandon = false;
bool issbton = false;
 
// Set Relay Pins
int relayOne = 4;
 
IRsend irsend(relayOne);  // Set the GPIO to be used to sending the message.
 
void setup()
{
 
  irsend.begin();
  Serial.begin(115200);
 
  // Initialize wifi connection
  wifiConnected = connectWifi();
  Serial.print("WiFi Connected");
 
  if (wifiConnected) {
    upnpBroadcastResponder.beginUdpMulticast();
 
 
    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    tv = new Switch("tv", 3301, ligartv, desligartv);
    mudo = new Switch("mudo", 3302, ligarmudo, desligarmudo);
    youtube = new Switch("youtube", 3303, ligaryoutube, desligaryoutube);
    netflix = new Switch("netflix", 3304, ligarnetflix, desligarnetflix);
    hdmi3 = new Switch("hdmi3", 3305, ligarhdmi3, desligarhdmi3);
    pausa = new Switch("pausa", 3306, ligarpausa, desligarpausa);
    globo = new Switch("globo", 3307, ligarglobo, desligarglobo);
    record = new Switch("record", 3308, ligarrecord, desligarrecord);
    band = new Switch("band", 3309, ligarband, desligarband);
    sbt = new Switch("sbt", 3310, ligarsbt, desligarsbt);
   
 
    //Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*tv);
    upnpBroadcastResponder.addDevice(*mudo);
    upnpBroadcastResponder.addDevice(*youtube);
    upnpBroadcastResponder.addDevice(*netflix);
    upnpBroadcastResponder.addDevice(*hdmi3);
    upnpBroadcastResponder.addDevice(*pausa);
    upnpBroadcastResponder.addDevice(*globo);
    upnpBroadcastResponder.addDevice(*record);
    upnpBroadcastResponder.addDevice(*band);
    upnpBroadcastResponder.addDevice(*sbt);

    //Set relay pins to outputs
    pinMode(relayOne, OUTPUT);
 
  }
}
 
void loop()
{
  if (wifiConnected) {
    upnpBroadcastResponder.serverLoop();
    tv->serverLoop();
    mudo->serverLoop();
    youtube->serverLoop();
    netflix->serverLoop();
    hdmi3->serverLoop();
    pausa->serverLoop();
    globo->serverLoop();
    record->serverLoop();
    band->serverLoop();
    sbt->serverLoop();   
  }
}
// ----------  COMMANDS  ----------
bool ligartv() {
  Serial.print("TV ligada");
  irsend.sendSony(0xA90, 12,2);
  istvon = true;
  return istvon;
}

bool desligartv() {
  Serial.print("TV desligada");
  irsend.sendSony(0xA90, 12,2);
  istvon = false;
  return istvon;
}

bool ligarmudo(){
  Serial.print("TV mudo");
  irsend.sendSony(0x290, 12,2);
  ismudoon = true;
  return ismudoon;
}

bool desligarmudo(){
  Serial.print("TV com audio");
  irsend.sendSony(0x290, 12,2);
  ismudoon = false;
  return ismudoon;
}

bool ligaryoutube(){
  Serial.print("Youtube");
  irsend.sendSony(0x7123, 15,2);
  isyoutubeon = true;
  return isyoutubeon;
  ishdmi3on = false;
  isnetflixon = false;
  isgloboon = false;
  isrecordon = false;
  isbandon = false;
  issbton = false;
  return ishdmi3on; 
  return isnetflixon;
  return isgloboon;
  return isrecordon;
  return isbandon;
  return issbton;
}

bool desligaryoutube(){ //COLOCAR CÓDIGO EXIT
  Serial.print("Youtube desligado");
  irsend.sendSony(0xC70, 12, 2);
  isyoutubeon = false;
  return isyoutubeon;
}

bool ligarnetflix(){
  Serial.print("Netflix");
  irsend.sendSony(0x1F58, 15, 2);
  isyoutubeon = false;
  ishdmi3on = false;
  isnetflixon = true;
  return isnetflixon;
  isgloboon = false;
  isrecordon = false;
  isbandon = false;
  issbton = false;
  return isyoutubeon; 
  return ishdmi3on; 
  return isgloboon;
  return isrecordon;
  return isbandon;
  return issbton;
}

bool desligarnetflix(){ 
  Serial.print("Netflix desligado");
  irsend.sendSony(0xC70, 12,2);
  delay(500);
  irsend.sendSony(0xCD0, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isnetflixon = false;
  return isnetflixon;
}

bool ligarhdmi3(){
  Serial.print("HDMI3 ligado");
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isyoutubeon = false;
  ishdmi3on = true;
  return ishdmi3on; 
  isnetflixon = false;
  isgloboon = false;
  isrecordon = false;
  isbandon = false;
  issbton = false;
  return isyoutubeon; 
  return isnetflixon;
  return isgloboon;
  return isrecordon;
  return isbandon;
  return issbton;
}

bool desligarhdmi3(){
  Serial.print("HDMI3 ligado");
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA50, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  ishdmi3on = false;
  return ishdmi3on;
}

bool ligarpausa(){
  Serial.print("pausa ligado");
  irsend.sendSony(0x4CE9, 15,2);
  ispausaon = true;
  return ispausaon;
}

bool desligarpausa(){
  Serial.print("play ligado");
  irsend.sendSony(0x2CE9, 15,2);
  ispausaon = false;
  return ispausaon;
}

bool ligarglobo(){
  Serial.print("globo ligado");
  irsend.sendSony(0x10, 12,2);
  delay(100);
  irsend.sendSony(0x810, 12,2);
  delay(100);
  irsend.sendSony(0x5CE9, 15,2);
  delay(100);
  irsend.sendSony(0x10, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isyoutubeon = false;
  ishdmi3on = false;
  isnetflixon = false;
  isgloboon = true;
  return isgloboon;
  isrecordon = false;
  isbandon = false;
  issbton = false;
  return isyoutubeon; 
  return ishdmi3on; 
  return isnetflixon;
  return isrecordon;
  return isbandon;
  return issbton;
}

bool desligarglobo(){
  Serial.print("globo ligado");
  isgloboon = false;
  return isgloboon;
}

bool ligarrecord(){
  Serial.print("record ligado");
  irsend.sendSony(0x610, 12,2);
  delay(100);
  irsend.sendSony(0x5CE9 , 15,2);
  delay(100);
  irsend.sendSony(0x10, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isyoutubeon = false;
  ishdmi3on = false;
  isnetflixon = false;
  isgloboon = false;
  isrecordon = true;
  return isrecordon;
  isbandon = false;
  issbton = false;
  return isyoutubeon; 
  return ishdmi3on; 
  return isnetflixon;
  return isgloboon;
  return isbandon;
  return issbton;
}

bool desligarrecord(){
  Serial.print("record ligado");
  isrecordon = false;
  return isrecordon;
}

bool ligarband(){
  Serial.print("band ligado");
  irsend.sendSony(0x810, 12,2);
  delay(100);
  irsend.sendSony(0x5CE9 , 15,2);
  delay(100);
  irsend.sendSony(0x10, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isyoutubeon = false;
  ishdmi3on = false;
  isnetflixon = false;
  isgloboon = false;
  isrecordon = false;
  isbandon = true;
  return isbandon;
  issbton = false;
  return isyoutubeon; 
  return ishdmi3on; 
  return isnetflixon;
  return isgloboon;
  return isrecordon;
  return issbton;
}

bool desligarband(){
  Serial.print("band desligado");
  isbandon = false;
  return isbandon;
}

bool ligarsbt(){
  Serial.print("sbt ligado");
    irsend.sendSony(0xC10, 12,2);
  delay(100);
  irsend.sendSony(0x5CE9 , 15,2);
  delay(100);
  irsend.sendSony(0x10, 12,2);
  delay(100);
  irsend.sendSony(0xA70, 12,2);
  isyoutubeon = false;
  ishdmi3on = false;
  isnetflixon = false;
  isgloboon = false;
  isrecordon = false;
  isbandon = false;
  issbton = true;
  return issbton;
  return isyoutubeon; 
  return ishdmi3on; 
  return isnetflixon;
  return isgloboon;
  return isrecordon;
  return isbandon;

}

bool desligarsbt(){
  Serial.print("sbt desligado");
  issbton = false;
  return issbton;
}
 
// connect to wifi – returns true if successful or false if not
  boolean connectWifi() {
  boolean state = true;
  int i = 0;
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
 
  // Wait for connection
  // Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }
 
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
 
  return state;
}
