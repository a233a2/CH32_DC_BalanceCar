################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/DC_Balance_Car_Control_307/user/src/isr.c \
D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/DC_Balance_Car_Control_307/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/DC_Balance_Car_Control_307/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\Libraries\doc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_components" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Core" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Ld" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Peripheral" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Startup" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\user\inc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_common" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_device" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\code" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/DC_Balance_Car_Control_307/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\Libraries\doc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_components" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Core" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Ld" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Peripheral" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Startup" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\user\inc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_common" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_device" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\code" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
