#include <iostream>
using namespace std;

//������
//��Ķ�����Ĭ����private
class Point{
	int xPos;
	int yPos;
public:
	void print(void)
	{
		cout<<"xPos = "<<xPos<<", yPos = "<<yPos<<endl;
	}
};

//ʹ����
Point point1;   //������ı�������Ķ���

int main()
{
	point1.xPos = 100;
	point1.yPos = 200;
	point1.print();
	return 0;
}