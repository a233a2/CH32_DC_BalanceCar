/*
 * Other.h
 *
 *  Created on: 2024Äê5ÔÂ11ÈÕ
 *      Author: SJY
 */

#ifndef OTHER_H_
#define OTHER_H_



#define PRESS_ENTER C4
#define PRESS_NEXT C5


void LED_Blink_Init(void);
void LED_Light(void);
void LED_Blink(void);

void Beep_Init(void);


void Key_Init(void);
void Y_angle_ZeroOFFset_get(void);

void Beep_Test(void);
void Beep_Ring_500MS(void);

extern const uint8  choumao[877];

#endif /* OTHER_H_ */
