//友元类
#include<iostream>
#include <cmath>
using namespace std;

class CLine;				//声明类CLine

class CPoint //定义CPoint类
{
private:
	int x, y;
	friend CLine; //友元类的声明，位置同样不受限制	
public:
	CPoint(int i = 0, int j = 0) //构造函数，带缺省参数值
	{
		x = i;
		y = j;
	}	
	void disp() //成员函数，输出点的信息
	{
		cout << "(" << x << "," << y << ")";
	}
};
class CLine				//类CLine的定义，其中所有的函数都是CPoint类的友元函数
{
public:
	float dis(CPoint& p1,CPoint& p2)		//可访问p1和p2的private成员
	{
		float d;
		d=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
		return d;
	}
	void Set(CPoint* p1,int a,int b)		//可访问p1和p2的private成员
	{
		p1->x=a;
		p1->y=b;
	}
};

int main()
{
	CLine cz1;			    //声明一个CLine类的对象cz1
	CPoint p1(1,2),p2(4,5);	//声明两个CPoint类对象p1和p2

	p1.disp();				//输出点p1的信息 
	cout<<"与";
	p2.disp();				//输出点p2的信息
	cout<<"距离="<<cz1.dis(p1,p2)<<endl;//调用cz1的成员函数dis计算两点间距

	cz1.Set(&p1,3,4);		//调用cz1的成员函数Set改写p1中的private成员x和y
	p1.disp();				//修改后的点p1信息输出

	cout<<endl;				//换行

	return 0;
}

