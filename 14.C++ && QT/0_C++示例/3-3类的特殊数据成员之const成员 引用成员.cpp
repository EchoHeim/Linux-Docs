#include <iostream>
using namespace std;

//����������ݳ�Ա֮const��Ա ���ó�Ա

//������
class Point{
	const int xPos;
	const int yPos;
	int & zPos;
public:
	Point(int & cp,int x = 0,int y = 0); 
	Point(const Point &);
	~Point();   
	void print(void);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
Point::Point(int & cp,int x,int y):xPos(x),yPos(y),zPos(cp)
{ 
	cout<<"���캯�� �������: int,int "<<endl;
}

Point::Point(const Point & pt):xPos(pt.xPos),yPos(pt.yPos),zPos(pt.zPos)
{ 
	cout<<"���ƹ��캯�� �������:Point "<<endl;
}
Point::~Point()    //����������ʵ��
{
	cout<<"��������������"<<endl;
}

void Point::print(void)
{
	cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
	cout<<"zPos = "<<zPos<<endl;
}

int main()
{
	int zPos = 300;
	Point pt1(zPos,100,200);
	pt1.print();
	return 0;
}