#include "includes.h"

/****************************************************
函数名：
形参：
返回值：
函数功能：
****************************************************/
int main(void)
{
	u8 ch;
	UART1_Init();
	UART2_Init();
	while(1)
	{
			while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
			ch = USART_ReceiveData(USART1);
			USART_SendData(USART2, ch);
	}
}





/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
