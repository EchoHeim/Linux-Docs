//public, protected, private派生方式
#include <iostream>
using namespace std;

class point		                       //point类定义
{
private:		                       //private成员列表，表示点的坐标信息
	int xPos;
	int yPos;	
public:
	point(int x = 0, int y = 0)	       //构造函数，带缺省参数
	{
		xPos = x;
		yPos = y;
	}	
	void disp()		                  //成员disp函数，用来输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}	
	int GetX()		                  //读取private成员xPos
	{
		return xPos;
	}	
	int GetY()		                 //读取private成员yPos
	{
		return yPos;
	}
};

class point3D : public point	    //3维点类point3D，从point类继承而来，注意格式
{
private:
	int zPos;				        //在point类基础上增加了zPos坐标信息
public:
	point3D(int x, int y, int z):point(x, y)//派生类构造函数，初始化表中调用基类构造函数
	{
		zPos = z;
	}	
	void disp()				       //隐藏了基类的中的同名disp函数
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}	
	int calcSum()			       //增添了计算3个数据成员和的函数
	{
		return GetX() + GetY() + zPos;
	}
};

int main()
{
	//自己动手, 分别使用public, protected和private派生point3D类,
	//则在public派生方式时下列访问派生类的GetX()不会出错,
	//但protected和private派生方式时就会编译报错.
	point3D pt(3, 4, 5);
	cout<<pt.GetX()<<endl;		//!!!!!!

	//disp()在3种方式下都可访问, 因为disp()在Point3D类中被覆盖成public类型了
	pt.disp();

	//calcSum()在3种方式下都可访问, 因为它是在Point3D类中新定义的public成员函数
	pt.calcSum();

	return 0;
}

