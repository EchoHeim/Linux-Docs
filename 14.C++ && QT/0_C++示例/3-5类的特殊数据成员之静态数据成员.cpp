#include <iostream>
using namespace std;

//���Ծ�̬���ݳ�Ա

class computer
{
private:
	float price; //float�����ݳ�Աprice����ʾ�۸�
	static float total_price; //statci��Ա���ܼۣ���������ĳ������
public:
	computer(const float p) //���캯����ģ������ԵĲ�������total_price�����ۼ�	
	{
		price = p;
		total_price += p;
	}
	~computer() //����������ģ���˻����ԵĲ�������total_price�м�ȥ���˵��Ե�price
	{
		total_price -= price;
	}
	void print() //�������
	{
		cout << "�ܼۣ�" << total_price << endl;
	}
};
float computer::total_price = 0;//��ʼ����ľ�̬��Ա��Ա


int main()
{
	computer comp1(7000); //�������1
	cout << "�������1��" << endl;
	comp1.print();
	computer comp2(4999); //�������2
	cout << "�������2��" << endl;
	comp2.print();
	computer comp3(2500); //�������3
	cout << "�������3��" << endl;
	comp1.print(); //�˴�����comp1.print()��comp2.print()��comp3.print()��������ͬ
	comp2.~computer(); //�˵�����2
	cout << "�˵�����2��" << endl;
	comp3.print();
/*	computer::total_price = 1000;
	cout<<"total = "<<computer::total_price<<endl;
	cout<<"total = "<<comp1.total_price<<endl; */
	return 0;
}

