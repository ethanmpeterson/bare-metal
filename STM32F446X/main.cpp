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

// Configure USART2 which is connected to the blackmagic probe on the PMBoard
void UART_INIT() {
	// fck is the peripheral clock
	// pg 808 in the reference manual has baud rate selection info

	// USART2 is on APB1
	// need to do clock enable of APB1 bus
	// in APB1 clock enable register, USART 2 enable is bit 17
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // This def is same as 1 << 17

}

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
