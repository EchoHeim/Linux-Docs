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
	cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
}
void Point::SetXpos(int x)
{	
	xPos = x; 
}
void Point::SetYpos(int y)
{	
	yPos = y; 
}



int main()
{
	//使用类
	Point point1;   //定义类的变量（类的对象）
//	point1.xPos = 100;
//	point1.yPos = 200;
	point1.SetXpos(100);
	point1.SetYpos(100);
	point1.print();
	return 0;
}