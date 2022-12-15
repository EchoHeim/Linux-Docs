//public, protected, private������ʽ
#include <iostream>
using namespace std;

class point		                       //point�ඨ��
{
private:		                       //private��Ա�б���ʾ���������Ϣ
	int xPos;
	int yPos;	
public:
	point(int x = 0, int y = 0)	       //���캯������ȱʡ����
	{
		xPos = x;
		yPos = y;
	}	
	void disp()		                  //��Աdisp������������������Ϣ
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}	
	int GetX()		                  //��ȡprivate��ԱxPos
	{
		return xPos;
	}	
	int GetY()		                 //��ȡprivate��ԱyPos
	{
		return yPos;
	}
};

class point3D : public point	    //3ά����point3D����point��̳ж�����ע���ʽ
{
private:
	int zPos;				        //��point�������������zPos������Ϣ
public:
	point3D(int x, int y, int z):point(x, y)//�����๹�캯������ʼ�����е��û��๹�캯��
	{
		zPos = z;
	}	
	void disp()				       //�����˻�����е�ͬ��disp����
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}	
	int calcSum()			       //�����˼���3�����ݳ�Ա�͵ĺ���
	{
		return GetX() + GetY() + zPos;
	}
};

int main()
{
	//�Լ�����, �ֱ�ʹ��public, protected��private����point3D��,
	//����public������ʽʱ���з����������GetX()�������,
	//��protected��private������ʽʱ�ͻ���뱨��.
	point3D pt(3, 4, 5);
	cout<<pt.GetX()<<endl;		//!!!!!!

	//disp()��3�ַ�ʽ�¶��ɷ���, ��Ϊdisp()��Point3D���б����ǳ�public������
	pt.disp();

	//calcSum()��3�ַ�ʽ�¶��ɷ���, ��Ϊ������Point3D�����¶����public��Ա����
	pt.calcSum();

	return 0;
}

