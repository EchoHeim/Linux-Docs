//重载函数调用运算符()
#include <iostream>
using namespace std;

class Demo		//Demo类定义
{
public:
	double operator()(double x, double y)	      //重载函数调用符(),两个double型参数
	{
		return x > y ? x : y;				      //返回两个参数中较大的一个
	}

	double operator()(double x, double y, double z)//重载函数调用符(),3个double型参数
	{
		return (x + y) * z;						  //将前两个相加，与第3个参数相乘，返回最后的结果
	}
};

void main()
{
	Demo de;											//声明一个类对象（注意和构造函数的区别，构造函数在定义时被调用）
	cout << de(2.5, 0.2) << endl;						//可以将对象像函数一样使用
	cout << de(1.2, 1.5, 7.0) << endl;
}

