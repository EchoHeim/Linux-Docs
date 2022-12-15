#include <iostream>
using namespace std;

//��ĸ��ƹ��캯��

//������
class Point{
	int xPos;
	int yPos;
public:
	Point(int x = 0,int y = 0); 
	Point(const Point &);
	~Point();   
	void print(void);
	void SetXpos(int x = 0);
	void SetYpos(int y = 10);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
Point::Point(int x,int y):xPos(x),yPos(y)
{ 
	cout<<"���캯�� �������: int,int "<<endl;
}
Point::Point(const Point & pt):xPos(pt.xPos),yPos(pt.yPos)
{ 
	cout<<"���ƹ��캯�� �������:Point "<<endl;
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
	Point pt1(100,200);
//	Point pt2 = pt1; //���ø��ƹ��캯��
	Point pt2(pt1);
	pt2.print();
	return 0;
}