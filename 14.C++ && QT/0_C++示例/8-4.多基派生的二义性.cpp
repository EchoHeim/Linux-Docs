//多基类继承时的二义性问题
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
		print();	//编译器无法决定采用A类中定义的版本还是B类中的版本
	}
};

int main()
{
	C c;
	c.disp();		//派生类内访问对象成员的二义性
	c.print();		//外部通过派生类对象访问基类成员的二义性
	return 0;
}

