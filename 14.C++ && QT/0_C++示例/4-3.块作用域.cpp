//块作用域
#include <iostream>
using namespace std;

void Work(int a, int b)
{
	class point				//类定义在函数内，在函数外无法使用point创建对象
	{
	private:
		int x, y;
	public:
		point(int xp = 0, int yp = 0)
		{
			x = xp;
			y = yp;
		}
		void print()
		{
			cout << x << "," << y << endl;
		}
	};

	point pt(a, b);	//函数内，创建point类的对象pt
	pt.print();		//输出提示信息
}
int main()
{
	Work(5, 6);				//work函数调用
	return 0;
}

