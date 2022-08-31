################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/kosh/Documents/GitHub/LSM100A_SDK/Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.c \
C:/Users/kosh/Documents/GitHub/LSM100A_SDK/Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.c 

OBJS += \
./Middlewares/Sigfox/sigfox_aes.o \
./Middlewares/Sigfox/sigfox_data.o 

C_DEPS += \
./Middlewares/Sigfox/sigfox_aes.d \
./Middlewares/Sigfox/sigfox_data.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Sigfox/sigfox_aes.o: C:/Users/kosh/Documents/GitHub/LSM100A_SDK/Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.c Middlewares/Sigfox/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DMX_BOARD_PSEUDODRIVER -DCORE_CM4 -DSTM32WLE5xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../Sigfox/App -I../../Sigfox/Target -I../../Sigfox/SJ -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../../../../../../Middlewares/Third_Party/Sigfox/Crypto -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../Middlewares/Third_Party/Sigfox/Monarch -I../../../../../../../Middlewares/Third_Party/Sigfox/SigfoxLib -I../../../../../../../Middlewares/Third_Party/Sigfox/SigfoxLibTest -I../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Sigfox/sigfox_data.o: C:/Users/kosh/Documents/GitHub/LSM100A_SDK/Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.c Middlewares/Sigfox/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DMX_BOARD_PSEUDODRIVER -DCORE_CM4 -DSTM32WLE5xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../Sigfox/App -I../../Sigfox/Target -I../../Sigfox/SJ -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../../../../../../Middlewares/Third_Party/Sigfox/Crypto -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../Middlewares/Third_Party/Sigfox/Monarch -I../../../../../../../Middlewares/Third_Party/Sigfox/SigfoxLib -I../../../../../../../Middlewares/Third_Party/Sigfox/SigfoxLibTest -I../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

