//��Ԫ��
#include<iostream>
#include <cmath>
using namespace std;

class CLine;				//������CLine

class CPoint //����CPoint��
{
private:
	int x, y;
	friend CLine; //��Ԫ���������λ��ͬ����������	
public:
	CPoint(int i = 0, int j = 0) //���캯������ȱʡ����ֵ
	{
		x = i;
		y = j;
	}	
	void disp() //��Ա��������������Ϣ
	{
		cout << "(" << x << "," << y << ")";
	}
};
class CLine				//��CLine�Ķ��壬�������еĺ�������CPoint�����Ԫ����
{
public:
	float dis(CPoint& p1,CPoint& p2)		//�ɷ���p1��p2��private��Ա
	{
		float d;
		d=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
		return d;
	}
	void Set(CPoint* p1,int a,int b)		//�ɷ���p1��p2��private��Ա
	{
		p1->x=a;
		p1->y=b;
	}
};

int main()
{
	CLine cz1;			    //����һ��CLine��Ķ���cz1
	CPoint p1(1,2),p2(4,5);	//��������CPoint�����p1��p2

	p1.disp();				//�����p1����Ϣ 
	cout<<"��";
	p2.disp();				//�����p2����Ϣ
	cout<<"����="<<cz1.dis(p1,p2)<<endl;//����cz1�ĳ�Ա����dis����������

	cz1.Set(&p1,3,4);		//����cz1�ĳ�Ա����Set��дp1�е�private��Աx��y
	p1.disp();				//�޸ĺ�ĵ�p1��Ϣ���

	cout<<endl;				//����

	return 0;
}

