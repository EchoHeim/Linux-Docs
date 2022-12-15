//由其他类型转换到自定义类型
#include <iostream>
using namespace std;

class point;                                  //声明

class anotherPoint                            //anotherPoint类定义
{
private:                                      //private成员列表
	double x;
	double y;
public:
	anotherPoint(double xx = 1, double yy = 1) //构造函数，带缺省参数值
	{
		x = xx;
		y = yy;
	}
	void print()			//输出函数，点的信息
	{
		cout << "( " << x << " , " << y << " )";
	}
	friend class point;		//使point类成为本类的友元类, 这样point
							//类就可以访问anotherPoint 类的private变量了
};

class point		//point类定义
{
private:		//private成员列表
	int xPos;
	int yPos;
public:
//	explicit //如果在构造函数前加上explicit, 就不允许 point pt1 = 5这种隐式转换了
	point(int x = 0, int y = 0)	//构造函数，带缺省参数，两个int型变量
	{
		xPos = x;
		yPos = y;
	}
	point(anotherPoint aP)		//构造函数，参数为anotherPoint类对象
	{
		xPos = aP.x;			//由于point类是anotherPoint类的友元类,
		yPos = aP.y;			//因此这里可以访问anotherPoint的私有变量x和y
	}
	void print()				//输出函数，点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
};

int main()
{
	//1. 将int类型数字5转换成point类型
	point p1;			//创建point类对象p1，采用带缺省参数的构造函数，即x＝0、y＝0
	cout << 5 << " 转换成 ";
	p1 = 5;				//等价于p1＝point(5,0);
	p1.print();			//输出点p1的信息
	
	//2. 将double类型变量dX转换成point类型
	double dX = 1.2;	//声明一个double变量dX
	cout << dX << " 转换成 ";
	p1 = dX;			//等价于p1=point(int(dX),0)
	p1.print();			//输出点p1的信息
	
	//3. 将anotherPoint类型转换成point类型
	anotherPoint p2(12.34, 56.78);	//创建anotherPoint类的对象p2
	p2.print();
	cout << " 转换成 ";
	p1 = p2;			//等价于p1=point(p2);
	p1.print();			//输出点p1的信息

	//4. 测试在point构造函数前加上explicit以阻止隐性转换的情况
	
	return 0;
}

