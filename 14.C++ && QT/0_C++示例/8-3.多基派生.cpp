//多基派生的声明和定义
#include <iostream>
using namespace std;

class A				                           //类A的定义
{
public:
	void print()	                           //A中定义了print函数
	{
		cout << "Hello,this is A" << endl;
	}
};
class B				                          //类B的定义
{
public:
	void show()		                          //B中定义了show函数
	{
		cout << "Hello,this is B" << endl;
	}
};

class C : public A, public B	              //类C由类A和类B共同派生而来
{
public:
	void disp()
	{
		show();		                         //在类内部基类的成员函数
	}
};

int main()
{
	C c;
	c.print();		//在类外部 通过 派生类对象 访问 基类 成员
	c.disp();		//在类外部 访问 派生类对象 的新添加的成员
	return 0;
}

