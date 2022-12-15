//����ת������(����ת������������)
#include <iostream>
using namespace std;

class anotherPoint					//anotherPoint�ඨ��
{
private:							//private��Ա�б�
	double x;
	double y;
public:
	anotherPoint(double xx = 1.11, double yy = 1.11)//���캯������ȱʡ����ֵ
	{
		x = xx;
		y = yy;
	}
	void print()					//��Ա��������������Ϣ
	{
		cout << "( " << x << " , " << y << " )" << endl;
	}
};
class point							//Point�ඨ��
{
private:							//private��Ա�б�
	int xPos;
	int yPos;
public:
	point(int x = 0, int y = 0)		//���캯������ȱʡ����ֵ
	{
		xPos = x;
		yPos = y;
	}
	void print()					//��Ա��������������Ϣ
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	operator int()					//����Point��int�͵�ת������int()
	{
		return xPos;
	}
	operator double()				//����Point��double�͵�ת������double()
	{
		return xPos * yPos;
	}
	operator anotherPoint()			//����Point��anotherPoint�͵�ת������anotherPoint()
	{
		return anotherPoint(xPos, yPos);
	}
};
int main()
{
	point p1(4, 5);			//����һ��point�����p1
	p1.print();

	//1. pointת����int
	int x1 = p1;			//p1��ֵ��һ��int�ͱ�����point�е�ת������int()����ʽ����
	cout << x1 << endl;

	//2. pointת����double
	double dX = p1;			//p1��ֵ��һ��double�ͱ�����point�е�ת������double()����ʽ����
	cout << dX << endl;

	//3. pointת����anotherPoint
	anotherPoint p2;		//����anotherPoint�����p2�����캯������ȱʡֵ
	p2 = p1;				//p1��ֵ��p2��point�е�ת������anotherPoint()����ʽ����
							//�ȼ���p2��another(p1.xPos,p1.yPos)
	p2.print();				//��p2�Ƿ��޸ĳɹ�

	return 0;
}
