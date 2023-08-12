#pragma once

//#include <C:/Program Files/Python311/include/Python.h>  //put it in properties additional include libs

#include <Python.h>

#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iterator>

#define PY_SSIZE_T_CLEAN

class Symbol
{
private:
	std::string symbol = "phSymbol";
	std::string reading = "phReading";
	std::string meaning = "phMeaning";
	bool isLearnt = false;

public:
	Symbol(std::string inSymbol, std::string inReading, std::string inMeaning);

	std::string_view GetSymbol();
	std::string_view GetReading();
	std::string_view GetMeaning();

	void SetIsLearnt(bool inIsLearnt);
};


class Module
{
private:
	std::string fromFile = "phFile";
	std::string moduleName = "phModule";
	std::vector<Symbol> wordList;
	std::vector<Symbol> kanjiList;

public:
	Module(std::string inFromFile, std::string inModuleName);

	void AddToWords(Symbol& inWord);
	void AddToKanji(Symbol& inKanji);

	std::string_view GetFileName();
	std::string_view GetModuleName();
};




class FileHandler
{

public:

	static void RunPythonScript(int argc, const char* argv[]);

	static void Split(const std::string& s, char delim, std::vector<std::string>& elems);
	static void ReadTablesFile();

	static void ReadUserSettingsFile();

	/*std::string_view GetSymbol();
	std::string_view GetReading();
	std::string_view GetMeaning();

	void AddToWords();
	void AddToKanji();

	std::string_view GetFileName();
	std::string_view GetModuleName();*/
};