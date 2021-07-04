#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

class pushButton
{
  public:
    //Constructor
    pushButton(int pin);
    //Interface
    bool wasPressed(void);
    bool wasReleased(void);
    bool retentionState(void);
    uint64_t pressedFor(void);
  private:
    //Control Variables
    int _pin;
    uint64_t delayBotao = 0;
    uint64_t firstPress = 0;
    uint64_t beenPressedFor = 0;    
    bool retention = false;
    bool estadoAtual = HIGH;
    bool estadoAnterior = HIGH;
};

#endif
