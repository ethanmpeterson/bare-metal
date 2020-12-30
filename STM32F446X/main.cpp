#include "stm32f4xx.h"
#include <stdio.h>
#include <math.h>

#define LED_PORT GPIOB
#define LED_DDR GPIOB
#define LED 1

void delay() {
    for (volatile long long i = 0; i < 5000000; i++);
}

uint32_t brVAL = 0;

uint32_t makeBRRValue(uint32_t baud) {
	uint32_t periphClock = SystemCoreClock / 4;
	double usartDiv = (double) periphClock / (8 * baud);
	uint32_t mantissa = (uint32_t) usartDiv;
	uint32_t fraction = round(8 * (usartDiv - mantissa));
	return (mantissa << 4) | fraction;
}

// Configure USART2 which is connected to the blackmagic probe on the PMBoard
void USART2_INIT() {
	// fck is the peripheral clock
	// pg 808 in the reference manual has baud rate selection info

	// USART2 is on APB1
	// need to do clock enable of APB1 bus
	// in APB1 clock enable register, USART 2 enable is bit 17
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // This def is same as 1 << 17

	// Configure PA2 and PA3 and as Tx and Rx for the UART
	// first enable clock for the GPIO pins 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // same as 1 << 0 (enable bit for GPIOA is in bit 0)

	// set the alternate function reister accordingly to get UART setup on PA2 and PA3
	GPIOA->AFR[0] = 0x0700; // index 0 for lower 32 bits of AFR register and UART is in bit 7
	// Mode setting for PA2 in bits 4 and 5. bit 4 should be 0 and bit 5 should be 1
	GPIOA->MODER |= GPIO_MODER_MODER2_1; // same as 1 << 5
	// PA3 also needs to be in alternate function mode. set bit 7
	GPIOA->MODER |= GPIO_MODER_MODER3_1; // same as 1 << 7

	// The following values are for without over sample
	// USART2->BRR = 0x019A; // working
	// USART2->BRR = 0x197; // working
	// uint32_t baud = 115200;
	// USART2->BRR = ((SystemCoreClock / 4) + baud / 2) / baud;
	// brVAL = ((SystemCoreClock / 4) + baud / 2) / baud;
	// USART2->BRR = 0x0307; // working for oversample
	USART2->BRR = makeBRRValue(115200);
	brVAL = makeBRRValue(115200);

	// SET USART enable, transmit enable, receive enable in control register 1
	USART2->CR1 |= USART_CR1_TE; // only enable transmit for now
	USART2->CR1 |= USART_CR1_OVER8;
	USART2->CR1 |= USART_CR1_UE;
}

void USART_WRITE(int c) {
	while (!(USART2->SR & USART_SR_TXE)); // check that there is buffer space first
	USART2->DR = (c & 0xFF);
}

__attribute__((weak)) int __io_putchar(int ch) {
	USART_WRITE(ch);
	return 0;
}

int main(void) {
	SystemCoreClockUpdate();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // enable GPIO port B  clock
    LED_PORT->MODER |= LED; // set bit 0 to output
    LED_PORT->ODR = 0;
	USART2_INIT();

	printf("Hello World!\n");
	for(;;) {
    	LED_PORT->ODR ^= 1;
		USART_WRITE(65);
		delay();
	}
}
