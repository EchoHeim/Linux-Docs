#include <iostream>
using namespace std;

//��������
//һ����Ϊdisplay�����غ��� :
//��ͬ����,��ͬ����(��������,����,����˳��)

void display(int num = 0)
{
	printf("����һ������: num = %d\r\n",num);
}
void display(int num,char ch)
{
	printf("������������1: num = %d   ch = %c\n",num,ch);
}
void display(char ch,int num)
{
	printf("��������������2: num = %d   ch = %c\n",num,ch);
}

int main()
{
	display();
	display(1);
	display(2,'*');
	display('@',3);
	return 0;
}

//ע: ����������ʹ�ú�����Ĭ�ϲ��������������������
