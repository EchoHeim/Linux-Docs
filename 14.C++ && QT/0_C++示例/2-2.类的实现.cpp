#include <iostream>
using namespace std;

//������
//��Ķ�����Ĭ����private
class Point{
	int xPos;
	int yPos;
public:
	void print(void);
	void SetXpos(int x);
	void SetYpos(int y);
};
//ʵ����  ��һ��ʵ����ĳ�Ա����
void Point::print(void)
{
	cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
}
void Point::SetXpos(int x)
{	
	xPos = x; 
}
void Point::SetYpos(int y)
{	
	yPos = y; 
}



int main()
{
	//ʹ����
	Point point1;   //������ı�������Ķ���
//	point1.xPos = 100;
//	point1.yPos = 200;
	point1.SetXpos(100);
	point1.SetYpos(100);
	point1.print();
	return 0;
}