#ifndef _BEEP_H
#define _BEEP_H

#define BEEP(x) x?GPIO_ResetBits(GPIOB,GPIO_Pin_8): GPIO_SetBits(GPIOB,GPIO_Pin_8)  //����x�����ùܽ�B-8�����0����1

void GPIO_BEEP_Init(void);
void BEEP_ON(void);
void BEEP_OFF(void);

#endif
