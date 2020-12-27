#include "stm32f4xx.h"
#include <memory>

std::unique_ptr<int> a = std::make_unique<int>();
volatile int *b;
volatile float fTestVal = 0;

int main(void) {
  b = a.get();
	for(;;) {
		(*a)++;
    fTestVal += 0.01;
	}
}
