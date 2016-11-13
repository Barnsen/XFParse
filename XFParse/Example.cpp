
#include <Windows.h>
#include <iostream>
#include <string>
#include <sys/stat.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "..\src\xfparse.hpp"

XFParse parse;

int main()
{
	SetConsoleTitleA("XFParse Example!");
	cout << "XFParse Example : " << endl;
	parse.open("Example.xf");
	cout << parse.GetElement("Name") << endl;
	int age = parse.GetIntElement("Age");
	cout << age << endl;
	cout << parse.GetElement("Day") << endl;
	float Prec = parse.GetFloatElement("Precision");
	cout << Prec << endl;

	cout << "Setting a new age now!" << endl;
	parse.SetElement("Age", "222");

	cout << "Testing bool !" << endl;

	if (parse.GetBoolElement("Happy"))
	{
		cout << "Its a good day " << endl;
	}
	else
	{
		cout << "Its a bad day " << endl;
	}

	cout << "Creating new Element!" << endl;

	parse.SetNewElement("OldJack", "80");
	
	system("pause");
}