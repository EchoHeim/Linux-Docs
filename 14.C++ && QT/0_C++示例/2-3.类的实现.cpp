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

//��Ա����ռ�ݲ�ͬ���ڴ�����;
//��Ա��������ͬһ�ڴ�����(�����)
//������Ķ�������ĳ�Ա������
//����thisָ�����������ĸ���Ķ�����ó�Ա����

int main()
{
	//ʹ����
	Point point1;   //������ı�������Ķ���
	Point point2;
	point1.SetXpos(100);
	point1.SetYpos(100);
	point2.SetXpos(200);
	point2.SetYpos(200);
	point1.print();
	point2.print();

	return 0;
}