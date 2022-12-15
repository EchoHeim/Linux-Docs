#include <iostream>
using namespace std;

class point
{
	int xPos; //默认为private的数据成员x和y
	int yPos;
public:
	point(int x = 0, int y = 0) //构造函数
	{
		xPos = x;
		yPos = y;
	}
	void print() const //const成员函数内无法修改数据成员，否则编译器报错
	{
//		xPos = 5; //1. 试图修改x将引发编译器报错
//		set(); //2. 试图调用非const函数将引发编译器报错
		cout << "x: " << xPos << " ,y: " << yPos << endl;
	}
	void set() //将set()定义成const函数就能解决问题
	{
	}
};

int main()
{
	point pt;		//声明类对象，以缺省参数形式调用构造函数
	pt.print();		//调用const成员函数

	return 0;
}
