//�±������[]
#include <iostream>
using namespace std;

class CharSZ					//��CharSZ�Ķ���
{
private:						//private��Ա�б�
	int iLen;
	char *pBuf;
public:
	CharSZ(int size)			//���캯��
	{
		iLen= size;
		pBuf = new char[iLen];	//����һ�鶯̬�ڴ棬�ַ�����
	}
	~CharSZ()					//��������
	{
		delete[] pBuf;			//�ͷ�����Ķ�̬�ڴ�
	}
	int GetLen()				//��ȡprivate��ԱiLen��ֵ
	{
		return iLen;
	}

	char& operator [](int i);	//�Գ�Ա������ʽ�����±������
};
char & CharSZ::operator[](int i)//�±���������ص�ʵ��
{
	char szNull = '\0';	//���ڷ��ؿ��ַ�ʱ, ���ڷ�������Ϊchar &������ֱ��return '\0';
	if (i < iLen && i >= 0)		//�������i����Ч��Χ��
	{
		return pBuf[i];			//�����ַ�����ĵ�i��1��Ԫ��
	}
	else
	{
		cout << "�±�Խ��" << endl;	//����i���Ϸ�
		return szNull;			//������ַ�. ����ֱ��return '\0';
	}
}

int main()
{
	char *sz = "Hello World!";
	CharSZ de(strlen(sz) + 1);		//����de������Ķ�̬�ڴ��СΪn���ɴ��n-1����Ч�ַ�������'\0'��

	//��sz�����ݸ��Ƹ�de
	int i;
	for (i = 0; i < (strlen(sz) + 1); i++)
	{
		de[i] = sz[i];
	}

	//������de��ֵ
	for (i = 0; i < de.GetLen(); i++)
	{
		cout << de[i];
	}

	cout << endl;
	return 0;
}

