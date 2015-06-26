/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

class ConfigurationManager {
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

	void removeComment(string &line) const;
	bool onlyWhitespace(const string &line) const;
	bool validLine(const string &line) const;
	void extractKey(string &key, size_t const &sepPos, const string &line) const;
	void extractValue(string &value, size_t const &sepPos, const string &line) const;
	void extractContents(const string &line);
	void parseLine(const std::string &line, size_t const lineNo);
	void ExtractKeys();

public:
	ConfigurationManager();
	ConfigurationManager(const string &fName);
	virtual ~ConfigurationManager();
	bool keyExists(const string &key) const;
	string getValueOfKey(const string &key);
};

#endif /* CONFIGURATIONMANAGER_H_ */
