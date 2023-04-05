#include <Wire.h>
#include <Adafruit_MPL115A2.h>
#include "Adafruit_seesaw.h"
#include "Adafruit_SHT4x.h"
#include "Adafruit_CCS811.h"
#include "Adafruit_VEML6070.h"

Adafruit_VEML6070 uv = Adafruit_VEML6070();
Adafruit_CCS811 ccs;

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

Adafruit_seesaw ss;

Adafruit_MPL115A2 mpl115a2;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");

  Serial.println("VEML6070 Test");
  uv.begin(VEML6070_1_T);  // pass in the integration time constant

  Serial.println("CCS811 test");

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
  
  Serial.println("Getting barometric pressure ...");
  if (! mpl115a2.begin()) {
    Serial.println("Sensor not found! Check wiring");
    while (1);
  }
    Serial.println("seesaw Soil Sensor active!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

    Serial.println("Adafruit SHT4x test");
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  // You can have 3 different precisions, higher precision takes longer
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  switch (sht4.getPrecision()) {
     case SHT4X_HIGH_PRECISION: 
       Serial.println("High precision");
       break;
     case SHT4X_MED_PRECISION: 
       Serial.println("Med precision");
       break;
     case SHT4X_LOW_PRECISION: 
       Serial.println("Low precision");
       break;
  }
  
}

void loop(void) 
{
  float pressureKPA = 0, temperatureC = 0;    

  mpl115a2.getPT(&pressureKPA,&temperatureC);
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
  Serial.print("Outdoor Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C both measured together");
  
  pressureKPA = mpl115a2.getPressure();  
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.println(" kPa");

  temperatureC = mpl115a2.getTemperature();  
  Serial.print("Outdoor Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");

  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Soil Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Soil Moisture: "); Serial.println(capread);

  sensors_event_t humidity, temp;
  
  uint32_t timestamp = millis();
  sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  timestamp = millis() - timestamp;

  Serial.print("Indoor Air Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  Serial.print("Read duration (ms): ");
  Serial.println(timestamp);

  if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());      
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }

  Serial.print("UV light level: "); Serial.println(uv.readUV());

  Serial.print ("##");
  Serial.print(temperatureC, 2);
  Serial.print ("$$");
  Serial.print(pressureKPA, 4);

  Serial.print ("$$");
  Serial.print(tempC);
  Serial.print ("$$");
  Serial.print(capread);
  Serial.print ("$$");
  Serial.print(temp.temperature);
  Serial.print ("$$");
  Serial.print(humidity.relative_humidity);
  Serial.print ("$$");
  Serial.print(ccs.geteCO2());
  Serial.print ("$$");
  Serial.print(ccs.getTVOC());
  Serial.print ("$$");
  Serial.print(uv.readUV());

  Serial.println("!!");


  delay(4000);
  
}
