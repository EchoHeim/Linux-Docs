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
		cout << "new1 操作符被调用, size = " << nSize << endl;
		void * pRet = new char[nSize];           //注意这里不会递归调用，他会直接调用系统默认的new
		return pRet;
	}
	static void * operator new[](size_t nSize)
	{
		cout << "new2 操作符被调用, size = " << nSize << endl;
		
		void * pRet = new char[nSize];           //注意这里不会递归调用，他会直接调用系统默认的new
		return pRet;
	}
	static void operator delete(void * pVoid)
	{
		cout << "delete1 操作符被调用." << endl;
		delete [] pVoid;
	}
	static void operator delete[](void * pVoid)
	{
		cout << "delete2 操作符被调用." << endl;
		delete [] pVoid;
	}
	char& operator [](int i);	//以成员函数形式重载下标运算符
};

char & CStudent::operator[](int i)
{
	char name='\0';
	cout<<"operator[] is call"<<endl;
	return name; 
}
int main()
{
	CStudent *pStu1 = new CStudent; 
	CStudent *pStu2 = new CStudent[5]; 

	delete pStu1;
	delete[] pStu2;

	return 0;
}

