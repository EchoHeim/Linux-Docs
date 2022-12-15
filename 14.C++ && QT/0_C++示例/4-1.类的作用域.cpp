//变量的作用域
#include <iostream>
using namespace std;

int x = 100; //定义性声明，全局int型变量x
int z = 200; //定义性声明，全局int型变量z

class Example //Example类定义
{
	int x; //默认为private的成员列表
	int y;
public:
	Example(int xp = 0, int yp = 0) //构造函数
	{
		x = xp;
		y = yp;
	}
	void print(int x) //成员函数print，形参为x
	{
		cout << "传递来的参数:  " << x << endl; //形参x覆盖掉了成员x和全局变量x
		cout << "成员x:  " << (this->x) << ", 成员y:  " << y << endl;//此处的y指的是成员y，如果要访问成员x，可使用this指针
		cout << "除了this指针外，还可以使用类名::的形式：" << endl;
		cout << "成员x:  " << Example::x << ", 成员y:  " << y << endl;//或使用类名加作用域限定符的形式指明要访问成员x
		cout << "全局x:  " << (::x) << endl; //访问全局变量x
		cout <<"全局z:   "<< z << endl;      //没有形参和数据成员会对全局变量z构成屏蔽，直接访问z即可
	}
};

int main()
{
	Example ex1; //声明一个Example类的对象ex1
	ex1.print(5); //调用成员函数print()
	return 0;
}

