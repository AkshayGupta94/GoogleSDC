#include "Adafruit_NeoPixel.h"
 
#define PIN 3
#define LEDS 8
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}
 
void loop() {
  strip.setPixelColor(0, 255, 0, 0); //RED
  strip.show(); //Show The Color
  delay(1000);
  strip.setPixelColor(0, 0, 255, 0); //Green
  strip.show(); //Show The Color
  delay(1000);
  strip.setPixelColor(0, 0, 0, 255); //Blue
  strip.show(); //Show The Color
  delay(1000);
}
