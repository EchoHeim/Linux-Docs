#include <iostream>
using namespace std;

//类的构造函数使用初始化表达式

//定义类
class Point{
	int xPos;
	int yPos;
public:
	Point(int x,int y); 
	~Point();    //析构函数的声明
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//实现类  进一步实现类的成员函数
Point::Point(int x,int y):xPos(x),yPos(y)
{ 
	cout<<"构造函数 传入参数: int,int "<<endl;
//	xPos = 0;yPos = 0;
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
	Point point1[2] = {Point(10,20),Point(11,21)};
	Point point1[5] = {Point(10,20),Point(11,21)};
	Point * p1 = new Point(100,200);
	p1->print();
	delete p1;
	point1[0].print();
	point1[1].print();
	cout<<"test"<<endl;
	return 0;
}