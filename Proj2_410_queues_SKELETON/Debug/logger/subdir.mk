################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../logger/logger_single_thread.cpp 

OBJS += \
./logger/logger_single_thread.o 

CPP_DEPS += \
./logger/logger_single_thread.d 


# Each subdirectory must supply rules for building sources it contributes
logger/%.o: ../logger/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


