#include <iostream>
using namespace std;

class point
{
	int xPos; //Ĭ��Ϊprivate�����ݳ�Աx��y
	int yPos;
public:
	point(int x = 0, int y = 0) //���캯��
	{
		xPos = x;
		yPos = y;
	}
	void print() const //const��Ա�������޷��޸����ݳ�Ա���������������
	{
//		xPos = 5; //1. ��ͼ�޸�x����������������
//		set(); //2. ��ͼ���÷�const��������������������
		cout << "x: " << xPos << " ,y: " << yPos << endl;
	}
	void set() //��set()�����const�������ܽ������
	{
	}
};

int main()
{
	point pt;		//�����������ȱʡ������ʽ���ù��캯��
	pt.print();		//����const��Ա����

	return 0;
}
