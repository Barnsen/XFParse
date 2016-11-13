#pragma once

/*     __                           
__  __/ _|_ __   __ _ _ __ ___  ___ 
\ \/ / |_| '_ \ / _` | '__/ __|/ _ \  XFParse
 >  <|  _| |_) | (_| | |  \__ \  __/  https://github.com/Force67/XFParse
/_/\_\_| | .__/ \__,_|_|  |___/\___|
         |_|         

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2016 Force67.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef XFPARSE
#define XFPARSE

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

#ifndef OR 
#define OR ||
#endif OR

//needed to not cause errors 
#undef max

class XFParse
{
private:
	/// Is number ?
	bool is_digits(const std::string &str)
	{
		return str.find_first_not_of("0123456789") == std::string::npos;
	}
	/// Does file exist ?
	bool Exists(char * file)
	{
		struct stat fileStat;
		if (stat(file, &fileStat) == 0)
		{
			return true;
		}
		return false;
	}

	//values
	std::vector < std::string > token;
	std::string openfile = "FF";
	std::vector < std::string > catche;

	int hitvalue = 0;

	bool catcheexists = false;
	bool generatedbefore = false;

	///is file null
	bool is_empty(std::string open)
	{
		std::ifstream pFile(open);
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	//replace given text at given pos
	bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	//delete string from stringvector
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
	//refresh the value containers
	void refresh()
	{
		token.clear();
		catche.clear();
		generatedbefore = false;
		catcheexists = false;
	}
	//get value as string
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

						//remove the "< and >" //we can use the static numbers regardless
						//cause we wont have any spaces anyway anymore.
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
	bool GetBoolElement(std::string element)
	{
		std::string result = GetElement(element);
		if (result == "true" OR result == "True")
		{
			return true;
		}
		return false;
	}
	/*
		Set Current Var to new value
	*/
	template <typename T>
	bool SetElement(std::string element, T newvar)
	{
		if (openfile != "FF" && !is_empty(openfile))
		{
			std::ifstream file(openfile);
			std::string line;

			//write whole file into catche
			if (!catcheexists)
			{
				while (std::getline(file, line))
				{
					catche.push_back(line);
				}
				catcheexists = true;
			}

			//the catche has the file in it line by line from top.

			if (element != GetElement(element))
			{
				//rebuild file without old line and 
				//insert new (changed) line
				for (std::string a : catche)
				{
					if (strstr(a.c_str(), element.c_str()))
					{

						std::string b = a;
						replace(b, GetElement(element), newvar);

						std::replace(catche.begin(), catche.end(), a, b);
		
						std::ofstream off(openfile);
						for (std::string a : catche)
						{
							off << a << std::endl;
						}
						off.close();
					}} return true ; } 
				else
				return false;
		}
		return false;
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
				while (std::getline(file, line))
				{
					catche.push_back(line);
				}
				catcheexists = true;
			}
			//get first line of file and copy newvar in temp
			std::ifstream iff(openfile);
			std::string temp;
			std::getline(iff, temp);

			//todo make mask and place value + copy


			//add new line at end of file
			std::ofstream off(openfile);
			for (std::string a : catche)
			{
				off << a << std::endl;
			}
			off << temp << std::endl;
			off.close();
			
		}
	}

};

#endif XFPARSE