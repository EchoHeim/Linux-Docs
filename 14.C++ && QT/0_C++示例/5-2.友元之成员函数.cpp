//��Line��ĳ�Ա����dis()��ΪPoint�����Ԫ����
#include <cmath>			//ʹ�ü���ƽ�����ĺ���sqrtҪ�õ���ͷ�ļ�
#include<iostream>
#include <cmath>
using namespace std;

class Point;				//����Point��

class Line					//����Line��(�˴�ע�⣬���������������ĺ���)
{
public:
	float dis(Point& p1, Point& p2); //��Ԫ������ԭ�ͣ���ΪLine��ĳ�Ա����
};
class Point					//����Point��
{
private:
	int x,y;				//private�����ݳ�Աx��y
	friend float Line::dis(Point &p1, Point &p2);	//��Ԫ������
public:
	Point(int i = 0, int j = 0)	//Point��Ĺ��캯������ȱʡ����
	{
		x = i;
		y = j;
	}
	void disp()				//��Ա����disp()��������������Ϣ
	{
		cout << "(" << x << "," << y << ")";
	}
};

//Line���ڳ�Ա����dis��ʵ�֣���ΪPoint�����Ԫ������������������У��ұ�����Point��Ķ���֮����Ϊ������а�����Point�������ͣ�
float Line::dis(Point &p1, Point &p2)
{
	float d = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	//�ɷ���Point������private��Ա

	return d;
}

int main()
{
	Line line1;					//����һ��Line��Ķ���line1
	Point p1(1,2), p2(4,5);		//��������Point��Ķ���p1��p2

	p1.disp();					//�����p1����Ϣ 
	cout << " �� "; 
	p2.disp();					//�����p2����Ϣ

	cout << " �ľ��� = " << line1.dis(p1, p2) << endl;
	//ͨ������line1�ĳ�Ա����dis�����������ľ���

	return 0;
}

