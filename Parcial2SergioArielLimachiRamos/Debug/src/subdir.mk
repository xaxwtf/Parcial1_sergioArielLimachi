################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LinkedList.c \
../src/Parcial2SergioArielLimachiRamos.c \
../src/afiche.c \
../src/cliente.c \
../src/control.c \
../src/informe.c \
../src/parser.c \
../src/utn.c 

OBJS += \
./src/LinkedList.o \
./src/Parcial2SergioArielLimachiRamos.o \
./src/afiche.o \
./src/cliente.o \
./src/control.o \
./src/informe.o \
./src/parser.o \
./src/utn.o 

C_DEPS += \
./src/LinkedList.d \
./src/Parcial2SergioArielLimachiRamos.d \
./src/afiche.d \
./src/cliente.d \
./src/control.d \
./src/informe.d \
./src/parser.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


