//��������
#include <iostream>
using namespace std;

void Work(int a, int b)
{
	class point				//�ඨ���ں����ڣ��ں������޷�ʹ��point��������
	{
	private:
		int x, y;
	public:
		point(int xp = 0, int yp = 0)
		{
			x = xp;
			y = yp;
		}
		void print()
		{
			cout << x << "," << y << endl;
		}
	};

	point pt(a, b);	//�����ڣ�����point��Ķ���pt
	pt.print();		//�����ʾ��Ϣ
}
int main()
{
	Work(5, 6);				//work��������
	return 0;
}

