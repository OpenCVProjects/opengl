################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Cara.cpp \
../src/Modelo.cpp \
../src/Mundo.cpp \
../src/Punto3D.cpp \
../src/main.cpp 

OBJS += \
./src/Cara.o \
./src/Modelo.o \
./src/Mundo.o \
./src/Punto3D.o \
./src/main.o 

CPP_DEPS += \
./src/Cara.d \
./src/Modelo.d \
./src/Mundo.d \
./src/Punto3D.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


