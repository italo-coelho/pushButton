/*
 * pushButton.cpp - Library for Push Buttons without using Delay
 * Created by Ítalo Coelho, January 3rd, 2020
 */

#include "Arduino.h"
#include "pushButton.h"

#define tempoDebounce 50

pushButton::pushButton(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}

bool pushButton::wasPressed()
{
  bool answer = false;

  if( (millis() - delayBotao) >  tempoDebounce )
  {
    estadoAtual = digitalRead(_pin);
    if(!estadoAtual && estadoAnterior)
    {
      answer = true;
      delayBotao = millis();
    }
    estadoAnterior = estadoAtual;
  }

  return answer;
}

bool pushButton::wasReleased()
{
  bool answer = false;

  if( (millis() - delayBotao) >  tempoDebounce )
  {
    estadoAtual = digitalRead(_pin);
    if(estadoAtual && !estadoAnterior)
    {
      answer = true;
      delayBotao = millis();
    }
    estadoAnterior = estadoAtual;
  }

  return answer;
}

bool pushButton::retentionState()
{
  if( (millis() - delayBotao) >  tempoDebounce )
  {
    estadoAtual = digitalRead(_pin);
    if(!estadoAtual && estadoAnterior)
    {
      retention = !retention;
      delayBotao = millis();
    }
    estadoAnterior = estadoAtual;
  }

  return retention;
}

uint64_t pushButton::pressedFor()
{
  if( (millis() - delayBotao) >  tempoDebounce )
  {
    estadoAtual = digitalRead(_pin);
    if(!estadoAtual && estadoAnterior)
    {
      firstPress = millis();
      delayBotao = millis();
    }
    estadoAnterior = estadoAtual;
    if(estadoAtual)
      beenPressedFor = 0;
    else
      beenPressedFor = millis() - firstPress;
  }
  return beenPressedFor;
}