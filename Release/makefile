################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
interrupts.lss \

FLASH_IMAGE += \
interrupts.hex \

EEPROM_IMAGE += \
interrupts.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: interrupts.elf secondary-outputs

# Tool invocations
interrupts.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,interrupts.map -mmcu=atmega1284p -o "interrupts.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

interrupts.lss: interrupts.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S interrupts.elf  >"interrupts.lss"
	@echo 'Finished building: $@'
	@echo ' '

interrupts.hex: interrupts.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex interrupts.elf  "interrupts.hex"
	@echo 'Finished building: $@'
	@echo ' '

interrupts.eep: interrupts.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex interrupts.elf  "interrupts.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: interrupts.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega1284p interrupts.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) interrupts.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
