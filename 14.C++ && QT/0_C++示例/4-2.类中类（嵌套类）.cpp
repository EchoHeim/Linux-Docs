//Ƕ����(������)
#include <iostream>
using namespace std;

class line //line�ඨ��
{
public:
	class point //point�ඨ����line���ڣ���Ϊpublic���ԣ��ⲿ�ɷ���
	{
	private: //point����˽�г�Ա�б�
		int x;
		int y;
	public:
		point(int xp = 0, int yp = 0) //point�๹�캯������ȱʡ����ֵ
		{
			x = xp;
			y = yp;
		}
		void printpoint(); //point���Ա����ԭ�ͣ��ⲿʵ��
	};
private:
	point p1, p2; //line������point�����Ա
public:
	line(int x1, int y1, int x2, int y2):p1(x1, y1), p2(x2, y2)//���캯������ʼ����
	{
	}
	void printline() //�����ʾ��Ϣ
	{
		p1.printpoint(); //���ö����Ա�Ĺ����ӿ�
		cout << "  ------->  ";
		p2.printpoint(); //���ö����Ա�Ĺ����ӿ�
		cout << endl;
	}
};
void line::point::printpoint() //point���к���printpoint()��ʵ�֣�ע��˫���������޶���
{
	cout << "( " << x << " , " << y << " )";
}
int main()
{
	line line1(1, 2, 3, 4);	//����line�๹�캯��������һ��line��Ķ���line1
	line1.printline();		//�����ʾ��Ϣ

	line::point pt(1, 3);	//��line::point����point�ඨ�壬����һ��point��Ķ���pt
	pt.printpoint();		//�����ʾ��Ϣ

	cout << endl;			//Ϊ�������ۣ�����
	return 0;
}

