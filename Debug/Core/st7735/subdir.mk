################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/st7735/fonts.c \
../Core/st7735/st7735.c \
../Core/st7735/touch.c 

OBJS += \
./Core/st7735/fonts.o \
./Core/st7735/st7735.o \
./Core/st7735/touch.o 

C_DEPS += \
./Core/st7735/fonts.d \
./Core/st7735/st7735.d \
./Core/st7735/touch.d 


# Each subdirectory must supply rules for building sources it contributes
Core/st7735/%.o: ../Core/st7735/%.c Core/st7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/max30102" -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/st7735" -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/esp8266" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-st7735

clean-Core-2f-st7735:
	-$(RM) ./Core/st7735/fonts.d ./Core/st7735/fonts.o ./Core/st7735/st7735.d ./Core/st7735/st7735.o ./Core/st7735/touch.d ./Core/st7735/touch.o

.PHONY: clean-Core-2f-st7735
