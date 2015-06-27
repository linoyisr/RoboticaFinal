
/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

void ConfigurationManager::removeComment(string &line) const
{
	if (line.find(';') != line.npos)
		line.erase(line.find(';'));
}

bool ConfigurationManager::onlyWhitespace(const string &line) const
{
	return (line.find_first_not_of(' ') == line.npos);
}

bool ConfigurationManager::validLine(const string &line) const
{
	string temp = line;
	temp.erase(0, temp.find_first_not_of("\t "));
	if (temp[0] == ':')
		return false;

	for (size_t i = temp.find(':') + 1; i < temp.length(); i++)
		if (temp[i] != ' ')
			return true;

	return false;
}

void ConfigurationManager::extractKey(string &key, size_t const &sepPos, const string &line) const
{
	key = line.substr(0, sepPos);
	if (key.find('\t') != line.npos || key.find(' ') != line.npos)
		key.erase(key.find_first_of("\t "));
}

void ConfigurationManager::extractValue(string &value, size_t const &sepPos, const string &line) const
{
	value = line.substr(sepPos + 1);
	value.erase(0, value.find_first_not_of(" "));
	value.erase(value.find_last_not_of("\r ") + 1);
}

void ConfigurationManager::extractContents(const string &line)
{
	string temp = line;
	temp.erase(0, temp.find_first_not_of("\t "));
	size_t sepPos = temp.find(':');

	string key, value;
	extractKey(key, sepPos, temp);
	extractValue(value, sepPos, temp);

	if (!keyExists(key))
		contents.insert(pair<string, string>(key, value));
	else
		exitWithError("CFG: Can only have unique key names!\n");
}

void ConfigurationManager::parseLine(const std::string &line, size_t const lineNo)
{
	string lineNumber;
	ostringstream ss;
	ss << lineNo;
	lineNumber = ss.str();
	if (line.find(':') == line.npos)
		exitWithError("CFG: Couldn't find separator on line: " + lineNumber + "\n");

	if (!validLine(line))
		exitWithError("CFG: Bad format for line: " + lineNumber + "\n");

	extractContents(line);
}

void ConfigurationManager::ExtractKeys()
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

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager::~ConfigurationManager()
{
}

ConfigurationManager::ConfigurationManager(const string &fName)
{
	this->fName = fName;
	ExtractKeys();
}

bool ConfigurationManager::keyExists(const string &key) const
{
	return contents.find(key) != contents.end();
}

string ConfigurationManager::getValueOfKey(const string &key)
{
	if (!keyExists(key))
		return "Key not found";
	return contents[key];
}

vector<int> ConfigurationManager::ConvertStringToIntArray(string value)
{
	vector<int> array;
	stringstream ss(value);
	int temp;
	while (ss >> temp)
		array.push_back(temp);

	return array;
}


