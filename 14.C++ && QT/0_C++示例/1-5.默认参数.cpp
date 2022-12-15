#include <iostream>
using namespace std;

//函数的默认参数
//如果给一个形参设置默认参数，则这个形参右边所有的参数都要设置默认参数
void func(int num1,int num2 = 10,char ch = '*');

int main()
{
	func(10,100,'&');
	func(10,100);
	func(10);
	//func();    //错误，因为第一个没有默认的参数
	return 0;
}

void func(int num1,int num2,char ch)
{
	printf("num1 = %d\n",num1);
	printf("num2 = %d\n",num2);
	printf("ch   = %c\n",ch);
	printf("\r\n");
}