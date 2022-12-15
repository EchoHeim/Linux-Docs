//->操作符重载
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
	DataPtr()                  //构造函数
	{
		m_Data = new Data;
	}
	~DataPtr()                //析构函数
	{
		delete m_Data;
	}
	//->操作符重载
	Data * operator->()
	{
		cout << "->操作符重载函数被调用." << endl;
		return m_Data;
	}
};

int main()
{
	DataPtr p;
	cout << p->GetData() << endl;	//等价于下面1句:
	cout << (p.operator->())->GetData() << endl;

	return 0;
}

