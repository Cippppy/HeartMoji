#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Esp.h>

// Replace your wifi credentials here
// ssid: your wifi name
// password: your wifi password
// if your wifi does not have a password, you can use just the ssid
const char* ssid     = "";
const char* password = "";

unsigned long timer;
boolean isItConnected = false;
unsigned char powerMode = 1;
volatile bool intFired = false;
boolean registered = true;


// Replace with your own ThingSpeak Account Channel ID, read key, and write key
unsigned long channelID = ;
const char* readAPIKey = "";
const char* writeAPIKey = "";

// 1 is a channel field. You don't need to change if you are following
// this tutorial. You can modify it according to your application
unsigned int powerField = 1;

WiFiClient  client;

void gpioInit();
void fullOn();
void fullOff();
void pressedButton();
void wifiInit();
void circlingClock();
ICACHE_RAM_ATTR void pressedButton();

void setup() {
  Serial.begin(115200);
  delay(100);
  
  gpioInit();
  delay(100);

  wifiInit();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    wifiInit();
  }
  powerMode = ThingSpeak.readFloatField(channelID,powerField,readAPIKey);
  delay(300);
  if(intFired) {
    if(powerMode == 0) {
      fullOn();
      powerMode = 1;
      ThingSpeak.writeField(channelID,powerField,powerMode,writeAPIKey);
      delay(100);
      unsigned char temp;
      int amount = 0;
      while(powerMode != temp && WiFi.status() == WL_CONNECTED) {
        temp = ThingSpeak.readFloatField(channelID,powerField,readAPIKey);
        amount++;
        if(amount > 50)
        {
          temp = powerMode;
        }
      delay(100);
      }
    }
    else {
      fullOff();
      powerMode = 0;
      ThingSpeak.writeField(channelID,powerField,powerMode,writeAPIKey);
      delay(100);
      unsigned char temp;
      int amount = 0;
      while(powerMode != temp && WiFi.status() == WL_CONNECTED) {
        temp = ThingSpeak.readFloatField(channelID,powerField,readAPIKey);
        amount++;
        if(amount > 50)
        {
          temp = powerMode;
        }
        delay(100);
      }
    }
    delay(200);
    intFired = false;
  }
  if(powerMode == 0) {
    fullOff();
  }
  else if(powerMode == 1){
    fullOn();
  }
  else if(powerMode == 2){
    circlingClock();
  }
  else if(powerMode == 3){
    blinky();
  }
  delay(100);
}

// Method to initialize all GPIO pins
void gpioInit() { 
  pinMode(D0, OUTPUT);    // D0, GPIO16, USER, WAKE
  pinMode(D2, OUTPUT);    // D2, GPIO4, SDA
  pinMode(D3, OUTPUT);    // D3, GPIO0, FLASH
  pinMode(D4, OUTPUT);    // D4, GPIO2, TXD1
  pinMode(D5, OUTPUT);    // D5, GPIO14, HSCLK
  pinMode(D6, OUTPUT);    // D6, GPIO12, HMISO
  pinMode(D7, OUTPUT);    // D7, GPIO13, HMOSI, CTS0
  pinMode(D8, OUTPUT);    // D8, GPIO15, HCS, RTS0
  pinMode(3,OUTPUT);      // GPIO3, RXD0

  pinMode(D1,INPUT_PULLUP);       // D1, GPIO5, SCL
  attachInterrupt(digitalPinToInterrupt(D1),pressedButton, RISING);
}

// Method to set all GPIO pins to high
void fullOn() {
    digitalWrite(D0, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
    digitalWrite(D5, 1);
    digitalWrite(D6, 1);
    digitalWrite(D7, 1);
    digitalWrite(D8, 1);
    digitalWrite(3,1);
}

// Method to turn all GPIO pins to low
void fullOff() {
    digitalWrite(D0, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
    digitalWrite(D5, 0);
    digitalWrite(D6, 0);
    digitalWrite(D7, 0);
    digitalWrite(D8, 0);
    digitalWrite(3,0);
}

// Method to have the led that is on circle clockwise around the heart
void circlingClock() {
  int state = 0;
  timer = millis();
  do {
    switch(state) {
    case 0 :
      digitalWrite(D0, 1);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 1 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 1);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 2 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 1);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 3 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 1);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 4 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 1);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 5 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,1);
      delay(75);
      state++;
      break;
    case 6 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 1);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 7 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 1);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state++;
      break;
    case 8 :
      digitalWrite(D0, 0);
      digitalWrite(D2, 1);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      digitalWrite(D6, 0);
      digitalWrite(D7, 0);
      digitalWrite(D8, 0);
      digitalWrite(3,0);
      delay(75);
      state = 0;
      break;
    }
  } while(((millis() - timer) < 5000));
}

// Method to have all the LEDs blink on & off
void blinky() {
  timer = millis();
  do{
    fullOn();
    delay(200);
    fullOff();
    delay(200);
    } while(((millis() - timer) < 5000));
}

// Interrupt used for push button to toggle LEDs
ICACHE_RAM_ATTR void pressedButton() {
  if(intFired == false) {
    intFired = true;
  }
}

// Method to initalize the wifi connection
void wifiInit() {
  if(WiFi.status() != WL_CONNECTED) {
    do {
      // We start by connecting to a WiFi network
      WiFi.begin(ssid, password);
      timer = millis();
      while(((millis() - timer) < 10000) && !isItConnected) {
        if(WiFi.status() != WL_CONNECTED) {
          delay(500);
        }
        else {
          isItConnected = true;
        }
      }
    } while(!isItConnected);
  ThingSpeak.begin(client);
  }
}
