#include <iostream>
using namespace std;

//��Ĺ��캯��֧������

//������
class Point{
	int xPos;
	int yPos;
public:
	Point(void);
	Point(int x);
	Point(int x,int y); 
	~Point();    //��������������
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
Point::Point(void)
{ 
	cout<<"���Թ��캯������ �������: void"<<endl;
	xPos = 0;yPos = 0;
}
Point::Point(int x)
{ 
	cout<<"���Թ��캯������ �������: int "<<endl;
	xPos = x;yPos = x;
}
Point::Point(int x,int y)  //��Ĺ��캯��
{ 
	cout<<"���Թ��캯������ �������: int,int "<<endl;
	xPos = x;
	yPos = y;
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
	Point point1(100,200); //()�е������Ǹ����캯�����ݵĲ��� 
	Point point2;
	Point point3(50);
	point1.print();
	point2.print();
	point3.print();
	return 0;
}