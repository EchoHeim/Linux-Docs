//将Line类的成员函数dis()作为Point类的友元函数
#include <cmath>			//使用计算平方根的函数sqrt要用到的头文件
#include<iostream>
#include <cmath>
using namespace std;

class Point;				//声明Point类

class Line					//定义Line类(此处注意，必须先声明这个类的函数)
{
public:
	float dis(Point& p1, Point& p2); //友元函数的原型，作为Line类的成员函数
};
class Point					//定义Point类
{
private:
	int x,y;				//private型数据成员x和y
	friend float Line::dis(Point &p1, Point &p2);	//友元的声明
public:
	Point(int i = 0, int j = 0)	//Point类的构造函数，带缺省参数
	{
		x = i;
		y = j;
	}
	void disp()				//成员函数disp()，用来输出点的信息
	{
		cout << "(" << x << "," << y << ")";
	}
};

//Line类内成员函数dis的实现，作为Point类的友元函数（必须在类外进行，且必须在Point类的定义之后。因为其参数中包含了Point这种类型）
float Line::dis(Point &p1, Point &p2)
{
	float d = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	//可访问Point类对象的private成员

	return d;
}

int main()
{
	Line line1;					//声明一个Line类的对象line1
	Point p1(1,2), p2(4,5);		//声明两个Point类的对象p1和p2

	p1.disp();					//输出点p1的信息 
	cout << " 与 "; 
	p2.disp();					//输出点p2的信息

	cout << " 的距离 = " << line1.dis(p1, p2) << endl;
	//通过调用line1的成员函数dis计算两个点间的距离

	return 0;
}

