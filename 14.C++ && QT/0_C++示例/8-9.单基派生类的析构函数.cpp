//派生类的析构函数
#include <iostream>
using namespace std;

class A					//A类的定义
{
private:				//private成员列表
	int x;	
public:					//public成员列表
	A(int xp = 0)		//构造函数，带缺省参数
	{
		x = xp;
		cout << "A的构造函数被执行" << endl;
	}
	~A()				//析构函数
	{
		cout << "A的析构函数被执行" << endl;
	}
};
class B					//B类的定义
{
public:					//public成员列表
	B()					//无参构造函数
	{
		cout << "B的构造函数被执行" << endl;
	}
	~B()				//析构函数
	{
		cout << "B的析构函数被执行" << endl;
	}
};
class C:public A		//类C由类A派生而来
{
private:
	int y;	
	B b;				//对象成员
public:
	C(int xp, int yp):A(xp), b()	//派生类的构造函数，基类和对象成员都在初始化表中完成初始化
	{
		y = yp;
		cout << "C的构造函数被执行" << endl;
	}
	~C()				//析构函数
	{
		cout << "C的析构函数被执行" << endl;
	}
};

int main()
{
	C c(1, 2);			//声明一个C类对象c
	return 0;			//main函数执行完毕，c撤销，析构函数触发执行
}

