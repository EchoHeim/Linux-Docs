#include <iostream>
using namespace std;

//������
class Point{
	int xPos;
	int yPos;
public:
	Point(int x,int y);    //�������캯��
	void print(void);
	void SetXpos(int x);
	void SetYpos(int y);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
//��Ĺ��캯��֧�ִ��ݲ���
Point::Point(int x,int y)  //��Ĺ��캯��
{ 
	cout<<"���캯��������"<<endl;
	xPos = x;
	yPos = y;
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
	point1.print();
	return 0;
}