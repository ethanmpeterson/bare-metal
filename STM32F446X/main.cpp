#include <memory>

std::unique_ptr<int> a = std::make_unique<int>();
volatile int *b;

int main(void) {
  b = a.get();
	for(;;) {
		(*a)++;
	}
}
