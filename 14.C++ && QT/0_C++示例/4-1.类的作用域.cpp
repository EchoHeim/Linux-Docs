//������������
#include <iostream>
using namespace std;

int x = 100; //������������ȫ��int�ͱ���x
int z = 200; //������������ȫ��int�ͱ���z

class Example //Example�ඨ��
{
	int x; //Ĭ��Ϊprivate�ĳ�Ա�б�
	int y;
public:
	Example(int xp = 0, int yp = 0) //���캯��
	{
		x = xp;
		y = yp;
	}
	void print(int x) //��Ա����print���β�Ϊx
	{
		cout << "�������Ĳ���:  " << x << endl; //�β�x���ǵ��˳�Աx��ȫ�ֱ���x
		cout << "��Աx:  " << (this->x) << ", ��Աy:  " << y << endl;//�˴���yָ���ǳ�Աy�����Ҫ���ʳ�Աx����ʹ��thisָ��
		cout << "����thisָ���⣬������ʹ������::����ʽ��" << endl;
		cout << "��Աx:  " << Example::x << ", ��Աy:  " << y << endl;//��ʹ���������������޶�������ʽָ��Ҫ���ʳ�Աx
		cout << "ȫ��x:  " << (::x) << endl; //����ȫ�ֱ���x
		cout <<"ȫ��z:   "<< z << endl;      //û���βκ����ݳ�Ա���ȫ�ֱ���z�������Σ�ֱ�ӷ���z����
	}
};

int main()
{
	Example ex1; //����һ��Example��Ķ���ex1
	ex1.print(5); //���ó�Ա����print()
	return 0;
}

