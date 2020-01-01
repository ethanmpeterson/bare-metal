#include "stm32f4xx.h"

void ms_delay(int ms) {
  while (ms-- > 0) {
    volatile int x = 500;
    while (x-- > 0)
      __asm("nop");
  }
}

int main(void) {
  RCC->AHB1ENR |= 1; /* enable GPIOA clock */

  GPIOA->MODER &= ~0x00000C00; /* clear pin mode */
  GPIOA->MODER |= 0x00000400;  /* set pin to output mode */

  while (1) {
    GPIOA->BSRR = 0x00000020; /* turn on LED */
    ms_delay(500);
    GPIOA->BSRR = 0x00200000; /* turn off LED */
    ms_delay(500);
  }
}
