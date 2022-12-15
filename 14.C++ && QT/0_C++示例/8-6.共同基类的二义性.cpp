//共同基类带来的二义性
#include <iostream>
using namespace std;

class A					        //公共基类
{
protected:				        //protected成员列表
	int x;
public:					        //public成员列表
	A(int xp = 0)		        //构造函数
	{
		x = xp;
	}
	void SetX(int xp)	        //设置protected成员x的值
	{
		x = xp;
	}
	void print()
	{
		cout << "this is x in A: " << x << endl;
	}
};
class B: public A		        //类B由类A派生而来
{
};
class C: public A		        //类C由类A派生而来
{
};
class D : public B, public C	//类D由类B和类C派生而来
{
};

int main()
{
	D d;			//声明一个D类对象exD
	d.SetX(5);		//SetX()具有二义性, 系统不知道是调用B类的还是C类的SetX()函数
	d.print();		//print()具有二义性, 系统不知道是调用B类的还是C类的print()函数
	return 0;
}

