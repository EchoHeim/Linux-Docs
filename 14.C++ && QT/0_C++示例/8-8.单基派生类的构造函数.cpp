//�����๹�캯���ĵ���˳��
#include <iostream>
using namespace std;

class A					//��A�Ķ���
{
private:				//private��Ա�б�
	int x;
public:
	A(int xp=0)			//���캯������ȱʡ����
	{
		x = xp;
		cout << "A�Ĺ��캯����ִ��" << endl;
	}
};
class B					//��B����
{
public:
	B()					//�޲ι��캯��
	{
		cout << "B�Ĺ��캯����ִ��" << endl;
	}
};
class C:public A		//��C����A��������
{
private:
	int y;
	B b;
public:
	C(int xp, int yp) : A(xp), b()	//���캯�������๹�캯���ڳ�ʼ�����е���
	{
		y = yp;
		cout << "C�Ĺ��캯����ִ��" << endl;
	}
};
int main()
{
	C c(1, 2);			//����C�����c
	return 0;
}
