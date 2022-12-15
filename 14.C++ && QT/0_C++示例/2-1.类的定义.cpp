#include <iostream>
using namespace std;

//定义类
//类的定义中默认是private
class Point{
	int xPos;
	int yPos;
public:
	void print(void)
	{
		cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
	}
};

//使用类
Point point1;   //定义类的变量（类的对象）

int main()
{
	point1.xPos = 100;
	point1.yPos = 200;
	point1.print();
	return 0;
}