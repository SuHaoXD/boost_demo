#pragma once

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <string>
#pragma warning(disable: 4251)
using namespace std;

class  Animal
{
public:
	Animal();
	Animal(string ID, string name, unsigned short age, char sex);
	virtual void PrintInfo()const = 0;
	virtual ~Animal() {}

	void setID(string ID);
	string getID()const;

	void setName(string name);
	string getName()const;

	void setAge(unsigned short age);
	unsigned short getAge()const;

	void setSex(char sex);
	char getSex()const;

private:
	string ID;
	string name;
	unsigned short age;
	char sex;
};

class Panda : public Animal
{
public:
	Panda();
	Panda(string ID, string name, unsigned short age, char sex);
	Panda(Panda &other);

	~Panda();

	void PrintInfo();
};

class DLL_EXPORT Human : public Animal
{
public:
	Human();
	Human(string id, string name, unsigned short age, char sex, string id_number, string company_name);
	Human(const Human &other);

	~Human();

	void setId_number(string id_number);
	string getId_number()const;

	void setCompany_name(string company_name);
	string getCompany_name()const;

	void PrintInfo()const;

	bool operator<(const Human &other) const;
private:
	string id_number;
	string company_name;
};
