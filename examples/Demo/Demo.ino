/*
 * This example shows the use of pushButton's:
 * - wasPressed: determines if the button was pressed
 * - retentionState: returns the retention state of the button as toggle switch
 * - pressedFor: returns how long the button has been pressed for (in miliseconds)
 * 
 * LED -> pin 10
 * Push Button -> pin 12
 *             -> GND
 */

#include "pushButton.h"

const int LED_PIN = 10;
const int BUTTON_PIN = 12;

pushButton button(BUTTON_PIN);

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  static int counter = 0;
  
  if(button.wasPressed())
    counter++;

  Serial.print("Counter: ")
  Serial.println(counter);

  Serial.print("Been Pressed For: ");
  Serial.println(int(button.pressedFor()));
  
  if(button.retentionState())
    Serial.println("Retention State: ON");
  else
    Serial.println("Retention State: OFF");

  digitalWrite(LED_PIN, button.retentionState());
}