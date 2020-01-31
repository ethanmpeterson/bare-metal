#include "LEDcpp.hpp"

CLed::CLed(GPIO_TypeDef *port, uint16_t pin, uint16_t toggleTime) {
  _port = port;
  _pin = pin;
  _toggleTime = toggleTime;
  counter = 0;
  off();
}

void CLed::runToggle() {
  if (++counter >= _toggleTime) {
    counter = 0;
    toggle();
  }
}
