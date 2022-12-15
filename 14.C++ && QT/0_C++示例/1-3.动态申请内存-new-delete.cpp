#include <iostream>
using namespace std;

struct TEST
{
	char name[20];
	int age;
};

int main()
{
	int * p1 = new int;
	TEST * p2 = new TEST;
	char * p3 = new char[100];

	cin>>p2->name>>p2->age>>p3;
	*p1 = 100;
	cout<<"*p1 = "<<*p1<<endl;
	cout<<p2->name<<"  "<<p2->age<<endl;
	cout<<"p3 : "<<p3<<endl;
	delete p1;
	delete p2;
	delete[] p3;
	return 0;
}
