################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/zf_components/seekfree_assistant.c \
D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/zf_components/seekfree_assistant_interface.c 

OBJS += \
./zf_components/seekfree_assistant.o \
./zf_components/seekfree_assistant_interface.o 

C_DEPS += \
./zf_components/seekfree_assistant.d \
./zf_components/seekfree_assistant_interface.d 


# Each subdirectory must supply rules for building sources it contributes
zf_components/seekfree_assistant.o: D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/zf_components/seekfree_assistant.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\Libraries\doc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_components" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Core" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Ld" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Peripheral" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Startup" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\user\inc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_common" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_device" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\code" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_components/seekfree_assistant_interface.o: D:/DeskTop.....IMPORTANT/CHV307_Library-master/CH32V307/DC_Balance_Car_Control_307/libraries/zf_components/seekfree_assistant_interface.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\Libraries\doc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_components" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Core" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Ld" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Peripheral" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\sdk\Startup" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\user\inc" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_common" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_device" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\DC_Balance_Car_Control_307\code" -I"D:\DeskTop.....IMPORTANT\CHV307_Library-master\CH32V307\DC_Balance_Car_Control_307\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

