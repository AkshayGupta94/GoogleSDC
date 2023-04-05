// muntaser, pennapps 2022
// Send an 'P' to toggle pump
// Refrences:
// https://www.arduino.cc/en/tutorial/sweep
// https://www.arduino.cc/en/serial/read
#include <Servo.h>
#include "Adafruit_NeoPixel.h"

#define PIN 3
#define LEDS 8

Servo servo;
int angle = 10;
#define PIN_PUMP_ON 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

const char HEATSINK_FAN_ON = 'F';
const char HEATSINK_FAN_OFF = 'f';
const char EXHAUST_FAN_ON = 'E';
const char EXHAUST_FAN_OFF = 'e';
const char COOLER_ON = 'C';
const char COOLER_OFF = 'c';
const char HEATER_ON = 'H';
const char HEATER_OFF = 'h';
const char LIGHT_ON = 'L';
const char LIGHT_OFF = 'l';
const char PUMP_ON = 'P';
const char PUMP_OFF = 'p';
const char DEMOCOMBO = 'X';


void setup() {
  //initialize connections here
  pinMode(PIN_PUMP_ON, OUTPUT);

  Serial.begin(115200);     // opens serial port
  servo.attach(9);
  servo.write(angle);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  
}

void fanControl(int x) {
  //code to control heatsink fan here
  //x = 1 fan on, x = 0 fan off
  
}


void fanControl2(int x) {
  //code to control exhaust fan here
  //x = 1 fan on, x = 0 fan off
  
}


void coolerControl(int x) {
  //code to control cooler here
  //x = 1 cooler on, x = 0 cooler off
  
    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 255, 0); //GREEN
  strip.show(); //Show The Color
  delay(300);
    }

    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 0, 0); //OFF
  strip.show(); //Show The Color
  delay(300);
    }
  
}


//void heaterControl(int x) {
//  //code to control heater here
//  //x = 1 heater on, x = 0 heater off
//  
//}


void lightControl(int x) {
  //code to control light here
  //x = 1 light on, x = 0 light off
  if (x == 1) {
    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 255, 255, 255); //RED
  strip.show(); //Show The Color
  delay(300);
    }
  }

  
  if (x == 0) {
    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 0, 0); //RED
  strip.show(); //Show The Color
  delay(300);
    }
  }

  
}



void heaterControl(int x) {
  //code to control heater here
  //x = 1 heater on, x = 0 heater off
  if (x == 1) {

    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 255, 0, 0); //RED
  strip.show(); //Show The Color
  delay(300);
    }

    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 0, 0); //RED
  strip.show(); //Show The Color
  delay(300);
    }
      for(int angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  }
  }
  else { 
  // now scan back from 180 to 10 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
  }
  
}

void pumpControl( int x) {

  if (x == 0) {
    digitalWrite(PIN_PUMP_ON, LOW);
  delay(1000);
  }
  if (x==1) {

  
    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 0, 255); //BLUE
  strip.show(); //Show The Color
  delay(300);
    }


    
      digitalWrite(PIN_PUMP_ON, HIGH);
  delay(2000);

    for (int i = 0; i<8; i++) {
  strip.setPixelColor(i, 0, 0, 0); //OFF
  strip.show(); //Show The Color
  delay(300);
    }
  
    digitalWrite(PIN_PUMP_ON, LOW);
  delay(1000);
  }
}


void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    int incomingByte = Serial.read(); // read the incoming byte:

    Serial.print("Recieved: ");
    Serial.println(incomingByte, DEC);
    if (incomingByte == HEATSINK_FAN_ON) {
      fanControl(1);
    }
    if (incomingByte == HEATSINK_FAN_OFF) {
      fanControl(0);
    }
    if (incomingByte == EXHAUST_FAN_ON) {
      fanControl2(1);
    }
    if (incomingByte == EXHAUST_FAN_OFF) {
      fanControl2(0);
    }
    if (incomingByte == COOLER_ON) {
      coolerControl(1);
    }
    if (incomingByte == COOLER_OFF) {
      coolerControl(0);
    }
    if (incomingByte == HEATER_ON) {
      heaterControl(1);
    }
    if (incomingByte == HEATER_OFF) {
      heaterControl(0);
    }
    if (incomingByte == LIGHT_ON) {
      lightControl(1);
    }
    if (incomingByte == LIGHT_OFF) {
      lightControl(0);
    }

    if (incomingByte == PUMP_OFF) {
      pumpControl(0);
    }

    if (incomingByte == PUMP_ON) {
      pumpControl(1);
      pumpControl(0);
    }

     if (incomingByte == DEMOCOMBO) {
      delay(20000);
      lightControl(1);
      delay(1000);
      lightControl(0);
      delay(1000);
      pumpControl(1);
      delay(1000);
      pumpControl(0);
      delay(500);
      heaterControl(1);
      delay(500);
      heaterControl(0);
      delay(500);
      coolerControl(1);
      delay(500);
      coolerControl(0);
      delay(500);
      while (1) {
        Serial.flush();
        delay(1000);
      }
    }

    Serial.flush();
    delay(1000);
    incomingByte = PUMP_OFF;
    
        
  }
}
