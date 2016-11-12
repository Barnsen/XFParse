#pragma once

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

class XFParse
{
private:
	bool is_digits(const std::string &str)
	{
		return str.find_first_not_of("0123456789") == std::string::npos;
	}
	bool Exists(char * file)
	{
		struct stat fileStat;
		if (stat(file, &fileStat) == 0)
		{
			return true;
		}
		return false;
	}
	std::vector < std::string > token;
	std::string openfile = "FF";
	bool generatedbefore = false;
public:
	bool open(char * filename)
	{
		if (Exists(filename))
		{
			std::string a(filename);
			openfile = a;
			return true;
		}
		return false;
	}
	void refresh()
	{
		generatedbefore = false;
	}
	std::string GetElement(std::string element)
	{
			//if its opened
			if (openfile != "FF")
			{
				std::ifstream file(openfile);
				std::string str;

				//string to token, so it doesnt break the getline.,..
				if (!generatedbefore)
				{
					while (std::getline(file, str))
					{
						token.push_back(str);
					}
					generatedbefore = true;
				}
				for (std::string line : token)
				{
						// Process str
						if (strstr(line.c_str(), element.c_str()))
						{
							//delete all spaces
							line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

							//remove the "< and >" //this is not ideal yet
							std::string removebrakets = line.substr(1, line.length() - 2);

							//find pos of ":"

							std::string bformat = removebrakets.substr(removebrakets.find(":") + 1, removebrakets.length() - 1);
							return bformat;
				
				}
			}
		}
	}
	/*
	  Variable Conversions.
	*/
	int GetIntElement(std::string element)
	{
		return std::stoi(GetElement(element));
	}
	float GetFloatElement(std::string element)
	{
		return (float)::atof(GetElement(element).c_str());
	}
	double GetDoubleElement(std::string element)
	{
		return ::atof(GetElement(element).c_str());
	}
};