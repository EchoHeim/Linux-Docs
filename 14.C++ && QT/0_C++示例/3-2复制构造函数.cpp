#include <iostream>
#include <cstring>
using namespace std;

class computer
{
private:
	char * brand;
	float price;
public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) + 1];
		strcpy(brand, sz);
		price = p;
	}
	computer(const computer & comp)  //显示定义复制构造函数
	{
		brand = new char[strlen(comp.brand)+1]; //动态开辟内存
		strcpy(brand,comp.brand); //复制内容
		price = comp.price;
	}
	~computer()
	{
		delete[] brand;
		cout << "清理现场" << endl;
	}
	void print()
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

int main()
{
	computer comp1("Dell", 7000);//调用有参构造函数声明computer类对象comp1，并初始化
	comp1.print();
	computer comp2(comp1);       //调用复制构造函数声明computer类对象comp2，并用comp1为其初始化
	comp2.print();
	return 0;
}
