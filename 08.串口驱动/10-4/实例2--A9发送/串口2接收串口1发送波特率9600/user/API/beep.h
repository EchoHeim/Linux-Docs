#ifndef _BEEP_H
#define _BEEP_H

#define BEEP(x) x?GPIO_ResetBits(GPIOB,GPIO_Pin_8): GPIO_SetBits(GPIOB,GPIO_Pin_8)  //根据x，来让管脚B-8，输出0或者1

void GPIO_BEEP_Init(void);
void BEEP_ON(void);
void BEEP_OFF(void);

#endif
