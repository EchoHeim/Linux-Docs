#include <iostream>
#include <cstring>
using namespace std;
class computer
{
private:
	char * brand; //ָ���Ա
	float price;
public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) + 1]; //���󴴽�ʱΪbrand����һ�鶯̬�ڴ�
		strcpy(brand, sz); //�ַ�������
		price = p;
	}
	~computer()
	{
		delete[] brand; //�������ʱ���ͷ��ڴ棬����й¶
		brand = NULL;
		cout << "�����ֳ�" << endl;
	}
	void print() //��Ϣ���
	{
		cout << "Ʒ�ƣ�" << brand << endl;
		cout << "�۸�" << price << endl;
	}
};

int main()
{
	computer comp("Dell", 7000); //���ù��캯������computer����comp
	comp.print(); //��Ϣ���

	return 0;
}
