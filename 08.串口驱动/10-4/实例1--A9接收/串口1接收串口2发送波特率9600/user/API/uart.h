#ifndef _UART_H_
#define _UART_H_
#include "stm32f10x.h"
#define USARTx USART1

extern u8 USART1_RX_OK;//��ʾ���յ�pc�·���һ֡���� *123#
extern u8 USART1_RX_BUF[20];//��Ŵ���1���յ�������

void UART1_Init(void);//����1��ʼ��
void UART2_Init(void);//����2��ʼ��
void USART1_Echo(void);   //����1�Ļ��Ժ���

#endif
