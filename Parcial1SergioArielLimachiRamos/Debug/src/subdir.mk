################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Parcial1SergioArielLimachiRamos.c \
../src/cliente.c \
../src/informe.c \
../src/publicacion.c \
../src/utn.c 

OBJS += \
./src/Parcial1SergioArielLimachiRamos.o \
./src/cliente.o \
./src/informe.o \
./src/publicacion.o \
./src/utn.o 

C_DEPS += \
./src/Parcial1SergioArielLimachiRamos.d \
./src/cliente.d \
./src/informe.d \
./src/publicacion.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


