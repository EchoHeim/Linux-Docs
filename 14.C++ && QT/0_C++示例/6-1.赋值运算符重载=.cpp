//赋值运算符重载
#include <iostream>
#include <cstring>
using namespace std;

class computer
{
private:
	char *brand;						//字符指针brand
	float price;
public:
	computer()							//无参构造函数
	{
		brand = NULL;					//brand初始化为NULL
		price = 0;
		cout << "无参构造函数被调用" << endl;
	}
	computer(const char* sz,float p)
	{
		brand = new char[strlen(sz)+1];	//构造函数中为brand分配一块动态内存
		strcpy(brand, sz);				//字符串复制
		price = p;
		cout << "带参构造函数被调用" << endl;
	}
	computer(const computer& cp)		//复制构造函数
	{
		brand = new char[strlen(cp.brand) + 1];	//为brand分配动态内存
		strcpy(brand, cp.brand);		//字符串复制
		price = cp.price;
		cout << "复制构造函数被调用" << endl;
	}

//	//如果我们没有重载=，则系统会隐式的重载成如下形式:
//	computer &operator=(const computer &cp)
//	{
//		price = cp.price;
//		brand = cp.brand;
//		cout<<"系统默认赋值函数被调用"<<endl;
//		return (*this);
//	}
//
//应该使用下述函数取代上述系统隐式的定义
	computer &operator=(const computer &cp)		//成员函数形式重载赋值运算符
	{
		if (this==&cp)			//首先判断是否是自赋值，是的话返回当前对象
			return  (*this);

		price=cp.price;			//如果不是自赋值，先对price赋值
		delete[] brand;			//防止内存泄露，先释放brand指向的内容
		brand=new char[strlen(cp.brand)+1];		//为brand重新开辟一块内存空间
		if (brand!=NULL)			//如果开辟成功
		{
			strcpy(brand,cp.brand);		//复制字符串
		}
		cout<<"赋值运算符重载函数被调用"<<endl;

		return  (*this);										//返回当前对象的引用，为的是实现链式赋值
	}
	~computer()				//析构函数，释放动态内存，delete[] NULL不会出错
	{
		delete[] brand;
		cout << "析构函数被调用" << endl;
	}
	void print()						//成员函数，输出信息
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

int main()
{
	computer com1("Dell", 2000);	//调用含参构造函数声明对象com1
	computer com2 = com1;			//调用复制构造函数(注意和赋值运算符重载的区别)

	computer com3;				    //调用无参构造函数
	com3 = com1;				    //调用赋值运算符重载函数

	return 0;
}

