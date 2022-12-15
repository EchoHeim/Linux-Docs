//->����������
#include <iostream>
using namespace std;

class Data
{
public:
	int GetData() {return 5;}
};

class DataPtr
{
private:
	Data *m_Data;
public:
	DataPtr()                  //���캯��
	{
		m_Data = new Data;
	}
	~DataPtr()                //��������
	{
		delete m_Data;
	}
	//->����������
	Data * operator->()
	{
		cout << "->���������غ���������." << endl;
		return m_Data;
	}
};

int main()
{
	DataPtr p;
	cout << p->GetData() << endl;	//�ȼ�������1��:
	cout << (p.operator->())->GetData() << endl;

	return 0;
}

