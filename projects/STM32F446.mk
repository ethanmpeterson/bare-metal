CMSIS = ../../libraries/CMSIS_5

SRCS += ../../includes/STM32F446XX/system_stm32f4xx.c
SRCS += ../../includes/STM32F446XX/startup_stm32f446xx.s

OBJS := $(addprefix ,$(notdir $(SRCS:.c=.o)))
OBJS := $(addprefix ,$(notdir $(OBJS:.s=.o)))
vpath %.c $(sort $(dir $(SRCS)))
vpath %.s $(sort $(dir $(SRCS)))

INCLUDES += -I.
INCLUDES += -I../../includes/STM32F446XX
INCLUDES += -I$(CMSIS)/CMSIS/Core/Include

CFLAGS += $(CDEFS)

CFLAGS += -mcpu=cortex-m4 -mthumb # M4 specific flags
CFLAGS += -O0 # optimization off
CFLAGS += -std=gnu11 # use GNU 11 standard

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2 # generate debug info
# generate dependency info
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
endif

CFLAGS += -fno-common
CFLAGS += -Wall # turn on warnings
CFLAGS += -pedantic # more warnings
CFLAGS += -Wsign-compare
CFLAGS += -Wcast-align
CFLAGS += -Wconversion # neg int const implicitly converted to uint
CFLAGS += -fsingle-precision-constant
CFLAGS += -fomit-frame-pointer # do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += --specs=nano.specs

# NOTE: Change this FPU option depending on the specific M4 in use
#CFLAGS += -mfloat-abi=soft # No FP
CFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 # Soft FP
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP

LDFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16 # Soft FP
#LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 # Hard FP

LDFLAGS += -mcpu=cortex-m4 -mthumb # processor setup
#LDFLAGS += -nostartfiles # no start files are used
LDFLAGS += --specs=nano.specs
LDFLAGS += -Wl,--gc-sections # linker garbage collector
LDFLAGS += -Wl,-Map=$(TARGET).map #generate map file
LDFLAGS += -T$(LINKER_SCRIPT)
LDFLAGS += $(LIBS)
LDFLAGS += -lc

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size
DBG = $(CROSS_COMPILE)gdb

all: clean $(SRCS) build size
	@echo "Successfully finished..."

build: $(TARGET).elf $(TARGET).bin $(TARGET).lst

$(TARGET).elf: $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	@echo "Building" $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	@echo "Building" $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.hex: %.elf
	@$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	@$(OBJCOPY) -O binary $< $@

%.lst: %.elf
	@$(OBJDUMP) -x -S $(TARGET).elf > $@

size: $(TARGET).elf
	@$(SIZE) $(TARGET).elf

disass: $(TARGET).elf
	@$(OBJDUMP) -d $(TARGET).elf

disass-all: $(TARGET).elf
	@$(OBJDUMP) -D $(TARGET).elf

debug:
	@$(DBG) --eval-command="target extended-remote :4242" \
	 $(TARGET).elf

burn:
	@st-info --probe
	@openocd -f board/st_nucleo_f4.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	@echo "Cleaning..."
	@rm -f $(TARGET).elf
	@rm -f $(TARGET).bin
	@rm -f $(TARGET).map
	@rm -f $(TARGET).hex
	@rm -f $(TARGET).lst
	@rm -f *.o
	@rm -f *.d

.PHONY: all build size clean burn disass disass-all
