//���غ������������()
#include <iostream>
using namespace std;

class Demo		//Demo�ඨ��
{
public:
	double operator()(double x, double y)	      //���غ������÷�(),����double�Ͳ���
	{
		return x > y ? x : y;				      //�������������нϴ��һ��
	}

	double operator()(double x, double y, double z)//���غ������÷�(),3��double�Ͳ���
	{
		return (x + y) * z;						  //��ǰ������ӣ����3��������ˣ��������Ľ��
	}
};

void main()
{
	Demo de;											//����һ�������ע��͹��캯�������𣬹��캯���ڶ���ʱ�����ã�
	cout << de(2.5, 0.2) << endl;						//���Խ���������һ��ʹ��
	cout << de(1.2, 1.5, 7.0) << endl;
}

