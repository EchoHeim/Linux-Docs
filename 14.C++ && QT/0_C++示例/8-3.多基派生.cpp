//��������������Ͷ���
#include <iostream>
using namespace std;

class A				                           //��A�Ķ���
{
public:
	void print()	                           //A�ж�����print����
	{
		cout << "Hello,this is A" << endl;
	}
};
class B				                          //��B�Ķ���
{
public:
	void show()		                          //B�ж�����show����
	{
		cout << "Hello,this is B" << endl;
	}
};

class C : public A, public B	              //��C����A����B��ͬ��������
{
public:
	void disp()
	{
		show();		                         //�����ڲ�����ĳ�Ա����
	}
};

int main()
{
	C c;
	c.print();		//�����ⲿ ͨ�� ��������� ���� ���� ��Ա
	c.disp();		//�����ⲿ ���� ��������� ������ӵĳ�Ա
	return 0;
}

