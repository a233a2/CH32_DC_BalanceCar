#include "zf_common_headfile.h"

extern float Angle_Y;  //主要！前后角度
extern float Angle_Y_zero;//零飘

extern float Gyro_Y;  //主要！前后角度
extern float Gyro_Y_zero;//零飘

extern float Angle_Z;  //左右角度
//extern float Angle_Z_zero;//零飘


void angle_fliter_get(void);
void Y_angle_ZeroOFFset_get(void);
