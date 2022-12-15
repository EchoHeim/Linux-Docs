//对操作符>>的重载
#include <iostream>
using namespace std;

//http://blog.csdn.net/mzlogin/archive/2009/04/19/5177784.aspx
//解决VC6.0中友元方式重载运算符时无法访问类私有成员的方法：
//		在类定义之前将类和友元操作符函数的原型提前声明一下.
class Complex;
ostream & operator<<(ostream &os, Complex &C1); //对操作符<<的重载
istream & operator>>(istream &is, Complex &C1);

class Complex
{
private:
	double imag;		//虚部
	double real;		//实部
public:
	Complex(double r=0.0,double i=0.0)			//构造函数
	{
		real=r;
		imag=i;
	}
	friend ostream& operator<<(ostream& ,Complex& );		//友元函数声明
	friend istream& operator>>(istream& ,Complex& );
};

ostream& operator<<(ostream& os,Complex& C1)			//对操作符<<的重载
{
	os<<C1.real<<"+i*"<<C1.imag<<endl;
	return os;
}

istream& operator>>(istream& is,Complex& C1)			//对操作符>>的重载
{
	is>>C1.real;            //先输入实部
	while (is.get()!='*')     
	{
	}
	cin>>C1.imag;
	return is;
}

int main()
{
	Complex c1(2.5,3.1);
	cin>>c1;
	cout<<c1;
	return 0;
}

