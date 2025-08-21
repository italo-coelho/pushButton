#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#define DEBOUNCE 50
#define PIN_MODE 0x05 //INPUT_PULLUP

#include <Arduino.h>

class pushButton
{
  public:
    pushButton(uint8_t pin);
    pushButton(uint8_t pin, uint16_t debounce, uint8_t pin_mode = PIN_MODE);

    bool wasPressed(void);
    bool wasReleased(void);
    bool retentionState(void);
    uint32_t pressedFor(void);
    uint32_t releasedAfter(void);
    uint8_t nClick(uint32_t timeout = 500);

  private:
    uint8_t _pin;
    uint8_t _pinMode;
    uint16_t _debounce;
    uint32_t _pressTime = 0;
    uint32_t _pressDuration = 0;    
    bool _retention = false;
    bool _current = true;
    bool _previous = true;

    uint8_t _clicks = 0;
    uint32_t _lastClick = 0;
    uint32_t _pDuration = 0;
    uint32_t _thenPressed = 0;
    uint32_t _thenReleased = 0;
    uint32_t _thenRetention = 0;

    uint32_t time();
};

#endif
