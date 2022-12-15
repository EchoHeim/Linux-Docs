#include <iostream>
using namespace std;

const int Number = 1,n = 10;      //定义只读变量

int main(void)
{
	int a ;
	const int * p;                //常量指针 （指针p所指向的常量不能修改，但是可以改变指针p的指向）
	p = &Number;
	p = &n;
	//*p = 5;   //错误
	//n = 5;    //错误
                                 
	int n1 = 3;                   
	int const n2 = 5;             //注意（int const  、const int的写法是一样的）
	int * const pn = &n1;         //指针常量（指针pn所指向的变量是可以更新的，不可更新的是指针pn所指向的方向）
	//pn = &n2;   //错误
	//n2 = 6;     //错误
	*pn = 6;
	
	cout<<"n = "<<n<<endl;
	cout<<"n1 = "<<n1<<endl;
	return 0;
}
