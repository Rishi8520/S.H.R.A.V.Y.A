################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/audioINTERFACE.c \
../src/cognitiveCLASSIFIER.c \
../src/communicationN8N.c \
../src/eegACQUISITION.c \
../src/hal_entry.c \
../src/hapticFEEDBACK.c \
../src/mtk3INTEGRATION.c \
../src/mtk3_stubs.c \
../src/powerMANAGEMENT.c \
../src/semaphoresGLOBAL.c \
../src/shravyaMAIN.c \
../src/signalPROCESSING.c 

C_DEPS += \
./src/audioINTERFACE.d \
./src/cognitiveCLASSIFIER.d \
./src/communicationN8N.d \
./src/eegACQUISITION.d \
./src/hal_entry.d \
./src/hapticFEEDBACK.d \
./src/mtk3INTEGRATION.d \
./src/mtk3_stubs.d \
./src/powerMANAGEMENT.d \
./src/semaphoresGLOBAL.d \
./src/shravyaMAIN.d \
./src/signalPROCESSING.d 

OBJS += \
./src/audioINTERFACE.o \
./src/cognitiveCLASSIFIER.o \
./src/communicationN8N.o \
./src/eegACQUISITION.o \
./src/hal_entry.o \
./src/hapticFEEDBACK.o \
./src/mtk3INTEGRATION.o \
./src/mtk3_stubs.o \
./src/powerMANAGEMENT.o \
./src/semaphoresGLOBAL.o \
./src/shravyaMAIN.o \
./src/signalPROCESSING.o 

SREC += \
SHRAVYA.srec 

MAP += \
SHRAVYA.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/src" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/mtk3_bsp2/include" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/mtk3_bsp2/include/tk" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/mtk3_bsp2/include/sys" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/include" -I"." -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra/fsp/inc" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra/fsp/inc/api" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra/fsp/inc/instances" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra_gen" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra_cfg/fsp_cfg/bsp" -I"/media/rishi/Windows-SSD/PROJECT_&_RESEARCH/TRON_2025/CODEv2/SHRAVYA/ra_cfg/fsp_cfg" -std=c99 -Wno-stringop-overflow -Wno-format-truncation -flax-vector-conversions --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

