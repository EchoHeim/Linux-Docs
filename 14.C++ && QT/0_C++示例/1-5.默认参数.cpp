#include <iostream>
using namespace std;

//������Ĭ�ϲ���
//�����һ���β�����Ĭ�ϲ�����������β��ұ����еĲ�����Ҫ����Ĭ�ϲ���
void func(int num1,int num2 = 10,char ch = '*');

int main()
{
	func(10,100,'&');
	func(10,100);
	func(10);
	//func();    //������Ϊ��һ��û��Ĭ�ϵĲ���
	return 0;
}

void func(int num1,int num2,char ch)
{
	printf("num1 = %d\n",num1);
	printf("num2 = %d\n",num2);
	printf("ch   = %c\n",ch);
	printf("\r\n");
}