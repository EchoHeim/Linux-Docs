#include <iostream>
using namespace std;

const int Number = 1,n = 10;      //����ֻ������

int main(void)
{
	int a ;
	const int * p;                //����ָ�� ��ָ��p��ָ��ĳ��������޸ģ����ǿ��Ըı�ָ��p��ָ��
	p = &Number;
	p = &n;
	//*p = 5;   //����
	//n = 5;    //����
                                 
	int n1 = 3;                   
	int const n2 = 5;             //ע�⣨int const  ��const int��д����һ���ģ�
	int * const pn = &n1;         //ָ�볣����ָ��pn��ָ��ı����ǿ��Ը��µģ����ɸ��µ���ָ��pn��ָ��ķ���
	//pn = &n2;   //����
	//n2 = 6;     //����
	*pn = 6;
	
	cout<<"n = "<<n<<endl;
	cout<<"n1 = "<<n1<<endl;
	return 0;
}
