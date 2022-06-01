/*
 * pushButton.cpp - Library for Push Buttons without using Delay
 * Created by Ítalo Coelho, January 3rd, 2020
 */

#include "Arduino.h"
#include "pushButton.h"

#define debounce 50

pushButton::pushButton(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}

bool pushButton::wasPressed()
{
  bool answer = false;
  static uint64_t then = millis();

  estadoAtual = digitalRead(_pin);
  if(!estadoAtual && estadoAnterior)
  {
    if(millis() - then > debounce)
    {
      answer = true;
      then = millis();
    }
  }
  estadoAnterior = estadoAtual;

  return answer;
}

bool pushButton::wasPressed(int _debounce)
{
  bool answer = false;
  static uint64_t then = millis();

  estadoAtual = digitalRead(_pin);
  if(!estadoAtual && estadoAnterior)
  {
    if(millis() - then > _debounce)
    {
      answer = true;
      then = millis();
    }
  }
  estadoAnterior = estadoAtual;

  return answer;
}

bool pushButton::wasReleased()
{
  bool answer = false;
  static uint64_t then = millis();

  estadoAtual = digitalRead(_pin);
  if(estadoAtual && !estadoAnterior)
  {
    if(millis() - then > debounce)
    {
      answer = true;
      then = millis();
    }
  }
  estadoAnterior = estadoAtual;

  return answer;
}

bool pushButton::retentionState()
{
  static uint64_t then = millis();

  estadoAtual = digitalRead(_pin);
  if(!estadoAtual && estadoAnterior)
  {
    if(millis() - then > debounce)
    {
      retention = !retention;
      then = millis();
    }
  }
  estadoAnterior = estadoAtual;

  return retention;
}

uint64_t pushButton::pressedFor()
{
  estadoAtual = digitalRead(_pin);
  if(!estadoAtual && estadoAnterior)
  {
    firstPress = millis();
  }
  estadoAnterior = estadoAtual;
  if(estadoAtual)
    beenPressedFor = 0;
  else
    beenPressedFor = millis() - firstPress;

  return beenPressedFor;
}