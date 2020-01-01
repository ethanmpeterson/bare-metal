#include "stm32f4xx.h"

void ms_delay(int ms) {
  for (; ms > 0; ms--) {
    for (int i = 0; i < 3195; i++)
      ;
  }
}

int main(void) {
  RCC->AHB1ENR |= 1; /* enable GPIOA clock */

  GPIOA->MODER = 0x400;

  while (1) {
    GPIOA->ODR = 0x20;
    ms_delay(2000);
    GPIOA->ODR &= ~0x20;
    ms_delay(2000);
  }
}
