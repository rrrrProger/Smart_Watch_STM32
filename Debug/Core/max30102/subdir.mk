################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/max30102/max30102.c 

OBJS += \
./Core/max30102/max30102.o 

C_DEPS += \
./Core/max30102/max30102.d 


# Each subdirectory must supply rules for building sources it contributes
Core/max30102/%.o Core/max30102/%.su Core/max30102/%.cyclo: ../Core/max30102/%.c Core/max30102/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/roman/Smart_Watch_STM32/Core/max30102" -I"/home/roman/Smart_Watch_STM32/Core/st7735" -I"/home/roman/Smart_Watch_STM32/Core/esp8266" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-max30102

clean-Core-2f-max30102:
	-$(RM) ./Core/max30102/max30102.cyclo ./Core/max30102/max30102.d ./Core/max30102/max30102.o ./Core/max30102/max30102.su

.PHONY: clean-Core-2f-max30102

