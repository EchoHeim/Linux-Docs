//将一个外部函数申明为类的友元函数
#include <cmath>	//使用计算平方根的函数sqrt要用到的头文件
#include <iostream>
using namespace std;

class Point										//Point类定义
{
private:
	int x, y;
	friend float dis(Point &p1, Point & p2);	//友元函数的声明，声明位置没有关系，可以是public，也可是private
public:
	Point(int i = 0, int j = 0)					//构造函数，带缺省参数值
	{
		x = i;
		y = j;
	}	
	void disp()									//成员函数
	{
		cout << "(" << x << "," << y << ")";
	}
};
float dis(Point & p1, Point & p2)			//友元函数的实现
{
	//友元函数中可访问类的private成员
	float d = sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
	return d;
}
int main()
{
	Point p1(1, 2), p2(4, 5);				//声明两个Point类的对象p1和p2
	p1.disp();								//显示点p1的信息
	
	cout << "与";
	p2.disp();								//显示点p2的信息
	
	cout << "距离=" << dis(p1, p2) << endl;	//利用友元函数计算两点举例
	
	return 0;
}

