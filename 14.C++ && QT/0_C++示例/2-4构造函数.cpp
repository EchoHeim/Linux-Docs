#include <iostream>
using namespace std;

//定义类
class Point{
	int xPos;
	int yPos;
public:
	Point(int x,int y);    //声明构造函数
	void print(void);
	void SetXpos(int x);
	void SetYpos(int y);
};
//实现类  进一步实现类的成员函数
//类的构造函数支持传递参数
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
	point1.print();
	return 0;
}