#include <iostream>
using namespace std;

struct TEST
{
	char name[20];
	int age;
};

void swap(int & a,int & b)
{
	/*
	int c;
	c = a;
	a = b;
	b = c;*/

	a=a^b;
	b=a^b;
	a=a^b;
}
void swap_p(int * a,int * b)
{	
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void print_test(struct TEST & test)
{
	printf("name: %s\n",test.name);
	printf("age : %d\n",test.age);
}
int main()
{
	int a = 100;
	int & aa = a; 
	aa = 1000;
	printf(" a = %d \n",a);
	printf(" aa = %d \n",aa);
	printf(" add : 0x%x \n",&a);
	printf(" add : 0x%x \n",&aa);

	
	int a = 100,b = 10;
	struct TEST test = {"zhangsan",22};

	printf("a = %d,b = %d\n",a,b);
	swap(a,b);
	printf("swap : a = %d,b = %d\n",a,b);	
	swap_p(&a,&b);
	printf("swap : a = %d,b = %d\n",a,b);

	print_test(test);

	return 0;
}