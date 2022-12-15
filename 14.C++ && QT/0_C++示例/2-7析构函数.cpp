#include <iostream>
#include <cstring>
using namespace std;
class computer
{
private:
	char * brand; //指针成员
	float price;
public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) + 1]; //对象创建时为brand分配一块动态内存
		strcpy(brand, sz); //字符串复制
		price = p;
	}
	~computer()
	{
		delete[] brand; //对象别撤销时，释放内存，避免泄露
		brand = NULL;
		cout << "清理现场" << endl;
	}
	void print() //信息输出
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

int main()
{
	computer comp("Dell", 7000); //调用构造函数声明computer变量comp
	comp.print(); //信息输出

	return 0;
}
