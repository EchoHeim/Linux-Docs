//��һ���ⲿ��������Ϊ�����Ԫ����
#include <cmath>	//ʹ�ü���ƽ�����ĺ���sqrtҪ�õ���ͷ�ļ�
#include <iostream>
using namespace std;

class Point										//Point�ඨ��
{
private:
	int x, y;
	friend float dis(Point &p1, Point & p2);	//��Ԫ����������������λ��û�й�ϵ��������public��Ҳ����private
public:
	Point(int i = 0, int j = 0)					//���캯������ȱʡ����ֵ
	{
		x = i;
		y = j;
	}	
	void disp()									//��Ա����
	{
		cout << "(" << x << "," << y << ")";
	}
};
float dis(Point & p1, Point & p2)			//��Ԫ������ʵ��
{
	//��Ԫ�����пɷ������private��Ա
	float d = sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
	return d;
}
int main()
{
	Point p1(1, 2), p2(4, 5);				//��������Point��Ķ���p1��p2
	p1.disp();								//��ʾ��p1����Ϣ
	
	cout << "��";
	p2.disp();								//��ʾ��p2����Ϣ
	
	cout << "����=" << dis(p1, p2) << endl;	//������Ԫ���������������
	
	return 0;
}

