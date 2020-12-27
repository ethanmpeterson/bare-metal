#include "stm32f4xx.h"
#include <memory>

#define LED_PORT GPIOB
#define LED_DDR GPIOB
#define LED 1

void delay() {
    for (volatile long long i = 0; i < 5000000; i++);
}

std::unique_ptr<int> a = std::make_unique<int>();
volatile int *b;
volatile float fTestVal = 0;

volatile int clockSpeed = SystemCoreClock;

int main(void) {
	SystemCoreClockUpdate();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // enable GPIO port B  clock
    LED_PORT->MODER |= LED; // set bit 0 to output
    LED_PORT->ODR = 0;

    b = a.get();

	for(;;) {
		LED_PORT->ODR ^= LED;
		delay();

		(*a)++;
    	fTestVal += 0.01;
	}
}
