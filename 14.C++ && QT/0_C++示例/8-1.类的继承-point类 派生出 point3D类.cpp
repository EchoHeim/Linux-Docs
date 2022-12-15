//继承与派生的概念 由point类 派生出 point3D类
#include <iostream>
using namespace std;

class point		                         //point类定义
{
private:		                         //private成员列表，表示点的坐标信息
	int xPos;
	int yPos;	
public:
	point(int x = 0, int y = 0)	         //构造函数，带缺省参数
	{
		xPos = x;
		yPos = y;
	}	
	void disp()	                    	 //成员disp函数，用来输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	int GetX()		                    //读取private成员xPos
	{
		return xPos;
	}	
	int GetY()		                   //读取private成员yPos
	{
		return yPos;
	}
};
class point3D:public point	          //3维点类point3D，从point类继承而来
{
private:
	int zPos;				          //在point类基础上增加了zPos坐标信息	
public:
	point3D(int x, int y, int z):point(x, y)//派生类构造函数，初始化表中调用基类构造函数
	{
		zPos = z;
	}	
	void disp()				         //隐藏了基类的中的同名disp函数
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}	
	int calcSum()			         //增添了计算3个数据成员和的函数
	{
		return GetX() + GetY() + zPos;
	}
};
int main()
{
	point pt1(7, 8);			//建立point类对象pt1
	pt1.disp();					//显示pt1的信息

	point3D pt2(3, 4, 5);		//建立point3D类对象pt2
	pt2.disp();					//显示pt2的信息

	int res = pt2.calcSum();	//计算pt2中3个坐标信息的加和
	cout << res << endl;		//输出结果

	return 0;
}

