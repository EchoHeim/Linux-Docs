//��ֵ���������
#include <iostream>
#include <cstring>
using namespace std;

class computer
{
private:
	char *brand;						//�ַ�ָ��brand
	float price;
public:
	computer()							//�޲ι��캯��
	{
		brand = NULL;					//brand��ʼ��ΪNULL
		price = 0;
		cout << "�޲ι��캯��������" << endl;
	}
	computer(const char* sz,float p)
	{
		brand = new char[strlen(sz)+1];	//���캯����Ϊbrand����һ�鶯̬�ڴ�
		strcpy(brand, sz);				//�ַ�������
		price = p;
		cout << "���ι��캯��������" << endl;
	}
	computer(const computer& cp)		//���ƹ��캯��
	{
		brand = new char[strlen(cp.brand) + 1];	//Ϊbrand���䶯̬�ڴ�
		strcpy(brand, cp.brand);		//�ַ�������
		price = cp.price;
		cout << "���ƹ��캯��������" << endl;
	}

//	//�������û������=����ϵͳ����ʽ�����س�������ʽ:
//	computer &operator=(const computer &cp)
//	{
//		price = cp.price;
//		brand = cp.brand;
//		cout<<"ϵͳĬ�ϸ�ֵ����������"<<endl;
//		return (*this);
//	}
//
//Ӧ��ʹ����������ȡ������ϵͳ��ʽ�Ķ���
	computer &operator=(const computer &cp)		//��Ա������ʽ���ظ�ֵ�����
	{
		if (this==&cp)			//�����ж��Ƿ����Ը�ֵ���ǵĻ����ص�ǰ����
			return  (*this);

		price=cp.price;			//��������Ը�ֵ���ȶ�price��ֵ
		delete[] brand;			//��ֹ�ڴ�й¶�����ͷ�brandָ�������
		brand=new char[strlen(cp.brand)+1];		//Ϊbrand���¿���һ���ڴ�ռ�
		if (brand!=NULL)			//������ٳɹ�
		{
			strcpy(brand,cp.brand);		//�����ַ���
		}
		cout<<"��ֵ��������غ���������"<<endl;

		return  (*this);										//���ص�ǰ��������ã�Ϊ����ʵ����ʽ��ֵ
	}
	~computer()				//�����������ͷŶ�̬�ڴ棬delete[] NULL�������
	{
		delete[] brand;
		cout << "��������������" << endl;
	}
	void print()						//��Ա�����������Ϣ
	{
		cout << "Ʒ�ƣ�" << brand << endl;
		cout << "�۸�" << price << endl;
	}
};

int main()
{
	computer com1("Dell", 2000);	//���ú��ι��캯����������com1
	computer com2 = com1;			//���ø��ƹ��캯��(ע��͸�ֵ��������ص�����)

	computer com3;				    //�����޲ι��캯��
	com3 = com1;				    //���ø�ֵ��������غ���

	return 0;
}

