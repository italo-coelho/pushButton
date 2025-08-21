/*
 * pushButton.cpp - Library for Push Buttons without using Delay
 * Created by Ítalo Coelho, January 3rd, 2020
 */

#include "pushButton.h"

pushButton::pushButton(uint8_t pin)
{
  _pin = pin;
  _pinMode = PIN_MODE;
  _debounce = DEBOUNCE;
  pinMode(_pin, _pinMode);
}

pushButton::pushButton(uint8_t pin, uint16_t debounce, uint8_t pin_mode)
{
  _pin = pin;
  _pinMode = pin_mode;
  _debounce = debounce;
  pinMode(_pin, _pinMode);
}

/*
  \brief Determine if the button was Pressed. 
  \note Implemented with debouncing taken in to consideration.
  \return True if Pressed
*/
bool pushButton::wasPressed()
{
  bool answer = false;

  _current = digitalRead(_pin);
  if(!_current && _previous)
  {
    if(time() - _thenPressed > _debounce)
    {
      answer = true;
      _thenPressed = time();
    }
  }
  _previous = _current;

  return answer;
}

/*
  \brief Determine if the button was Released. 
  \note Implemented with debouncing taken in to consideration.
  \return True if Released
*/
bool pushButton::wasReleased()
{
  bool answer = false;

  _current = digitalRead(_pin);
  if(_current && !_previous)
  {
    if(time() - _thenReleased > _debounce)
    {
      answer = true;
      _thenReleased = time();
    }
  }
  _previous = _current;

  return answer;
}

/*
  \brief Determine boolean state of the button as a toggle switch. 
  \note Implemented with debouncing taken in to consideration.
  \return Current State
*/
bool pushButton::retentionState()
{
  _current = digitalRead(_pin);
  if(!_current && _previous)
  {
    if(time() - _thenRetention > _debounce)
    {
      _retention = !_retention;
      _thenRetention = time();
    }
  }
  _previous = _current;

  return _retention;
}

/*
  \brief Calculate the time that the button has been pressed. 
  \note Will return 0 when button is released. Does not take debouncing in to account.
  \return Time in Miliseconds
*/
uint32_t pushButton::pressedFor()
{
  _current = digitalRead(_pin);
  if(!_current && _previous)
  {
    _pressTime = time();
  }
  _previous = _current;
  if(_current)
    _pressDuration = 0;
  else
    _pressDuration = time() - _pressTime;

  return _pressDuration;
}

/*
  \brief Calculate the time that the button was pressed before it was released. 
  \note Will return 0, except in the first call after button is released. Does not take debouncing in to account.
  \return Time in Miliseconds
*/
uint32_t pushButton::releasedAfter()
{
  uint32_t answer;
  uint32_t duration = pressedFor();

  if((duration == 0) && (_pDuration > 0))
    answer = _pDuration;
  else
    answer = 0;
  
  _pDuration = duration;

  return answer;
}

/*
  \brief Get Multiple Fast Clicks
  \param timeout Maximum time in ms allowed between clicks (default = 500ms)
  \note Will return the number of clicks performed after timeout has passed from the last click, otherwise, always returns 0.
  \return Number of clicks
*/
uint8_t pushButton::nClick(uint32_t timeout)
{
  uint8_t answer;

  if(wasPressed())
  {
    _clicks++;
    _lastClick = time();
  }

  if(time() - _lastClick >= timeout)
  {
    answer = _clicks;
    _clicks = 0;
  }
  else
    answer = 0;
  return answer;
}

/*
  \brief Calculate the time since the code started running. 
  \note Does NOT use millis() when compiled for ESP32 to avoid crashes while using FreeRTOS.
  \return Time in Miliseconds
*/
uint32_t pushButton::time()
{
#ifdef ESP32
  return xTaskGetTickCount() *portTICK_PERIOD_MS;
#endif //ESP32

  return millis();
}