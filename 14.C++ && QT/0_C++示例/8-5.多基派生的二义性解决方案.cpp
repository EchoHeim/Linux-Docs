//�����̳�ʱ�Ķ���������Ľ������, �����뱸ע�е�1��2
#include <iostream>
using namespace std;

class A				//��A�Ķ���
{
public:
	void print()	//A�ж�����print����
	{
		cout<<"Hello,this is A"<<endl;
	}
};

class B				//��B�Ķ���
{
public:
	void print()	//B��ͬ��������print����
	{
		cout<<"Hello,this is B"<<endl;
	}
};

class C : public A, public B	//��C����A����B��ͬ��������
{
public:
	void disp()
	{
		A::print();       	   //1. ָ������A���ж���İ汾
	}

	//����print����, �����������ò�ͬ�����print����
	void print()
	{
		if (true)
			A::print();
		else
			B::print();
	}
};

int main()
{
	C c;
	c.disp();		//�������ڷ��ʶ����Ա�Ķ����Եõ����

	c.A::print();	//2.1 ָ������B���ж���İ汾 c.(A::print());
	c.print();		//2.2 ��C��������print����

	return 0;
}

