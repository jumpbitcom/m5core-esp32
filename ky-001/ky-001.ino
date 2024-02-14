// Required libraries will be imported
#include <OneWire.h>
#include <DallasTemperature.h>            
#include <M5Stack.h>

// Here the input pin is declared to which the sensor module is connected
#define KY001_Signal_PIN 19 // GPIO2 IO6

// Libraries are configured
OneWire oneWire(KY001_Signal_PIN);          
DallasTemperature sensors(&oneWire);    


void setup() {
  M5.begin();  //Init M5Core.
  M5.Power.begin(); //Init Power module.
  // print text on lcd with big letters
  M5.Lcd.setTextSize(3);  // Set the text size to 3 times the default size
  M5.Lcd.print("KY-001 temp");  // Print text on the screen (string)

 // Sensor is initialized
  sensors.begin();  
}

//main program loop
void loop()
{
    // Temperature measurement is started...
    sensors.requestTemperatures();
    // M5 get pin RXD1 and output measured Data 
    M5.Lcd.setCursor(0, 0);  // Set the cursor to the top left corner of the screen
    


    M5.Lcd.print("T: ");  // Print text on the screen (string)
        
    // ... and output measured temperature
    M5.Lcd.print("T: ");  // Print text on the screen (string)
    M5.Lcd.print(sensors.getTempCByIndex(0));

    delay(1000); // 1s pause until next measurement
    M5.Lcd.clear();
    // begin on top of screen to print new temperature
    M5.Lcd.setCursor(0, 0);
}