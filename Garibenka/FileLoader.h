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
#include "sutfcpplib/utf_string.h"

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
	std::wstring fromFile;
	std::wstring moduleName;
	std::vector<Symbol> wordList;
	std::vector<Symbol> kanjiList;

	int timesAsked = 0;			// how many symbols from module were asked
	int answeredCorrectly = 0;	// how many of those symbols were answered correctly

public:
	Module() = default;
	Module(std::wstring inModuleName);
	Module(std::wstring inFromFile, std::wstring inModuleName);

	void AddToWords(Symbol& inWord);
	void AddToKanji(Symbol& inKanji);

	void SetFromFile(std::wstring& inFromFile);
	void SetModuleName(std::wstring& inModuleName);

	std::wstring& GetFileName();
	std::wstring& GetModuleName();
};




class FileHandler
{

public:
	

	static void RunPythonScript(int argc, const char* argv[]);

	static void Split(const std::string& s, char delim, std::vector<std::string>& elems);
	static void SplitWide(const std::wstring& s, wchar_t delim, std::vector<std::wstring>& elems);
	static void ReadTablesFile(std::vector<Module>& modules);

	static void LoadModuleStats();
	static void UpdateModuleStatsFile();

	static void ReadUserSettingsFile(std::unordered_map<std::string, std::string>& userSettings);
	static void UpdateUserSettingsMap(std::string inSetting, std::string inOption); // inSetting - setting name, inOption - chosen option to replace
	static void UpdateUserSettingsFile();

	static void ReadLocFile(std::unordered_map<std::wstring, std::wstring>& currentLang,
								const std::unordered_map<std::string, std::string> userSettings);


	
};

//stores modules
static std::vector<Module> moduleVector;

//stores user settings
static std::unordered_map<std::string, std::string> userSettings;

//LOC DATA
//stores current selected language
static std::unordered_map<std::wstring, std::wstring> currentLang;