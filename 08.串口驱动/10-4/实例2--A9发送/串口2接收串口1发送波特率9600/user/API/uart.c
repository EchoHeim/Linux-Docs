#include "includes.h"

u8 USART1_RX_OK=0;//表示接收到pc下发的一帧数据 *123#
u8 USART1_RX_BUF[20];//存放串口1接收到的数据

/****************************************************
函数名：UART1_Init
形参：无
返回值：无
函数功能：串口1的初始化  PA9 -- TX  PA8 -- RX
****************************************************/
void UART1_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1,ENABLE);//时钟的初始化
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);//管脚9初始化位输出管脚
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_Initstructure);//管脚10初始化位输入管脚
	
	USART_Initstructure.USART_BaudRate = 9600;//配置rs232协议的波特率
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;//配置rs232协议数据位的的位宽
	USART_Initstructure.USART_StopBits = USART_StopBits_1;//配置rs232协议的停止位的位宽
	USART_Initstructure.USART_Parity = USART_Parity_No;//配置rs232协议奇偶校验位
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//配置rs232协议的硬件流控制
	USART_Initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能接收和发送
	USART_Init(USART1,&USART_Initstructure);//串口初始化
	
	USART_Cmd(USART1,ENABLE);//使能串口1
	
}

/****************************************************
函数名：UART2_Init
形参：无
返回值：无
函数功能：串口2的初始化  PA2 -- TX  PA3 -- RX
****************************************************/
void UART2_Init(void)//注释同上
{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //GPIOA时钟初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //UART2时钟初始化
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);                 //管脚2初始化位输出管脚
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_Initstructure);                //管脚3初始化位输入管脚
	
	USART_Initstructure.USART_BaudRate = 9600;                                   //配置rs232协议的波特率
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;                    //配置rs232协议数据位的的位宽
	USART_Initstructure.USART_StopBits = USART_StopBits_1;                         //配置rs232协议的停止位的位宽
	USART_Initstructure.USART_Parity = USART_Parity_No;                            //配置rs232协议奇偶校验位
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//配置rs232协议的硬件流控制
	USART_Initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                //使能接收和发送
	USART_Init(USART2,&USART_Initstructure);                                       //串口初始化
	
	USART_Cmd(USART2,ENABLE);//使能串口2
	
}

/****************************************************
函数名：fputc
形参：ch代表要得到的参数  *f代表数据保存的地方
返回值：返回得到的参数
函数功能：用户printf函数的调用
****************************************************/
int fputc (int ch, FILE *f)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);//等待上次发送数据发送完成
	USART_SendData(USARTx, ch);//把ch中的数据发送到电脑	
	return ch;
}
/****************************************************
函数名：USART1_Echo
形参：无
返回值：无
函数功能：串口1的回显功能  电脑给开发板发送数据，开发板再把接收到的数据返回给电脑
****************************************************/
void USART1_Echo()
{
	u8 ch;
	static u8 USART1_RX_NUM=0; //接收数据数组下标
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
	//等待接收数据
	
	ch = USART_ReceiveData(USART1);//把接收到的数据保存到ch中
	
	if(USART1_RX_NUM >20)
	{
		 USART1_RX_NUM =0;
		 printf("请从新输入");
	 }
	if(ch == '*')
	{
		USART1_RX_NUM=0;//收到起始信号‘*’时，下标值为0
	}
	else if(ch =='#')
	{
		USART1_RX_BUF[USART1_RX_NUM] = '\0';//一帧信号结束,最后加上\0
		USART1_RX_OK =1;//代表一帧信号已收到
	}
	else
	{
		USART1_RX_BUF[USART1_RX_NUM++] = ch;//将接收到的数据按顺序存放在USART1_RX_NUM中
	}
	
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待上次发送数据发送完成
	
	USART_SendData(USART1, ch);//把ch中的数据发送到电脑	
}













