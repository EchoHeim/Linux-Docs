#include <iostream>
using namespace std;

//��Ĺ��캯��ʹ�ó�ʼ�����ʽ

//������
class Point{
	int xPos;
	int yPos;
public:
	Point(int x = 0,int y = 0); 
	~Point();    //��������������
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
Point::Point(int x,int y):xPos(x),yPos(y)
{ 
	cout<<"���캯�� �������: int,int "<<endl;
}
Point::~Point()    //����������ʵ��
{
	cout<<"��������������"<<endl;
}

void Point::print(void)
{
	cout<<"xPos = "<<this->xPos<<", yPos = "<<this->yPos<<endl;
}
void Point::SetXpos(int x)
{	
	this->xPos = x; 
}
void Point::SetYpos(int y)
{	
	this->yPos = y; 
}

int main()
{
	Point * p1 = new Point(100,200);
	p1->print();
	delete p1;
	Point * p2 = new Point[5];
	Point * tmp = p2;
	p2->print();
	p2++;
	p2->print();
	delete[] tmp;
	return 0;
}

//malloc ���ٶ�����ڴ棬���ܴ������캯��