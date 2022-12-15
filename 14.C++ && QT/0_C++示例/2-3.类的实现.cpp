#include <iostream>
using namespace std;

//定义类
//类的定义中默认是private
class Point{
	int xPos;
	int yPos;
public:
	void print(void);
	void SetXpos(int x);
	void SetYpos(int y);
};
//实现类  进一步实现类的成员函数
void Point::print(void)
{
	cout<<"xPos = "<<this->xPos<<", yPos = "<<this->yPos<<endl;
}
void Point::SetXpos(int x)
{	
	this->xPos = x; 
}
void Point::SetYpos(int y)
{	
	this->yPos = y; 
}

//成员变量占据不同的内存区域;
//成员函数共用同一内存区域(代码段)
//所有类的对象公用类的成员函数，
//依靠this指针来区别是哪个类的对象调用成员函数

int main()
{
	//使用类
	Point point1;   //定义类的变量（类的对象）
	Point point2;
	point1.SetXpos(100);
	point1.SetYpos(100);
	point2.SetXpos(200);
	point2.SetYpos(200);
	point1.print();
	point2.print();

	return 0;
}