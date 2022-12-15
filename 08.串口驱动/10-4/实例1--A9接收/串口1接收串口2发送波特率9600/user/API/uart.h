#ifndef _UART_H_
#define _UART_H_
#include "stm32f10x.h"
#define USARTx USART1

extern u8 USART1_RX_OK;//表示接收到pc下发的一帧数据 *123#
extern u8 USART1_RX_BUF[20];//存放串口1接收到的数据

void UART1_Init(void);//串口1初始化
void UART2_Init(void);//串口2初始化
void USART1_Echo(void);   //串口1的回显函数

#endif
