#include <iostream>
using namespace std;

//��Ĺ��캯��ʹ�ó�ʼ�����ʽ

//������
class Point{
	int xPos;
	int yPos;
public:
	Point(int x,int y); 
	~Point();    //��������������
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
Point::Point(int x,int y):xPos(x),yPos(y)
{ 
	cout<<"���캯�� �������: int,int "<<endl;
//	xPos = 0;yPos = 0;
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
	Point point1[2] = {Point(10,20),Point(11,21)};
	Point point1[5] = {Point(10,20),Point(11,21)};
	Point * p1 = new Point(100,200);
	p1->print();
	delete p1;
	point1[0].print();
	point1[1].print();
	cout<<"test"<<endl;
	return 0;
}