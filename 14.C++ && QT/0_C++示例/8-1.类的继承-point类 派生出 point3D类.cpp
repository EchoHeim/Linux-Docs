//�̳��������ĸ��� ��point�� ������ point3D��
#include <iostream>
using namespace std;

class point		                         //point�ඨ��
{
private:		                         //private��Ա�б���ʾ���������Ϣ
	int xPos;
	int yPos;	
public:
	point(int x = 0, int y = 0)	         //���캯������ȱʡ����
	{
		xPos = x;
		yPos = y;
	}	
	void disp()	                    	 //��Աdisp������������������Ϣ
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	int GetX()		                    //��ȡprivate��ԱxPos
	{
		return xPos;
	}	
	int GetY()		                   //��ȡprivate��ԱyPos
	{
		return yPos;
	}
};
class point3D:public point	          //3ά����point3D����point��̳ж���
{
private:
	int zPos;				          //��point�������������zPos������Ϣ	
public:
	point3D(int x, int y, int z):point(x, y)//�����๹�캯������ʼ�����е��û��๹�캯��
	{
		zPos = z;
	}	
	void disp()				         //�����˻�����е�ͬ��disp����
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}	
	int calcSum()			         //�����˼���3�����ݳ�Ա�͵ĺ���
	{
		return GetX() + GetY() + zPos;
	}
};
int main()
{
	point pt1(7, 8);			//����point�����pt1
	pt1.disp();					//��ʾpt1����Ϣ

	point3D pt2(3, 4, 5);		//����point3D�����pt2
	pt2.disp();					//��ʾpt2����Ϣ

	int res = pt2.calcSum();	//����pt2��3��������Ϣ�ļӺ�
	cout << res << endl;		//������

	return 0;
}

