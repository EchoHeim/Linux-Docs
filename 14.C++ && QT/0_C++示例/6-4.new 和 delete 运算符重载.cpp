//new 和 delete 运算符重载
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
		cout << "new 操作符被调用, size = " << nSize << endl;
		void * pRet = new char[nSize];           //注意这里不会递归调用，他会直接调用系统默认的new
		return pRet;
	}
	static void operator delete(void * pVoid)
	{
		cout << "delete 操作符被调用." << endl;
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

