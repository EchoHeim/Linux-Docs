//使用虚基类解决共同基类带来的二义性问题
#include <iostream>
using namespace std;

class A				//公共虚基类A
{
protected:			//protected成员列表
	int x;
public:
	A(int xp = 0)		//构造函数，带缺省构造参数
	{
		x=xp;
	}
	void SetX(int xp)//SetX函数用以设置protected成员x
	{
		x = xp;
	}
	void print()	//print函数输出信息
	{
		cout << "this is x in A: " << x << endl;
	}
};
class B: virtual public A	//B由A虚基派生而来
{
};
class C: virtual public A	//C由A虚基派生而来
{
};
class D:public B,public C	//D由B和C共同派生
{
};
int main()
{
	D d;			//声明一个D类对象exD

	d.SetX(5);		//SetX函数，因为virtual派生，在D中只有一个版本，不会二义
	d.print();		//print函数，因为virtual派生，在D中只有一个版本，不会二义

	d.A::print();	//还可用类名显式说明调用函数的版本
	d.B::print();
	d.C::print();

	return 0;
}

