CSOURCES = $(wildcard *.c)
ASMSOURCES = $(wildcard *.s)
CPPSOURCES = $(wildcard *.cpp)

COBJECTS = $(patsubst %.c,%.o,$(CSOURCES))
CPPOBJECTS = $(patsubst %.cpp,%.o,$(CPPSOURCES))
ASMOBJECTS = $(patsubst %.s,%.o,$(ASMSOURCES))

CFLAGS += -mcpu=cortex-m4 -mthumb # M4 specific flags
CFLAGS += -O0 # optimization off
CFLAGS += -std=gnu11 # use GNU 11 standard

CFLAGS += -fno-common
# CFLAGS += -Wall # turn on warnings
# CFLAGS += -pedantic # more warnings
CFLAGS += -Wsign-compare
CFLAGS += -Wcast-align
CFLAGS += -Wconversion # neg int const implicitly converted to uint
CFLAGS += -fsingle-precision-constant
CFLAGS += -fomit-frame-pointer # do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += --specs=nano.specs
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP
CFLAGS += -g

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -mcpu=cortex-m4 -mthumb # M4 specific flags
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP
LDFLAGS += -T link.ld -lstdc++

CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
LD = arm-none-eabi-ld

fw.bin : firmware
	arm-none-eabi-objcopy -O binary $^ $@

firmware: $(COBJECTS) $(CPPOBJECTS) $(ASMOBJECTS)
	$(CPP) $(LDFLAGS) $^ -o $@
	arm-none-eabi-size $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CPP) -c $(CFLAGS) $^ -o $@

%.o: %.s
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm *.o
	rm firmware
# firmware: main.o startup.o syscalls.o sysmem.o clock.o
# 	arm-none-eabi-g++ -T link.ld build/main.o build/startup.o build/clock.o build/syscalls.o \
# 	build/sysmem.o -o build/firmware

# startup.o: startup.s
# 	arm-none-eabi-gcc -c startup.s -o build/startup.o

# main.o: main.cpp
# 	arm-none-eabi-g++ -c main.cpp -o build/main.o

# syscalls.o: syscalls.c
# 	arm-none-eabi-gcc -c syscalls.c -o build/syscalls.o

# sysmem.o: sysmem.c
# 	arm-none-eabi-gcc -c sysmem.c -o build/sysmem.o

# clock.o: clock.c
# 	arm-none-eabi-gcc -c clock.c -o build/clock.o


