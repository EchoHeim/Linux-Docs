//��ϻ��Ǽ̳�
#include <iostream>
using namespace std;

class Eye      //�۾�
{
public:
	void Look() {cout << "Eye.Look()." << endl;}
};
class Nose    //����
{
public:
	void Smell() {cout << "Nose.Smell()." << endl;}
};
class Mouth  //��
{
public:
	void Eat() {cout << "Mouth.Eat()." << endl;}
};
class Ear   //����
{
public:
	void Listen() {cout << "Ear.Listen()." << endl;}
};

//��Ϸ�ʽ���߼���������������չ�ܷ��㡣
class Head
{
private:
	Eye m_eye;
	Nose m_nose;
	Mouth m_mouth;
	Ear m_ear;
public:
	void Look()
	{
		m_eye.Look();
	}
	void Smell()
	{
		m_nose.Smell();
	}
	void Eat()
	{
		m_mouth.Eat();
	}
	void Listen()
	{
		m_ear.Listen();
	}
};

//�̳з�ʽ�����������ƴ����ܶ��߼��ϵ�����
class HeadX : public Eye, public Nose, public Mouth, public Ear
{
};

int main()
{
	Head h;
	h.Look();
	h.Smell();
	h.Eat();
	h.Listen();
	
	cout << endl;

	HeadX hx;
	hx.Look();
	hx.Smell();
	hx.Eat();
	hx.Listen();

	cout << endl;

	return 0;
}

