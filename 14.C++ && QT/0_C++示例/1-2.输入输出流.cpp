#include <iostream>
using namespace std;

struct TEST
{
	char name[20];
	int age;
};
int main()
{
	int a = 100;
	char c = 'c';
	float f = 3.14;
	double d = 88.345;
	char str[128];

	cin>>a>>c>>f>>d;
	cin>>str;

	cout<<"a = "<<a<<endl<<"c = "<<c<<endl;
	cout<<"f = "<<f<<endl;
	cout<<"d = "<<d<<endl;
	cout<<"str : "<<str<<endl;

	for(int i=0;i<10;i++)
		cout<<"i = "<<i<<endl;
	return 0;
}
