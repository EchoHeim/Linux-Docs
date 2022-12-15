#include <iostream>
using namespace std;

//测试静态成员函数

class computer
{
private:
	char *name;
	float price;
	static float total_price; //静态数据成员
public:
	computer(const char *chr, const float p) //构造函数，模拟买电脑操作
	{
		name = new char[strlen(chr) + 1];
		strcpy(name, chr);
		price = p;
		total_price += p;
	}
	~computer() //析构函数，模拟退掉电脑的操作
	{
		if (name)
		{
			delete[] name;
			name = NULL;
		}
		total_price -= price;
	}
	static void print_total() //静态成员函数，原则上只能访问静态数据成员
	{
		cout << "总价：" << total_price << endl;
	}
	static void print(computer &com); //静态成员函数print()原型，如果要访问某具体对象，必须传递参数
	void print_this(void)
	{
		cout << "名称"  << this->name << endl;
		cout << "价格："<< this->price << endl;	
	}
};
void computer::print(computer & com) //静态成员函数print()实现
{
	print_total();
//	print_this();
	cout << "名称" << com.name << endl;
	cout << "价格" << com.price << endl;
}

float computer::total_price = 0; //初始化

int main()
{
	computer comp1("IBM", 7000); //声明类对象comp1，初始化，买入
	computer::print(comp1); //类名加作用域限定符访问statci成员函数，传递参数comp1
	computer::print_total(); //类名加作用域限定符访问statci成员函数

	computer comp2("ASUS", 4999); //声明类对象comp2，初始化，买入
	computer::print(comp2); //类名加作用域限定符访问statci成员函数，传递参数comp2
	computer::print_total();

	comp2.~computer(); //析构函数调用，退还电脑
	computer::print_total();

	return 0;
}