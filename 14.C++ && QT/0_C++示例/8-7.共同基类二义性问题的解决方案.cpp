//ʹ�����������ͬ��������Ķ���������
#include <iostream>
using namespace std;

class A				//���������A
{
protected:			//protected��Ա�б�
	int x;
public:
	A(int xp = 0)		//���캯������ȱʡ�������
	{
		x=xp;
	}
	void SetX(int xp)//SetX������������protected��Աx
	{
		x = xp;
	}
	void print()	//print���������Ϣ
	{
		cout << "this is x in A: " << x << endl;
	}
};
class B: virtual public A	//B��A�����������
{
};
class C: virtual public A	//C��A�����������
{
};
class D:public B,public C	//D��B��C��ͬ����
{
};
int main()
{
	D d;			//����һ��D�����exD

	d.SetX(5);		//SetX��������Ϊvirtual��������D��ֻ��һ���汾���������
	d.print();		//print��������Ϊvirtual��������D��ֻ��һ���汾���������

	d.A::print();	//������������ʽ˵�����ú����İ汾
	d.B::print();
	d.C::print();

	return 0;
}

