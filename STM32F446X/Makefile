BUILD_DIR = build
INCLUDES = \
-Ilibraries/CMSIS/Device/ST/STM32F4xx/Include \
-Ilibraries/CMSIS/Include


CSOURCES = $(wildcard *.c)
ASMSOURCES = $(wildcard *.s)
CPPSOURCES = $(wildcard *.cpp)

COBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CSOURCES))
CPPOBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPPSOURCES))
ASMOBJECTS = $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASMSOURCES))

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
CFLAGS += $(INCLUDES)


LDFLAGS += -Wl,--gc-sections
LDFLAGS += -mcpu=cortex-m4 -mthumb # M4 specific flags
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP
LDFLAGS += -T link.ld -lstdc++
LDFLAGS += -lm
LDFLAGS += $(INCLUDES)


CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
LD = arm-none-eabi-ld

$(BUILD_DIR)/fw.bin: $(BUILD_DIR)/firmware.elf
	arm-none-eabi-objcopy -O binary $^ $@

$(BUILD_DIR)/firmware.elf: $(COBJECTS) $(CPPOBJECTS) $(ASMOBJECTS)
	$(CPP) $(LDFLAGS) $^ -o $@
	arm-none-eabi-size $@

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CPP) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.s
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm build/*

blackmagic:
	@gdb-multiarch -nx --batch \
  		-ex 'target extended-remote /dev/ttyACM0' \
  		-ex 'monitor swdp_scan' \
  		-ex 'attach 1' \
  		-ex 'load' \
  		-ex 'compare-sections' \
  		-ex 'kill' \
  		$(BUILD_DIR)/firmware.elf

stlink:
	@st-flash write $(BUILD_DIR)/fw.bin 0x8000000