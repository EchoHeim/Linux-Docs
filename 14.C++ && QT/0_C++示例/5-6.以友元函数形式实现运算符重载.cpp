//友员函数形式 的 运算符重载
#include <iostream.h>
//using namespace std;

class complex							//定义复数类complex
{
private:
	double real,imag;					//private成员，分别代表实部和虚部

public:
	complex(double r=0.0,double i=0.0)	//构造函数，带缺省参数值
	{
		real=r;
		imag=i;
	}
	void disp()														//成员函数，输出复数
	{
		cout<<real<<" + "<<"i*"<<imag<<endl;
	}

	friend complex operator + (const complex & C1,const complex & C2);	//友元函数形式重载加+
	friend complex operator - (const complex &,const complex &);	//友元函数形式重载减－
	friend complex operator - (const complex &);					//友元函数形式重载一元－（取反）
	friend complex operator * (const complex &,const complex &);	//友元函数形式重载乘*
	friend complex operator / (const complex &,const complex &);	//友元函数形式重载除*
	friend complex & operator ++(complex &);							//友元函数形式重载前置++
	friend complex operator ++(complex &,int);						//友元函数形式重载后置++
};

complex operator+ (const complex& C1,const complex& C2)		//加+的实现
{
	return complex(C1.real + C2.real, C1.imag + C2.imag);
}

complex operator- (const complex& C1,const complex& C2)		//减-的实现
{
	return complex(C1.real - C2.real, C1.imag - C2.imag);
}

complex operator- (const complex& C1)						//单目-，即取反的实现
{
	return complex(-C1.real, -C1.imag);
}

complex operator *(const complex& C1,const complex& C2)		//乘*的实现
{
	return complex(C1.real * C2.real - C1.imag * C2.imag, C1.real * C2.imag + C1.imag * C2.real);
}

complex operator /(const complex& C1,const complex& C2)		//除*的实现
{
	return complex((C1.real * C2.real + C1.imag + C2.imag) / (C2.real * C2.real + C2.imag * C2.imag),
		(C1.imag * C2.real - C1.real * C2.imag) / (C2.real * C2.real + C2.imag * C2.imag));
}

complex & operator ++(complex& C1)		//前置++的实现
{
	cout << "前置++" << endl;
	C1.real += 1;
	C1.imag += 1;
	return C1;
}

complex operator ++(complex& C1,int)	//后置++的实现，体会和前置++的区别
{
	cout << "后置++" << endl;
	complex ctemp = C1;
	++C1;
	return ctemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;
	
	cxRes = cx1 - cx2;	//相当于operator-(cx1, cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//相当于operator-(cx1)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//相当于operator+(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//相当于operator*(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//相当于operator/(cx1, cx2)
	cxRes.disp();
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//相当于operator++(cx3)
	cxRes.disp();
	cx3.disp();
	
	cxRes = cx4++;		//相当于operator++(cx4, 0)
	cxRes.disp();
	cx4.disp();
	
	//注意下述语句在友元函数形式和成员函数形式的对比。
	cxRes = cx1 + 5;	//相当于operator+(cx1, 5);
	cxRes.disp();

	cxRes = 5 + cx1;	//相当于operator+(5, cx1);
	cxRes.disp();

	return 0;
}
