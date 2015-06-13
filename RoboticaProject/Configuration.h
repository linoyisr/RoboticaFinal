/*
 * Configuration.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

class Configuration {
private:
	map<string, string> contents;
	string fName;

	void exitWithError(const string &error)
	{
		cout << error;
		cin.ignore();
		cin.get();

		exit(EXIT_FAILURE);
	}

	template <typename T>
	static string T_to_string(T const &val)
	{
		ostringstream ostr;
		ostr << val;

		return ostr.str();
	}

	template <typename T>
	static T string_to_T(string const &val)
	{
		istringstream istr(val);
		T returnVal;
		if (!(istr >> returnVal))
		{
			string name = (string)typeid(T).name();
			exitWithError("CFG: Not a valid " + name + " received!\n");
		}

		return returnVal;
	}

	template<typename T>
	static string string_to_T(string const &val)
	{
		return val;
	}

	void removeComment(string &line) const
	{
		if (line.find(';') != line.npos)
			line.erase(line.find(';'));
	}

	bool onlyWhitespace(const string &line) const
	{
		return (line.find_first_not_of(' ') == line.npos);
	}

	bool validLine(const string &line) const
	{
		string temp = line;
		temp.erase(0, temp.find_first_not_of("\t "));
		if (temp[0] == '=')
			return false;

		for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
			if (temp[i] != ' ')
				return true;

		return false;
	}

	void extractKey(string &key, size_t const &sepPos, const string &line) const
	{
		key = line.substr(0, sepPos);
		if (key.find('\t') != line.npos || key.find(' ') != line.npos)
			key.erase(key.find_first_of("\t "));
	}

	void extractValue(string &value, size_t const &sepPos, const string &line) const
	{
		value = line.substr(sepPos + 1);
		value.erase(0, value.find_first_not_of("\t "));
		value.erase(value.find_last_not_of("\t ") + 1);
	}

	void extractContents(const string &line)
		{
			string temp = line;
			temp.erase(0, temp.find_first_not_of("\t "));
			size_t sepPos = temp.find('=');

			string key, value;
			extractKey(key, sepPos, temp);
			extractValue(value, sepPos, temp);

			if (!keyExists(key))
				contents.insert(pair<string, string>(key, value));
			else
				exitWithError("CFG: Can only have unique key names!\n");
		}

	void parseLine(const std::string &line, size_t const lineNo)
	{
		if (line.find('=') == line.npos)
			exitWithError("CFG: Couldn't find separator on line: " + T_to_string(lineNo) + "\n");

		if (!validLine(line))
			exitWithError("CFG: Bad format for line: " + T_to_string(lineNo) + "\n");

		extractContents(line);
	}

	void ExtractKeys()
	{
		ifstream file;
		file.open(fName.c_str());
		if (!file)
			exitWithError("CFG: File " + fName + " couldn't be found!\n");

		string line;
		size_t lineNo = 0;
		while (getline(file, line))
		{
			lineNo++;
			string temp = line;

			if (temp.empty())
				continue;

			removeComment(temp);
			if (onlyWhitespace(temp))
				continue;

			parseLine(temp, lineNo);
		}

		file.close();
	}

public:
	Configuration();
	virtual ~Configuration();

	Configuration(const string &fName)
	{
		this->fName = fName;
		ExtractKeys();
	}

	bool keyExists(const string &key) const
	{
		return contents.find(key) != contents.end();
	}

	template <typename ValueType>
	ValueType getValueOfKey(const string &key, ValueType const &defaultValue = ValueType()) const
	{
		if (!keyExists(key))
			return defaultValue;

		return string_to_T<ValueType>(contents.find(key)->second);
	}

};

#endif /* CONFIGURATION_H_ */
