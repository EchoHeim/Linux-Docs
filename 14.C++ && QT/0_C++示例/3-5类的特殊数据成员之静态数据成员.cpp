#include <iostream>
using namespace std;

//测试静态数据成员

class computer
{
private:
	float price; //float型数据成员price，表示价格
	static float total_price; //statci成员，总价，不依附于某个对象
public:
	computer(const float p) //构造函数，模拟买电脑的操作，对total_price进行累加	
	{
		price = p;
		total_price += p;
	}
	~computer() //析构函数，模拟退还电脑的操作，从total_price中减去所退电脑的price
	{
		total_price -= price;
	}
	void print() //输出函数
	{
		cout << "总价：" << total_price << endl;
	}
};
float computer::total_price = 0;//初始化类的静态成员成员


int main()
{
	computer comp1(7000); //买入电脑1
	cout << "购买电脑1后" << endl;
	comp1.print();
	computer comp2(4999); //买入电脑2
	cout << "购买电脑2后" << endl;
	comp2.print();
	computer comp3(2500); //买入电脑3
	cout << "购买电脑3后" << endl;
	comp1.print(); //此处调用comp1.print()、comp2.print()和comp3.print()输出结果相同
	comp2.~computer(); //退掉电脑2
	cout << "退掉电脑2后" << endl;
	comp3.print();
/*	computer::total_price = 1000;
	cout<<"total = "<<computer::total_price<<endl;
	cout<<"total = "<<comp1.total_price<<endl; */
	return 0;
}

