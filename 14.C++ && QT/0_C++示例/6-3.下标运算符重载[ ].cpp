//下标运算符[]
#include <iostream>
using namespace std;

class CharSZ					//类CharSZ的定义
{
private:						//private成员列表
	int iLen;
	char *pBuf;
public:
	CharSZ(int size)			//构造函数
	{
		iLen= size;
		pBuf = new char[iLen];	//开辟一块动态内存，字符数组
	}
	~CharSZ()					//析构函数
	{
		delete[] pBuf;			//释放申请的动态内存
	}
	int GetLen()				//读取private成员iLen的值
	{
		return iLen;
	}

	char& operator [](int i);	//以成员函数形式重载下标运算符
};
char & CharSZ::operator[](int i)//下标运算符重载的实现
{
	char szNull = '\0';	//用于返回空字符时, 由于返回类型为char &，不能直接return '\0';
	if (i < iLen && i >= 0)		//如果参数i在有效范围内
	{
		return pBuf[i];			//返回字符数组的第i＋1个元素
	}
	else
	{
		cout << "下标越界" << endl;	//参数i不合法
		return szNull;			//输出空字符. 不能直接return '\0';
	}
}

int main()
{
	char *sz = "Hello World!";
	CharSZ de(strlen(sz) + 1);		//对象de中申请的动态内存大小为n，可存放n-1个有效字符（除开'\0'）

	//将sz的内容复制给de
	int i;
	for (i = 0; i < (strlen(sz) + 1); i++)
	{
		de[i] = sz[i];
	}

	//逐个输出de的值
	for (i = 0; i < de.GetLen(); i++)
	{
		cout << de[i];
	}

	cout << endl;
	return 0;
}

