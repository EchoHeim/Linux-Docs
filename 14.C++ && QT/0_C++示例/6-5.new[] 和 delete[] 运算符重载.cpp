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
		cout << "new1 ������������, size = " << nSize << endl;
		void * pRet = new char[nSize];           //ע�����ﲻ��ݹ���ã�����ֱ�ӵ���ϵͳĬ�ϵ�new
		return pRet;
	}
	static void * operator new[](size_t nSize)
	{
		cout << "new2 ������������, size = " << nSize << endl;
		
		void * pRet = new char[nSize];           //ע�����ﲻ��ݹ���ã�����ֱ�ӵ���ϵͳĬ�ϵ�new
		return pRet;
	}
	static void operator delete(void * pVoid)
	{
		cout << "delete1 ������������." << endl;
		delete [] pVoid;
	}
	static void operator delete[](void * pVoid)
	{
		cout << "delete2 ������������." << endl;
		delete [] pVoid;
	}
	char& operator [](int i);	//�Գ�Ա������ʽ�����±������
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

