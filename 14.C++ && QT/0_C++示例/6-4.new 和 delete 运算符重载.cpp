//new �� delete ���������
#include <iostream>
using namespace std;

class CStudent
{
public:
	int iId;
	char szName[10];
public:
	static void * operator new(size_t nSize)
	{
		cout << "new ������������, size = " << nSize << endl;
		void * pRet = new char[nSize];           //ע�����ﲻ��ݹ���ã�����ֱ�ӵ���ϵͳĬ�ϵ�new
		return pRet;
	}
	static void operator delete(void * pVoid)
	{
		cout << "delete ������������." << endl;
		delete [] pVoid;
	}
};
int main()
{
	CStudent *pStu = new CStudent;

	pStu->iId = 101;
	strcpy(pStu->szName, "Tony");

	delete pStu;

	return 0;
}

