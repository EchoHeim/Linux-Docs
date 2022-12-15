//��Ա������ʽ �� ���������
#include <iostream.h>
//using namespace std;

class complex							//���帴����complex
{
private:
	double real,imag;					//private��Ա���ֱ����ʵ�����鲿

public:
	complex(double r=0.0,double i=0.0)	//���캯������ȱʡ����ֵ
	{
		real=r;
		imag=i;
	}
	void disp()														//��Ա�������������
	{
		cout<<real<<" + "<<"i*"<<imag<<endl;
	}

	friend complex operator + (const complex & C1,const complex & C2);	//��Ԫ������ʽ���ؼ�+
	friend complex operator - (const complex &,const complex &);	//��Ԫ������ʽ���ؼ���
	friend complex operator - (const complex &);					//��Ԫ������ʽ����һԪ����ȡ����
	friend complex operator * (const complex &,const complex &);	//��Ԫ������ʽ���س�*
	friend complex operator / (const complex &,const complex &);	//��Ԫ������ʽ���س�*
	friend complex & operator ++(complex &);							//��Ԫ������ʽ����ǰ��++
	friend complex operator ++(complex &,int);						//��Ԫ������ʽ���غ���++
};

complex operator+ (const complex& C1,const complex& C2)		//��+��ʵ��
{
	return complex(C1.real + C2.real, C1.imag + C2.imag);
}

complex operator- (const complex& C1,const complex& C2)		//��-��ʵ��
{
	return complex(C1.real - C2.real, C1.imag - C2.imag);
}

complex operator- (const complex& C1)						//��Ŀ-����ȡ����ʵ��
{
	return complex(-C1.real, -C1.imag);
}

complex operator *(const complex& C1,const complex& C2)		//��*��ʵ��
{
	return complex(C1.real * C2.real - C1.imag * C2.imag, C1.real * C2.imag + C1.imag * C2.real);
}

complex operator /(const complex& C1,const complex& C2)		//��*��ʵ��
{
	return complex((C1.real * C2.real + C1.imag + C2.imag) / (C2.real * C2.real + C2.imag * C2.imag),
		(C1.imag * C2.real - C1.real * C2.imag) / (C2.real * C2.real + C2.imag * C2.imag));
}

complex & operator ++(complex& C1)		//ǰ��++��ʵ��
{
	cout << "ǰ��++" << endl;
	C1.real += 1;
	C1.imag += 1;
	return C1;
}

complex operator ++(complex& C1,int)	//����++��ʵ�֣�����ǰ��++������
{
	cout << "����++" << endl;
	complex ctemp = C1;
	++C1;
	return ctemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;
	
	cxRes = cx1 - cx2;	//�൱��operator-(cx1, cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//�൱��operator-(cx1)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//�൱��operator+(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//�൱��operator*(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//�൱��operator/(cx1, cx2)
	cxRes.disp();
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//�൱��operator++(cx3)
	cxRes.disp();
	cx3.disp();
	
	cxRes = cx4++;		//�൱��operator++(cx4, 0)
	cxRes.disp();
	cx4.disp();
	
	//ע�������������Ԫ������ʽ�ͳ�Ա������ʽ�ĶԱȡ�
	cxRes = cx1 + 5;	//�൱��operator+(cx1, 5);
	cxRes.disp();

	cxRes = 5 + cx1;	//�൱��operator+(5, cx1);
	cxRes.disp();

	return 0;
}
