// Required libraries will be imported
#include <OneWire.h>
#include <DallasTemperature.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Here the input pin is declared to which the sensor module is connected
#define KY001_Signal_PIN 19 // GPIO2 IO6

// WiFi credentials
const char *ssid = "iPhone";
const char *password = "2pac-1234";

// Libraries are configured
OneWire oneWire(KY001_Signal_PIN);
DallasTemperature sensors(&oneWire);

void setup()
{
  M5.begin(); // Init M5Core.
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  M5.Power.begin(); // Init Power module.
  // print text on lcd with big letters
  M5.Lcd.setTextSize(3); // Set the text size to 3 times the default size
  showMenu();
  // Sensor is initialized
  sensors.begin();
}

// main program loop
void loop()
{
  // check if the button is pressed
  M5.update(); // Update button status
  // capture button A pressed
  if (M5.BtnA.wasPressed())
  {
    M5.Lcd.clear();           // Clear the screen
    M5.Lcd.setCursor(0, 0);   // Set the cursor to the top left corner of the screen
    M5.Lcd.print("Button A"); // Print text on the screen (string)
    // wait 1 second
    delay(1000);
    // call function get temperature
    getTemperature();
    showMenu();
  }
  if (M5.BtnB.wasPressed())
  {
    M5.Lcd.clear();           // Clear the screen
    M5.Lcd.setCursor(0, 0);   // Set the cursor to the top left corner of the screen
    M5.Lcd.print("Button B"); // Print text on the screen (string)
    // wait 1 second
    delay(1000);
    // call function get temperature
    getTime();
    showMenu();
  }
}

// Function to get the temperature
void getTemperature()
{
  // Temperature measurement is started...
  sensors.requestTemperatures();
  // M5 get pin RXD1 and output measured Data
  M5.Lcd.clear();             // Clear the screen
  M5.Lcd.setCursor(0, 0);     // Set the cursor to the top left corner of the screen
  M5.Lcd.print("Temperatur"); // Print text on the screen (string)
  M5.Lcd.setCursor(0, 30);    // Set the cursor to the top left corner of the screen

  // ... and output measured temperature
  M5.Lcd.print("T: "); // Print text on the screen (string)
  M5.Lcd.print(sensors.getTempCByIndex(0));
  delay(4000); // 1s pause until next measurement
}

// function to show time from internet source
void getTime()
{
  M5.Lcd.clear();         // Clear the screen
  M5.Lcd.setCursor(0, 0); // Set the cursor to the top left corner of the screen
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    Serial.println("Do http get request");
    http.begin("http://worldtimeapi.org/api/timezone/Europe/Zurich");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      String payload = http.getString();
      Serial.println(payload);

      // Parse the JSON response to extract the time
      int timeIndex = payload.indexOf("datetime\":\"") + 11;
      String timeString = payload.substring(timeIndex, payload.indexOf("\"", timeIndex));

      M5.Lcd.clear();
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.print("Time:");
      M5.Lcd.setCursor(0, 30);
      M5.Lcd.print(timeString);
      delay(4000); // 1s pause until next measurement
    }
    else
    {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  else
  {
    Serial.println("WiFi not connected");
  }
}

void showMenu()
{
  M5.Lcd.clear();                // Clear the screen
  M5.Lcd.setCursor(0, 0);        // Set the cursor to the top left corner of the screen
  M5.Lcd.print("Button A Temp"); // Print text on the screen (string)
  M5.Lcd.setCursor(0, 30);       // Set the cursor to the top left corner of the screen
  M5.Lcd.print("Button B Time"); // Print text on the screen (string)
  M5.Lcd.setCursor(0, 60);       // Set the cursor to the top left corner of the screen
  M5.Lcd.print("Button C IoT");  // Print text on the screen (string)
}