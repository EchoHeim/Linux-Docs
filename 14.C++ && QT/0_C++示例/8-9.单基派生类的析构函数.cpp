//���������������
#include <iostream>
using namespace std;

class A					//A��Ķ���
{
private:				//private��Ա�б�
	int x;	
public:					//public��Ա�б�
	A(int xp = 0)		//���캯������ȱʡ����
	{
		x = xp;
		cout << "A�Ĺ��캯����ִ��" << endl;
	}
	~A()				//��������
	{
		cout << "A������������ִ��" << endl;
	}
};
class B					//B��Ķ���
{
public:					//public��Ա�б�
	B()					//�޲ι��캯��
	{
		cout << "B�Ĺ��캯����ִ��" << endl;
	}
	~B()				//��������
	{
		cout << "B������������ִ��" << endl;
	}
};
class C:public A		//��C����A��������
{
private:
	int y;	
	B b;				//�����Ա
public:
	C(int xp, int yp):A(xp), b()	//������Ĺ��캯��������Ͷ����Ա���ڳ�ʼ��������ɳ�ʼ��
	{
		y = yp;
		cout << "C�Ĺ��캯����ִ��" << endl;
	}
	~C()				//��������
	{
		cout << "C������������ִ��" << endl;
	}
};

int main()
{
	C c(1, 2);			//����һ��C�����c
	return 0;			//main����ִ����ϣ�c������������������ִ��
}

