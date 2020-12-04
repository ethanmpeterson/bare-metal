firmware: main.o startup.o syscalls.o sysmem.o clock.o
	arm-none-eabi-gcc -T link.ld build/main.o build/startup.o build/clock.o build/syscalls.o \
	build/sysmem.o -o build/firmware

startup.o: startup.s
	arm-none-eabi-gcc -c startup.s -o build/startup.o

main.o: main.c
	arm-none-eabi-gcc -c main.c -o build/main.o

syscalls.o: syscalls.c
	arm-none-eabi-gcc -c syscalls.c -o build/syscalls.o

sysmem.o: sysmem.c
	arm-none-eabi-gcc -c sysmem.c -o build/sysmem.o

clock.o: clock.c
	arm-none-eabi-gcc -c clock.c -o build/clock.o

clean:
	rm build/**


