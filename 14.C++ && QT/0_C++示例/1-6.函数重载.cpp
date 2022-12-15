#include <iostream>
using namespace std;

//函数重载
//一组名为display的重载函数 :
//相同名称,不同参数(参数个数,类型,排列顺序)

void display(int num = 0)
{
	printf("调用一个参数: num = %d\r\n",num);
}
void display(int num,char ch)
{
	printf("调用两个参数1: num = %d   ch = %c\n",num,ch);
}
void display(char ch,int num)
{
	printf("调用两个个参数2: num = %d   ch = %c\n",num,ch);
}

int main()
{
	display();
	display(1);
	display(2,'*');
	display('@',3);
	return 0;
}

//注: 函数重载中使用函数的默认参数容易引起二义性问题
