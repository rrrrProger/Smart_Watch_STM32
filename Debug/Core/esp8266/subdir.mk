################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/esp8266/esp8266.c 

OBJS += \
./Core/esp8266/esp8266.o 

C_DEPS += \
./Core/esp8266/esp8266.d 


# Each subdirectory must supply rules for building sources it contributes
Core/esp8266/%.o Core/esp8266/%.su Core/esp8266/%.cyclo: ../Core/esp8266/%.c Core/esp8266/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/max30102" -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/st7735" -I"C:/Users/Roman/STM32CubeIDE/workspace_1.8.0/Watch/Core/esp8266" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-esp8266

clean-Core-2f-esp8266:
	-$(RM) ./Core/esp8266/esp8266.cyclo ./Core/esp8266/esp8266.d ./Core/esp8266/esp8266.o ./Core/esp8266/esp8266.su

.PHONY: clean-Core-2f-esp8266

