//�����̳�ʱ�Ķ���������
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
		print();	//�������޷���������A���ж���İ汾����B���еİ汾
	}
};

int main()
{
	C c;
	c.disp();		//�������ڷ��ʶ����Ա�Ķ�����
	c.print();		//�ⲿͨ�������������ʻ����Ա�Ķ�����
	return 0;
}

