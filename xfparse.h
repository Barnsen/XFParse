#pragma once

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

/*

	This is XFParse. A simple to use fileparser.

	(C) Force67 2016
*/

#undef max

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
	std::vector < std::string > catche;

	bool catcheexists = false;
	bool generatedbefore = false;
	bool is_empty(std::string open)
	{
		std::ifstream pFile(open);
		return pFile.peek() == std::ifstream::traits_type::eof();
	}
	bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
	void erase(std::vector<string>& v, string str)
	{
		std::vector<string>::iterator iter = v.begin();

		while (iter != v.end())
		{
			if (*iter == str)
				iter = v.erase(iter);
			else
				iter++;
		}
	}
public:
	bool open(char * filename)
	{
		std::string a(filename);
		if (Exists(filename) && !is_empty(a))
		{
			openfile = a;
			return true;
		}
		return false;
	}
	void refresh()
	{
		token.clear();
		catche.clear();
		generatedbefore = false;
		catcheexists = false;
	}
	std::string GetElement(std::string element)
	{
			//if its opened
			if (openfile != "FF" && !is_empty(openfile))
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
							//return line.substr(line.find(":") + 1, line.length() - 1);
							return removebrakets.substr(removebrakets.find(":") + 1, removebrakets.length() - 1);
						}}}
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
	/*
		Set Current Var to new value
		TODO : save position of variable in file.
	*/
	template <typename T>
	bool SetElement(std::string element, T newvar)
	{
		if (openfile != "FF" && !is_empty(openfile))
		{
			std::ifstream file(openfile);
			std::string line;

			if (!catcheexists)
			{
				int count = 0;
				while (std::getline(file, line))
				{
					catche.push_back(line);
					count++;
				}
				catcheexists = true;
			}
			for (std::string a : catche)
			{
				if (strstr(a.c_str(), element.c_str()))
				{
					
					erase(catche, a);

					replace(a, GetElement(element), newvar);

					catche.push_back(a);

					std::ofstream off(openfile);
					for (std::string b : catche)
					{
						off << b << std::endl;
					}
					off.close();
				}}}
	}
	/*
		Set new value
		TODO: finish
	*/
	template <typename R>
	bool SetNewElement(std::string newelement, R newvar)
	{
		if (openfile != "FF" && !is_empty(openfile))
		{
			std::ifstream file(openfile);
			std::string line;

			if (!catcheexists)
			{
				int count = 0;
				while (std::getline(file, line))
				{
					catche.push_back(line);
					count++;
				}
				catcheexists = true;
			}
		//	std::string firstline = 
			
		}
	}

};