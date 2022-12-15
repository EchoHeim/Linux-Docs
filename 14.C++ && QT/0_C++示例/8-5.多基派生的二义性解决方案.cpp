//多基类继承时的二义性问题的解决方案, 见代码备注中的1和2
#include <iostream>
using namespace std;

class A				//类A的定义
{
public:
	void print()	//A中定义了print函数
	{
		cout<<"Hello,this is A"<<endl;
	}
};

class B				//类B的定义
{
public:
	void print()	//B中同样定义了print函数
	{
		cout<<"Hello,this is B"<<endl;
	}
};

class C : public A, public B	//类C由类A和类B共同派生而来
{
public:
	void disp()
	{
		A::print();       	   //1. 指明采用A类中定义的版本
	}

	//重载print函数, 根据条件调用不同基类的print函数
	void print()
	{
		if (true)
			A::print();
		else
			B::print();
	}
};

int main()
{
	C c;
	c.disp();		//派生类内访问对象成员的二义性得到解决

	c.A::print();	//2.1 指明采用B类中定义的版本 c.(A::print());
	c.print();		//2.2 在C类中重载print函数

	return 0;
}

