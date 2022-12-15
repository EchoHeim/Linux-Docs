//组合还是继承
#include <iostream>
using namespace std;

class Eye      //眼睛
{
public:
	void Look() {cout << "Eye.Look()." << endl;}
};
class Nose    //鼻子
{
public:
	void Smell() {cout << "Nose.Smell()." << endl;}
};
class Mouth  //嘴
{
public:
	void Eat() {cout << "Mouth.Eat()." << endl;}
};
class Ear   //耳朵
{
public:
	void Listen() {cout << "Ear.Listen()." << endl;}
};

//组合方式：逻辑很清晰，后续扩展很方便。
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

//继承方式，会给后续设计带来很多逻辑上的问题
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

