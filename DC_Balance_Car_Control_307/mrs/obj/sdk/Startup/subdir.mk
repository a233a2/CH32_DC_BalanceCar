################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/sdk/Startup/startup_ch32v30x_D8C.S 

OBJS += \
./sdk/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x_D8C.o: D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/sdk/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Startup" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
