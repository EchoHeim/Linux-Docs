//派生类构造函数的调用顺序
#include <iostream>
using namespace std;

class A					//类A的定义
{
private:				//private成员列表
	int x;
public:
	A(int xp=0)			//构造函数，带缺省参数
	{
		x = xp;
		cout << "A的构造函数被执行" << endl;
	}
};
class B					//类B定义
{
public:
	B()					//无参构造函数
	{
		cout << "B的构造函数被执行" << endl;
	}
};
class C:public A		//类C由类A派生而来
{
private:
	int y;
	B b;
public:
	C(int xp, int yp) : A(xp), b()	//构造函数，基类构造函数在初始化表中调用
	{
		y = yp;
		cout << "C的构造函数被执行" << endl;
	}
};
int main()
{
	C c(1, 2);			//创建C类对象c
	return 0;
}
