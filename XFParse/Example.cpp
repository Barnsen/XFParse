
#include <Windows.h>
#include <iostream>
#include <string>
#include <sys/stat.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "..\xfparse.h"

XFParse parse;

int main()
{
	cout << "XFParse Example : " << endl;
	parse.open("Example.xf");
	cout << parse.GetElement("Name") << endl;
	int age = parse.GetIntElement("Age");
	cout << age << endl;
	cout << parse.GetElement("Day") << endl;
	float Prec = parse.GetFloatElement("Precision");
	cout << Prec << endl;

	system("pause");
}