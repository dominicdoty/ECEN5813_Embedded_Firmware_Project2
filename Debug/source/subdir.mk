################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/POE_Project_2.c \
../source/char_counter.c \
../source/mtb.c \
../source/output_generator.c \
../source/ring_buffer.c \
../source/semihost_hardfault.c \
../source/uart_adapter.c \
../source/uart_handler.c 

OBJS += \
./source/POE_Project_2.o \
./source/char_counter.o \
./source/mtb.o \
./source/output_generator.o \
./source/ring_buffer.o \
./source/semihost_hardfault.o \
./source/uart_adapter.o \
./source/uart_handler.o 

C_DEPS += \
./source/POE_Project_2.d \
./source/char_counter.d \
./source/mtb.d \
./source/output_generator.d \
./source/ring_buffer.d \
./source/semihost_hardfault.d \
./source/uart_adapter.d \
./source/uart_handler.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I../board -I../tests -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../CMSIS_driver -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


