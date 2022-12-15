#include <iostream>
using namespace std;

class point //����Ķ���
{
private:
	int xPos;
	int yPos;
public:
	point(int x, int y) //��ȱʡ���õĹ��캯��
	{
		cout << "��Ĺ��캯����ִ��" << endl;
		xPos = x;
		yPos = y;
	}
	point(const point & pt) //���ƹ��캯��
	{
		cout << "��ĸ��ƹ��캯����ִ��" << endl;
		xPos = pt.xPos;
		yPos = pt.yPos;
	}
	~point()
	{
		cout<<"�������������ִ��"<<endl;
	}
	void print()
	{
		cout << "( " << xPos << ", " << yPos << ")";
	}
};

class line //line��Ķ���
{
private:
	point pt1; //point�������Ϊline���Ա���˴���д��point pt1(3,4)����
	point pt2;
public:
	line(int x1, int y1, int x2, int y2):pt1(x1,y1),pt2(x2,y2) //line������вι��캯��
	{
		cout << "�ߵĹ��캯����ִ��" << endl;
	}
	line(const line &ll):pt1(ll.pt1), pt2(ll.pt2) //line����ĸ��ƹ��캯��
	{
		cout << "�ߵĸ��ƹ��캯����ִ��" << endl;
	}
	~line()
	{
		cout<<"�ߵ�����������ִ��"<<endl;
	}
	void draw()
	{
		pt1.print();
		cout << "  to  ";
		pt2.print();
		cout << endl;
	}
};

int main()
{
	line l1(1, 2, 3, 4); //�����вι��캯��
	l1.draw();
	line l2(l1); //���ø��ƹ��캯��
	l2.draw();
	return 0;
}
