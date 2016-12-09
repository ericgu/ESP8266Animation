#include <stdarg.h>
#include <pgmspace.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "RGBColor.h"
#include "LEDState.h"
#include "WebForms.h"

#include "AllWhite.h"

#include "Animator.h"
#include "Animation.h"
#include "SingleColor.h"
#include "Rainbow.h"
#include "Chunky.h"
#include "RGBColorFade.h"
 
const char* ssid     = "ASUS";
const char* password = "Gunnerson";
const char* host = "wifitest.adafruit.com";

IPAddress ip(192,168,1,11);  //Node static IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

LEDState ledState;

#define PIN 12

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

Animation* pCurrentAnimation;
 
void printHeap()
{
    Serial.print("Free heap:");
    Serial.println(ESP.getFreeHeap(),DEC);
}

void handleRoot() {
  Serial.println("handleRoot");
  printHeap();
  
  ledState.Set(server);

  printHeap();

  WebForms::SendWebForm(server, ledState);
  Serial.println("Sent welcome");

  //WebForms::parseFormData(server);

  Serial.println(ledState.Mode);
  Serial.println(ledState.RGBValues);
  Serial.println(ledState.TimeInSeconds);
  Serial.println(ledState.CycleCount);

  printHeap();

  delay(100);
}

void SetupWiFi()
{
  Serial.begin(115200);
 
  // We start by connecting to a WiFi network
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


// To support:

// 1) Rainbow
// 2) Single color RGB
//   2A) Single color fade between colors. 
// 3) Set of RGB colors to fade the whole strip
// 4) Circle fade - fade from color A to color B and back again.
// 5) Circle fade with rotate. 

void setup() {

  ledState.Mode = "Rainbow";
  ledState.NewData = 1;

  // initialize digital pin 13 as an output.
  pinMode(0, OUTPUT);

  SetupWiFi();

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'



  Serial.println("Sizes");
  Serial.println(sizeof(Chunk));
  Serial.println(sizeof(Pixel));
  Serial.println(sizeof(RGBColor));
}

void setAnimationFromMode()
{
  if (ledState.NewData)
  {
    printHeap();

    ledState.NewData = false;
    if (pCurrentAnimation)
    {

      Serial.println("Delete");
      delete pCurrentAnimation;
      printHeap();
    }

    Serial.println(ledState.Mode);
    
    if (ledState.Mode == "Rainbow")
    {
      pCurrentAnimation = new Rainbow(&strip, 1200, 128, 0);
    }
    else if (ledState.Mode == "RainbowMirror")
    {
      pCurrentAnimation = new Rainbow(&strip, 1200, 128, 1);
    }
    else if (ledState.Mode == "White")
    {
      SingleColor* pSingleColor = new SingleColor(&strip, RGBColor(255, 255, 255));
      pCurrentAnimation = pSingleColor;
    }
    else if (ledState.Mode == "WhiteDim")
    {
      SingleColor* pSingleColor = new SingleColor(&strip, RGBColor(75, 75, 75));
      pSingleColor->dimToPercentage(30);
      pCurrentAnimation = pSingleColor;
    }
    else if (ledState.Mode == "Seahawks")
    {
      Chunky* pChunky = new Chunky(&strip, 2, 50);
      pChunky->setColor(0, RGBColor(0, 25, 250));
      pChunky->setColor(1, RGBColor(25, 247, 5));
      pCurrentAnimation = pChunky;
    }
    else if (ledState.Mode == "Huskies")
    {
      Chunky* pChunky = new Chunky(&strip, 2, 50);
      pChunky->setColor(0, RGBColor(102, 0, 153));
      pChunky->setColor(1, RGBColor(255, 150, 0));
      pCurrentAnimation = pChunky;
    }  
    else if (ledState.Mode == "RGBColorFade")
    {
      pCurrentAnimation = new RGBColorFade(&strip, ledState.RGBValues);
    }  
    else if (ledState.Mode == "Alternating")
    {
      Chunk chunk = Chunk(ledState.RGBValues);
      Chunky* pChunky = new Chunky(&strip, chunk.numPixels(), ledState.CycleCount);
      for (int i = 0; i < chunk.numPixels(); i++)
      {
        pChunky->setColor(i, chunk.getPixel(i)->getColor());
      } 
      pCurrentAnimation = pChunky;      
    }
    else if (ledState.Mode == "Off")
    {
      pCurrentAnimation = new SingleColor(&strip, RGBColor(0, 0, 0));
    }
  }
}

void loop() {
  //digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(10);              // wait for a second
  //digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  //delay(10);              // wait for a second

    // Check if a client has connected

  server.handleClient();
  setAnimationFromMode();

  pCurrentAnimation->update();
}

