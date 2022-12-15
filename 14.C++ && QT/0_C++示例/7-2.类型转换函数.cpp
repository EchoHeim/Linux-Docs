//类型转换函数(由类转换成其他类型)
#include <iostream>
using namespace std;

class anotherPoint					//anotherPoint类定义
{
private:							//private成员列表
	double x;
	double y;
public:
	anotherPoint(double xx = 1.11, double yy = 1.11)//构造函数，带缺省参数值
	{
		x = xx;
		y = yy;
	}
	void print()					//成员函数，输出点的信息
	{
		cout << "( " << x << " , " << y << " )" << endl;
	}
};
class point							//Point类定义
{
private:							//private成员列表
	int xPos;
	int yPos;
public:
	point(int x = 0, int y = 0)		//构造函数，带缺省参数值
	{
		xPos = x;
		yPos = y;
	}
	void print()					//成员函数，输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	operator int()					//定义Point向int型的转换函数int()
	{
		return xPos;
	}
	operator double()				//定义Point向double型的转换函数double()
	{
		return xPos * yPos;
	}
	operator anotherPoint()			//定义Point向anotherPoint型的转换函数anotherPoint()
	{
		return anotherPoint(xPos, yPos);
	}
};
int main()
{
	point p1(4, 5);			//声明一个point类变量p1
	p1.print();

	//1. point转换成int
	int x1 = p1;			//p1赋值给一个int型变量，point中的转换函数int()被隐式调用
	cout << x1 << endl;

	//2. point转换成double
	double dX = p1;			//p1赋值给一个double型变量，point中的转换函数double()被隐式调用
	cout << dX << endl;

	//3. point转换成anotherPoint
	anotherPoint p2;		//声明anotherPoint类对象p2，构造函数采用缺省值
	p2 = p1;				//p1赋值给p2，point中的转换函数anotherPoint()被隐式调用
							//等价于p2＝another(p1.xPos,p1.yPos)
	p2.print();				//看p2是否修改成功

	return 0;
}
