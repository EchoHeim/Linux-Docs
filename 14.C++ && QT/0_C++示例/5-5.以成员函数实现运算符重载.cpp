//成员函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex					//定义复数类 complex
{
private:
	double real, imag;			//private 成员，分别代表实部和虚部
public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}
	complex operator+= (const complex &);	//成员函数形式重载加+=

	complex operator+(const complex &);	//成员函数形式重载加+
	complex operator-(const complex &);	//成员函数形式重载减－
	complex operator-();					//成员函数形式重载一元－（取反）
	complex operator*(const complex &);	//成员函数形式重载乘*
	complex operator/(const complex &);	//成员函数形式重载除*

	complex & operator++();					//成员函数形式重载前置++
	complex operator++(int);				//成员函数形式重载后置++

	void disp()								//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex complex::operator+=(const complex& CC)		//加+=的实现
{
	real += CC.real;
	imag += CC.imag;
	return (*this);
}

complex complex::operator+(const complex& CC)		//加+的实现
{
	return complex(real + CC.real, imag + CC.imag);
}

complex complex::operator-(const complex& CC)		//减-的实现
{
	return complex(real - CC.real, imag - CC.imag);
}

complex complex::operator*(const complex& CC)		//乘*的实现
{
	return complex(real * CC.real - imag * CC.imag, real * CC.imag + imag * CC.real);
}

complex complex::operator/(const complex& CC)		//除/的实现
{
	return complex((real * CC.real + imag + CC.imag) / (CC.real * CC.real + CC.imag * CC.imag),
		(imag * CC.real - real * CC.imag) / (CC.real * CC.real + CC.imag * CC.imag));
}

complex complex::operator-()						//单目-，即取反的实现
{
	return complex(-real, -imag);
}

complex& complex::operator++()						//前置++的实现
{
	cout << "前置++" << endl;
	++real;
	++imag;
	return (*this);
}

complex complex::operator++(int)					//后置++的实现，体会和前置++的区别
{
	cout << "后置++" << endl;
	complex cTemp = (*this);	//最终的返回值的是原来的值，因此需要先保存原来的值
	++(*this);					//返回后原来的值需要加1
	return cTemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes += cx2;		//相当于cxRes.operator+=(cx2)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//相当于cx1.operator+(cx2)
	cxRes.disp();
	
	cxRes = cx1 - cx2;	//相当于cx1.operator-(cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//相当于cx1.operator*(cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//相当于cx1.operator/(cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//相当于cx1.operator-()
	cxRes.disp();
	
	cout << endl;
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//相当于cx3.operator++()
	cxRes.disp();
	cx3.disp();

	cout << endl;
	
	cxRes = cx4++;		//相当于cx4.operator++(0)
	cxRes.disp();
	cx4.disp();

	cout << endl;
	
	//注意下述语句在友元函数形式和成员函数形式中的对比。
	cxRes = cx1 + 5;	//相当于cx1.operator+(5) 或 cx1.operator+(complex(5))
	cxRes.disp();

//	cxRes = 5 + cx1;	//错误. 相当于5.operator+(cx1);
//	cxRes.disp();

	return 0;
}

