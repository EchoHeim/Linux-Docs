//��ͬ��������Ķ�����
#include <iostream>
using namespace std;

class A					        //��������
{
protected:				        //protected��Ա�б�
	int x;
public:					        //public��Ա�б�
	A(int xp = 0)		        //���캯��
	{
		x = xp;
	}
	void SetX(int xp)	        //����protected��Աx��ֵ
	{
		x = xp;
	}
	void print()
	{
		cout << "this is x in A: " << x << endl;
	}
};
class B: public A		        //��B����A��������
{
};
class C: public A		        //��C����A��������
{
};
class D : public B, public C	//��D����B����C��������
{
};

int main()
{
	D d;			//����һ��D�����exD
	d.SetX(5);		//SetX()���ж�����, ϵͳ��֪���ǵ���B��Ļ���C���SetX()����
	d.print();		//print()���ж�����, ϵͳ��֪���ǵ���B��Ļ���C���print()����
	return 0;
}

