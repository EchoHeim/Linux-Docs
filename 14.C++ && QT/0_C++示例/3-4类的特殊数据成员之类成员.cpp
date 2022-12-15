#include <iostream>
using namespace std;

class point //点类的定义
{
private:
	int xPos;
	int yPos;
public:
	point(int x, int y) //带缺省调用的构造函数
	{
		cout << "点的构造函数被执行" << endl;
		xPos = x;
		yPos = y;
	}
	point(const point & pt) //复制构造函数
	{
		cout << "点的复制构造函数被执行" << endl;
		xPos = pt.xPos;
		yPos = pt.yPos;
	}
	~point()
	{
		cout<<"点的析构函数被执行"<<endl;
	}
	void print()
	{
		cout << "( " << xPos << ", " << yPos << ")";
	}
};

class line //line类的定义
{
private:
	point pt1; //point类对象作为line类成员，此处若写成point pt1(3,4)，错
	point pt2;
public:
	line(int x1, int y1, int x2, int y2):pt1(x1,y1),pt2(x2,y2) //line对象的有参构造函数
	{
		cout << "线的构造函数被执行" << endl;
	}
	line(const line &ll):pt1(ll.pt1), pt2(ll.pt2) //line对象的复制构造函数
	{
		cout << "线的复制构造函数被执行" << endl;
	}
	~line()
	{
		cout<<"线的析构函数被执行"<<endl;
	}
	void draw()
	{
		pt1.print();
		cout << "  to  ";
		pt2.print();
		cout << endl;
	}
};

int main()
{
	line l1(1, 2, 3, 4); //调用有参构造函数
	l1.draw();
	line l2(l1); //调用复制构造函数
	l2.draw();
	return 0;
}
