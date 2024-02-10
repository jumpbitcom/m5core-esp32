#include <M5Stack.h>

// After M5Core is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void setup()
{
  M5.begin();  //Init M5Core.
  M5.Power.begin(); //Init Power module.
  M5.Lcd.print("Hello World");  // Print text on the screen (string)
}

// After the program in setup() runs, it runs the program in loop()
// The loop() function is an infinite loop in which the program runs repeatedly
void loop()
{
}