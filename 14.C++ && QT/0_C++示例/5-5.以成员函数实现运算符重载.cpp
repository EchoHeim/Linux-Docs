//��Ա������ʽ �� ���������
#include <iostream>
using namespace std;

class complex					//���帴���� complex
{
private:
	double real, imag;			//private ��Ա���ֱ����ʵ�����鲿
public:
	complex(double r = 0.0, double i = 0.0)	//���캯������ȱʡ����ֵ
	{
		real = r;
		imag = i;
	}
	complex operator+= (const complex &);	//��Ա������ʽ���ؼ�+=

	complex operator+(const complex &);	//��Ա������ʽ���ؼ�+
	complex operator-(const complex &);	//��Ա������ʽ���ؼ���
	complex operator-();					//��Ա������ʽ����һԪ����ȡ����
	complex operator*(const complex &);	//��Ա������ʽ���س�*
	complex operator/(const complex &);	//��Ա������ʽ���س�*

	complex & operator++();					//��Ա������ʽ����ǰ��++
	complex operator++(int);				//��Ա������ʽ���غ���++

	void disp()								//��Ա�������������
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex complex::operator+=(const complex& CC)		//��+=��ʵ��
{
	real += CC.real;
	imag += CC.imag;
	return (*this);
}

complex complex::operator+(const complex& CC)		//��+��ʵ��
{
	return complex(real + CC.real, imag + CC.imag);
}

complex complex::operator-(const complex& CC)		//��-��ʵ��
{
	return complex(real - CC.real, imag - CC.imag);
}

complex complex::operator*(const complex& CC)		//��*��ʵ��
{
	return complex(real * CC.real - imag * CC.imag, real * CC.imag + imag * CC.real);
}

complex complex::operator/(const complex& CC)		//��/��ʵ��
{
	return complex((real * CC.real + imag + CC.imag) / (CC.real * CC.real + CC.imag * CC.imag),
		(imag * CC.real - real * CC.imag) / (CC.real * CC.real + CC.imag * CC.imag));
}

complex complex::operator-()						//��Ŀ-����ȡ����ʵ��
{
	return complex(-real, -imag);
}

complex& complex::operator++()						//ǰ��++��ʵ��
{
	cout << "ǰ��++" << endl;
	++real;
	++imag;
	return (*this);
}

complex complex::operator++(int)					//����++��ʵ�֣�����ǰ��++������
{
	cout << "����++" << endl;
	complex cTemp = (*this);	//���յķ���ֵ����ԭ����ֵ�������Ҫ�ȱ���ԭ����ֵ
	++(*this);					//���غ�ԭ����ֵ��Ҫ��1
	return cTemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes += cx2;		//�൱��cxRes.operator+=(cx2)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//�൱��cx1.operator+(cx2)
	cxRes.disp();
	
	cxRes = cx1 - cx2;	//�൱��cx1.operator-(cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//�൱��cx1.operator*(cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//�൱��cx1.operator/(cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//�൱��cx1.operator-()
	cxRes.disp();
	
	cout << endl;
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//�൱��cx3.operator++()
	cxRes.disp();
	cx3.disp();

	cout << endl;
	
	cxRes = cx4++;		//�൱��cx4.operator++(0)
	cxRes.disp();
	cx4.disp();

	cout << endl;
	
	//ע�������������Ԫ������ʽ�ͳ�Ա������ʽ�еĶԱȡ�
	cxRes = cx1 + 5;	//�൱��cx1.operator+(5) �� cx1.operator+(complex(5))
	cxRes.disp();

//	cxRes = 5 + cx1;	//����. �൱��5.operator+(cx1);
//	cxRes.disp();

	return 0;
}

