#include "includes.h"

u8 USART1_RX_OK=0;//��ʾ���յ�pc�·���һ֡���� *123#
u8 USART1_RX_BUF[20];//��Ŵ���1���յ�������

/****************************************************
��������UART1_Init
�βΣ���
����ֵ����
�������ܣ�����1�ĳ�ʼ��  PA9 -- TX  PA8 -- RX
****************************************************/
void UART1_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1,ENABLE);//ʱ�ӵĳ�ʼ��
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);//�ܽ�9��ʼ��λ����ܽ�
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_Initstructure);//�ܽ�10��ʼ��λ����ܽ�
	
	USART_Initstructure.USART_BaudRate = 9600;//����rs232Э��Ĳ�����
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;//����rs232Э������λ�ĵ�λ��
	USART_Initstructure.USART_StopBits = USART_StopBits_1;//����rs232Э���ֹͣλ��λ��
	USART_Initstructure.USART_Parity = USART_Parity_No;//����rs232Э����żУ��λ
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����rs232Э���Ӳ��������
	USART_Initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܽ��պͷ���
	USART_Init(USART1,&USART_Initstructure);//���ڳ�ʼ��
	
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���1
	
}

/****************************************************
��������UART2_Init
�βΣ���
����ֵ����
�������ܣ�����2�ĳ�ʼ��  PA2 -- TX  PA3 -- RX
****************************************************/
void UART2_Init(void)//ע��ͬ��
{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //GPIOAʱ�ӳ�ʼ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //UART2ʱ�ӳ�ʼ��
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);                 //�ܽ�2��ʼ��λ����ܽ�
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_Initstructure);                //�ܽ�3��ʼ��λ����ܽ�
	
	USART_Initstructure.USART_BaudRate = 9600;                                   //����rs232Э��Ĳ�����
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;                    //����rs232Э������λ�ĵ�λ��
	USART_Initstructure.USART_StopBits = USART_StopBits_1;                         //����rs232Э���ֹͣλ��λ��
	USART_Initstructure.USART_Parity = USART_Parity_No;                            //����rs232Э����żУ��λ
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����rs232Э���Ӳ��������
	USART_Initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                //ʹ�ܽ��պͷ���
	USART_Init(USART2,&USART_Initstructure);                                       //���ڳ�ʼ��
	
	USART_Cmd(USART2,ENABLE);//ʹ�ܴ���2
	
}

/****************************************************
��������fputc
�βΣ�ch����Ҫ�õ��Ĳ���  *f�������ݱ���ĵط�
����ֵ�����صõ��Ĳ���
�������ܣ��û�printf�����ĵ���
****************************************************/
int fputc (int ch, FILE *f)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);//�ȴ��ϴη������ݷ������
	USART_SendData(USARTx, ch);//��ch�е����ݷ��͵�����	
	return ch;
}
/****************************************************
��������USART1_Echo
�βΣ���
����ֵ����
�������ܣ�����1�Ļ��Թ���  ���Ը������巢�����ݣ��������ٰѽ��յ������ݷ��ظ�����
****************************************************/
void USART1_Echo()
{
	u8 ch;
	static u8 USART1_RX_NUM=0; //�������������±�
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
	//�ȴ���������
	
	ch = USART_ReceiveData(USART1);//�ѽ��յ������ݱ��浽ch��
	
	if(USART1_RX_NUM >20)
	{
		 USART1_RX_NUM =0;
		 printf("���������");
	 }
	if(ch == '*')
	{
		USART1_RX_NUM=0;//�յ���ʼ�źš�*��ʱ���±�ֵΪ0
	}
	else if(ch =='#')
	{
		USART1_RX_BUF[USART1_RX_NUM] = '\0';//һ֡�źŽ���,������\0
		USART1_RX_OK =1;//����һ֡�ź����յ�
	}
	else
	{
		USART1_RX_BUF[USART1_RX_NUM++] = ch;//�����յ������ݰ�˳������USART1_RX_NUM��
	}
	
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȴ��ϴη������ݷ������
	
	USART_SendData(USART1, ch);//��ch�е����ݷ��͵�����	
}













