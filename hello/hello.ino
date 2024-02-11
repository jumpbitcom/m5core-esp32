#include <M5Stack.h>

// After M5Core is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void setup()
{
  M5.begin();  //Init M5Core.
  M5.Power.begin(); //Init Power module.
  // print text on lcd with big letters
  M5.Lcd.setTextSize(3);  // Set the text size to 3 times the default size
  M5.Lcd.print("Hello Martin");  // Print text on the screen (string)
  
}

// After the program in setup() runs, it runs the program in loop()
// The loop() function is an infinite loop in which the program runs repeatedly
void loop()
{
  M5.update();  // Update button status
  // capture button A pressed
  if (M5.BtnA.wasPressed())
  {
    M5.Lcd.clear();  // Clear the screen
    M5.Lcd.print("Button A pressed");  // Print text on the screen (string)
  }
}