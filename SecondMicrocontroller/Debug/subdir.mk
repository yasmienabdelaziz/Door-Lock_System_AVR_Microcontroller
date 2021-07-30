################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EEPROM.c \
../I2C.c \
../LCD.c \
../MC_two.c \
../Timer.c \
../UART.c 

OBJS += \
./EEPROM.o \
./I2C.o \
./LCD.o \
./MC_two.o \
./Timer.o \
./UART.o 

C_DEPS += \
./EEPROM.d \
./I2C.d \
./LCD.d \
./MC_two.d \
./Timer.d \
./UART.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


