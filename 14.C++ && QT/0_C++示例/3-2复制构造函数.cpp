#include <iostream>
#include <cstring>
using namespace std;

class computer
{
private:
	char * brand;
	float price;
public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) + 1];
		strcpy(brand, sz);
		price = p;
	}
	computer(const computer & comp)  //��ʾ���帴�ƹ��캯��
	{
		brand = new char[strlen(comp.brand)+1]; //��̬�����ڴ�
		strcpy(brand,comp.brand); //��������
		price = comp.price;
	}
	~computer()
	{
		delete[] brand;
		cout << "�����ֳ�" << endl;
	}
	void print()
	{
		cout << "Ʒ�ƣ�" << brand << endl;
		cout << "�۸�" << price << endl;
	}
};

int main()
{
	computer comp1("Dell", 7000);//�����вι��캯������computer�����comp1������ʼ��
	comp1.print();
	computer comp2(comp1);       //���ø��ƹ��캯������computer�����comp2������comp1Ϊ���ʼ��
	comp2.print();
	return 0;
}
