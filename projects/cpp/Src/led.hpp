#ifndef _LEDCPP_H
#define _LEDCPP_H
#include "stm32f4xx_hal.h"

class CLed {
  GPIO_TypeDef *_port;  // GPIOA,GPIOB....
  uint16_t _pin;        // GPIO_PIN_0,GPIO_PIN_1....
  uint16_t _toggleTime; // Toggle time in ms
  uint16_t counter;     // Toggle time counter
  void on() { HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET); }    // turn on LED
  void off() { HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET); } // turn off LED
  void toggle() { HAL_GPIO_TogglePin(_port, _pin); }             // toggle LED
public:
  CLed(GPIO_TypeDef *port, uint16_t pin, uint16_t toggleTim); // constructor
  void runToggle(); // run toggling LED from system tick every 1ms
};

#endif
