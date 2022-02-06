#include <FastLED.h>

#define LED_PIN 4
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];
String readString, red, green, blue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  
  //leds[0] = CRGB(255, 0, 0);
  //FastLED.show();
  
  while (Serial.available()) {
    if (Serial.available() >0) {
      char c = Serial.read(); 
      readString += c; 
    } 
  }

  if (readString.length() >0) {
      
      //255128000
      red = readString.substring(0, 3); //first three characters
      green = readString.substring(3, 6); //next three characters
      blue = readString.substring(6, 9); //last three characters 
      
      int r = red.toInt();
      int g = green.toInt();
      int b = blue.toInt();

      
            
      leds[0] = CRGB(r, g, b);
      FastLED.show();
    readString="";
  } 
}
