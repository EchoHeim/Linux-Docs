#include <iostream>
using namespace std;

//定义类
class Point{
	int xPos;
	int yPos;
public:
	Point(int x = 1,int y = 2);    //声明构造函数，并指定默认参数
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//实现类  进一步实现类的成员函数
//类的构造函数支持默认参数
Point::Point(int x,int y)  //类的构造函数
{ 
	cout<<"构造函数被调用"<<endl;
	xPos = x;
	yPos = y;
}
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

int main()
{
	Point point1(100,200); //()中的内容是给构造函数传递的参数 
	Point point2;
	point1.print();
	point2.print();
	return 0;
}