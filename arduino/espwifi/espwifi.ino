//Stuff to modify out of the gate
//WiFi.hostByName("your_mqtt.server.co.uk", MQTT_SERVER_IP);

//---------------------------------------------------------------------------


#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include "DHTesp.h"               //this lib includes the wire reading, bit banged




#define D0   16     //WAKE  =>  16
#define D1    5     //IOS   =>  5
#define D2    4     //=>  4
#define D3    0     //=>  0
#define D4    2     //=>  2
#define D5   14     //CLK   =>  14
#define D6   12     //MISO  =>  12
#define D7   13     //MOSI  =>  13
#define D8   15     //CS    =>  15
#define D9    3     //RX    =>  3
#define D17  17     //pin for dht sensor


#define DHTTYPE         DHT22

#define DHTDATAPIN      D2                        //Orange Wire
#define OneWireBus_Pin  D1                        //Yellow Wire
#define MQTT_VERSION    MQTT_VERSION_3_1_1
const PROGMEM uint16_t  MQTT_SERVER_PORT          = 1883;
const PROGMEM char*     MQTT_SERVER_ID            = "some.mqtt.broker.somewhere.com";
const PROGMEM char*     MQTT_CLIENT_ID            = "espSense";
const PROGMEM char*     MQTT_USER                 = "jon";
const PROGMEM char*     MQTT_PASSWORD             = "jon";
const char*             MQTT_HUMIDITY_TOPIC       = "sensor/house/humid";
const char*             MQTT_TEMPERATURE_TOPIC    = "sensor/house/temp";

const PROGMEM char*     WIFI_SSID                 = "Guest";
const PROGMEM char*     WIFI_PASS                 = "Guest";

boolean                 fDebug                    = true;
float                   temp                      = 0.0;
float                   hum                       = 0.0;
int                     sleepTimeS                = 900000000;

//what pin is the DHT residing on?
DHTesp dht;

WiFiClient espClient;
PubSubClient client(espClient);
IPAddress MQTT_SERVER_IP;


//---------------------------------------------------------------------------
void ConfigHardware(){

  //serial setup if in debug mode
    if ( fDebug == true ) {
      Serial.begin(115200);
      Serial.println();
    }

  //dht sensor setup
    dht.setup(D17, DHTesp::DHT22); 
  
  //blocking for sensor startup
    if ( fDebug == true ) {
      Serial.println("Calibrating Sensor");
      for( int x = 0; x < 5; x++){
        Serial.print(".");
        delay(1000);
      }
      Serial.println();
    }

  //set MQQT route (?)
    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
}

//---------------------------------------------------------------------------
//print out debug info based on passed in string value and debug flag.
void Debugger(char strMessage, char strValue) {
  if ( strValue == NULL ) {
    if ( fDebug == true ) {Serial.println(strMessage);}
  }else{
    if ( fDebug == true ) {
      Serial.print(strMessage);
      Serial.println(strValue);
    }
  }
}

//---------------------------------------------------------------------------
void reconnect() {
// Loop until we're reconnected
  while (!client.connected()) {
    if ( fDebug == true ) {Serial.print("INFO: Attempting MQTT connection...");}
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      if ( fDebug == true ) {Serial.println("INFO: connected");}
    } else {
      if ( fDebug == true ) {
        Serial.print("ERROR: failed, rc=");
        Serial.print(client.state());
        Serial.println("DEBUG: try again in 5 seconds");
        delay(5000);
      }
    }
  }
}

//---------------------------------------------------------------------------
void setup() {

//turn on the sensor
  ConfigHardware();

//get an object to interact with wifi
WiFiManager wifiManager;

//(where does this function resolve to?)

  wifi_station_set_hostname(WIFI_SSID);

//debug settings for wifi based on the debug flag
  if ( fDebug == true ) {
    wifiManager.setDebugOutput(true);
  }else{
    wifiManager.setDebugOutput(false);
  }

//not jm  //reset settings - for testing
//not jm  //wifiManager.resetSettings();

//force and auto-reconnect?
  if (!wifiManager.autoConnect(WIFI_SSID)) {
    delay(3000);
    ESP.reset();
  }

//not sure where WiFi object is coming from?
  WiFi.hostByName(MQTT_SERVER_ID, MQTT_SERVER_IP);

//debug -- does client.setServer belong inside this block?
  if ( fDebug == true ) {
    Serial.print("MQTT_SERVER_IP: ");
    Serial.println(MQTT_SERVER_IP);
    client.setServer(MQTT_SERVER_IP , MQTT_SERVER_PORT);
  }

//connect if not already
  if (!client.connected()) {
    reconnect();
  }

//grab some data from the sensor - is this properly handled or a memory leak?
//float temp = dht.readTemperature();
//float hum = dht.readHumidity();
temp = dht.getTemperature();
hum = dht.getHumidity();

//serial it out if fDebug
  if ( fDebug == true ) {
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.println();
  }

  //publish it on the bus
  client.publish(MQTT_TEMPERATURE_TOPIC, String(temp).c_str(), true);
  client.publish(MQTT_HUMIDITY_TOPIC, String(hum).c_str(), true);

/*
  float waterTemp = getTemp();
  if ( fDebug == true ) {
    Serial.print("DBS180 Temp: ");
    Serial.println(waterTemp);
  }
  client.publish(MQTT_AQUARIUM_TOPIC,String(waterTemp).c_str(), true);
  delay(1000);
  client.loop();

  if ( fDebug == true ) {Serial.println("Entering deepSleep for 15 minutes");}
*/

//deepSleep is not helpful for initial setup
//ESP.deepSleep(sleepTimeS);

}


//---------------------------------------------------------------------------
/*

//sensor read and convert code. 
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];
  byte i;
  byte present = 0;
  byte type_s;
  float celsius, fahrenheit;

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      if ( fDebug == true ) {Serial.println("No sensors found");}
      ds.reset_search();
      delay(250);
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      if ( fDebug == true ) {Serial.println("CRC is not valid!");}
      return -1000;
  }

  switch (addr[0]) {
    case 0x10:
      if ( fDebug == true ) {Serial.println("  Chip = DS18S20");}  // or old DS1820}
      type_s = 1;
      break;
    case 0x28:
      if ( fDebug == true ) {Serial.println("  Chip = DS18B20");}
      type_s = 0;
      break;
    case 0x22:
      if ( fDebug == true ) {Serial.println("  Chip = DS1822");}
      type_s = 0;
      break;
    default:
      if ( fDebug == true ) {Serial.println("Device is not a DS18x20 family device.");}
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad
  if ( fDebug == true ) {
    Serial.print("  Data = ");
    Serial.print(present, HEX);
    Serial.println(" ");
  }
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  if ( fDebug == true ) {
    Serial.print(" CRC=");
    Serial.print(OneWire::crc8(data, 8), HEX);
    Serial.println();
  }
 int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //byte MSB = data[1];
  //byte LSB = data[0];

  //float tempRead = ((MSB << 8) | LSB); //using two's compliment
  //float TemperatureSum = tempRead / 16;
  //
  return (celsius);

}
*/

void loop() {
//this is in the main event loop, for interactive debugging etc.

//grab some data from the sensor
    temp = dht.getTemperature();
    hum = dht.getHumidity();
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.println();
    delay(2500);



//No code in here as we are putting the ESP into deepsleep and waking every 15 minutes
  //so we save power and can run off of battery if needs be
}
