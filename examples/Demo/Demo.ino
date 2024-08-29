/*
 * Example shows the use of Push Buttons:
 * - wasPressed: determines if the button was pressed
 * - retentionState: returns the retention state of the button as toggle switch
 * - pressedFor: returns how long the button has been pressed for (in miliseconds)
 * 
 * Push Button -> pin 12
 * LED -> pin 10
 */

#include "pushButton.h"

#define LED 10
#define BUTTON 12

pushButton button(12);

void setup() 
{
  pinMode(LED, OUTPUT);
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

  digitalWrite(LED, button.retentionState());
}