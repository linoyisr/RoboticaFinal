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
	string T_to_string(T const &val);
	template <typename T>
	T string_to_T(string const &val)
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

	void removeComment(string &line) const;
	bool onlyWhitespace(const string &line) const;
	bool validLine(const string &line) const;
	void extractKey(string &key, size_t const &sepPos, const string &line) const;
	void extractValue(string &value, size_t const &sepPos, const string &line) const;
	void extractContents(const string &line);
	void parseLine(const std::string &line, size_t const lineNo);
	void ExtractKeys();

public:
	Configuration();
	Configuration(const string &fName);
	virtual ~Configuration();
	bool keyExists(const string &key) const;

	template <typename ValueType>
	ValueType getValueOfKey(const string &key)
	{
		if (!keyExists(key))
			return ValueType();
		return string_to_T<ValueType>(contents.find(key)->second);
	}
};

#endif /* CONFIGURATION_H_ */
