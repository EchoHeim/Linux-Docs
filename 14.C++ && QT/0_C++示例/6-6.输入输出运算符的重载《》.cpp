//�Բ�����>>������
#include <iostream>
using namespace std;

//http://blog.csdn.net/mzlogin/archive/2009/04/19/5177784.aspx
//���VC6.0����Ԫ��ʽ���������ʱ�޷�������˽�г�Ա�ķ�����
//		���ඨ��֮ǰ�������Ԫ������������ԭ����ǰ����һ��.
class Complex;
ostream & operator<<(ostream &os, Complex &C1); //�Բ�����<<������
istream & operator>>(istream &is, Complex &C1);

class Complex
{
private:
	double imag;		//�鲿
	double real;		//ʵ��
public:
	Complex(double r=0.0,double i=0.0)			//���캯��
	{
		real=r;
		imag=i;
	}
	friend ostream& operator<<(ostream& ,Complex& );		//��Ԫ��������
	friend istream& operator>>(istream& ,Complex& );
};

ostream& operator<<(ostream& os,Complex& C1)			//�Բ�����<<������
{
	os<<C1.real<<"+i*"<<C1.imag<<endl;
	return os;
}

istream& operator>>(istream& is,Complex& C1)			//�Բ�����>>������
{
	is>>C1.real;            //������ʵ��
	while (is.get()!='*')     
	{
	}
	cin>>C1.imag;
	return is;
}

int main()
{
	Complex c1(2.5,3.1);
	cin>>c1;
	cout<<c1;
	return 0;
}

