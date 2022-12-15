#include <iostream>
using namespace std;

//类的构造函数支持重载

//定义类
class Point{
	int xPos;
	int yPos;
public:
	Point(void);
	Point(int x);
	Point(int x,int y); 
	~Point();    //析构函数的声明
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//实现类  进一步实现类的成员函数
Point::Point(void)
{ 
	cout<<"测试构造函数重载 传入参数: void"<<endl;
	xPos = 0;yPos = 0;
}
Point::Point(int x)
{ 
	cout<<"测试构造函数重载 传入参数: int "<<endl;
	xPos = x;yPos = x;
}
Point::Point(int x,int y)  //类的构造函数
{ 
	cout<<"测试构造函数重载 传入参数: int,int "<<endl;
	xPos = x;
	yPos = y;
}
Point::~Point()    //析构函数的实现
{
	cout<<"析构函数被调用"<<endl;
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
	Point point3(50);
	point1.print();
	point2.print();
	point3.print();
	return 0;
}