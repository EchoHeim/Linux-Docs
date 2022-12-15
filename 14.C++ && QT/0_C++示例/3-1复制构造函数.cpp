#include <iostream>
using namespace std;

//类的复制构造函数

//定义类
class Point{
	int xPos;
	int yPos;
public:
	Point(int x = 0,int y = 0); 
	Point(const Point &);
	~Point();   
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//实现类  进一步实现类的成员函数
Point::Point(int x,int y):xPos(x),yPos(y)
{ 
	cout<<"构造函数 传入参数: int,int "<<endl;
}
Point::Point(const Point & pt):xPos(pt.xPos),yPos(pt.yPos)
{ 
	cout<<"复制构造函数 传入参数:Point "<<endl;
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
	Point pt1(100,200);
//	Point pt2 = pt1; //调用复制构造函数
	Point pt2(pt1);
	pt2.print();
	return 0;
}