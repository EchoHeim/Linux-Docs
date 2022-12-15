#include <iostream>
using namespace std;

//类的特殊数据成员之const成员 引用成员

//定义类
class Point{
	const int xPos;
	const int yPos;
	int & zPos;
public:
	Point(int & cp,int x = 0,int y = 0); 
	Point(const Point &);
	~Point();   
	void print(void);
};
//实现类  进一步实现类的成员函数
Point::Point(int & cp,int x,int y):xPos(x),yPos(y),zPos(cp)
{ 
	cout<<"构造函数 传入参数: int,int "<<endl;
}

Point::Point(const Point & pt):xPos(pt.xPos),yPos(pt.yPos),zPos(pt.zPos)
{ 
	cout<<"复制构造函数 传入参数:Point "<<endl;
}
Point::~Point()    //析构函数的实现
{
	cout<<"析构函数被调用"<<endl;
}

void Point::print(void)
{
	cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
	cout<<"zPos = "<<zPos<<endl;
}

int main()
{
	int zPos = 300;
	Point pt1(zPos,100,200);
	pt1.print();
	return 0;
}