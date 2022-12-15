#include <iostream>
using namespace std;

//���Ծ�̬��Ա����

class computer
{
private:
	char *name;
	float price;
	static float total_price; //��̬���ݳ�Ա
public:
	computer(const char *chr, const float p) //���캯����ģ������Բ���
	{
		name = new char[strlen(chr) + 1];
		strcpy(name, chr);
		price = p;
		total_price += p;
	}
	~computer() //����������ģ���˵����ԵĲ���
	{
		if (name)
		{
			delete[] name;
			name = NULL;
		}
		total_price -= price;
	}
	static void print_total() //��̬��Ա������ԭ����ֻ�ܷ��ʾ�̬���ݳ�Ա
	{
		cout << "�ܼۣ�" << total_price << endl;
	}
	static void print(computer &com); //��̬��Ա����print()ԭ�ͣ����Ҫ����ĳ������󣬱��봫�ݲ���
	void print_this(void)
	{
		cout << "����"  << this->name << endl;
		cout << "�۸�"<< this->price << endl;	
	}
};
void computer::print(computer & com) //��̬��Ա����print()ʵ��
{
	print_total();
//	print_this();
	cout << "����" << com.name << endl;
	cout << "�۸�" << com.price << endl;
}

float computer::total_price = 0; //��ʼ��

int main()
{
	computer comp1("IBM", 7000); //���������comp1����ʼ��������
	computer::print(comp1); //�������������޶�������statci��Ա���������ݲ���comp1
	computer::print_total(); //�������������޶�������statci��Ա����

	computer comp2("ASUS", 4999); //���������comp2����ʼ��������
	computer::print(comp2); //�������������޶�������statci��Ա���������ݲ���comp2
	computer::print_total();

	comp2.~computer(); //�����������ã��˻�����
	computer::print_total();

	return 0;
}