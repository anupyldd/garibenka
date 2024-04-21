#pragma once

#define _NO_CRT_STDIO_INLINE

#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <wx/wx.h>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <exception>

#define PY_SSIZE_T_CLEAN



class Symbol
{
private:
	std::wstring symbol = L"phSymbol";
	std::wstring reading = L"phReading";
	std::wstring meaning = L"phMeaning";
	bool isLearnt = false;

public:
	Symbol(std::wstring inSymbol, std::wstring inReading, std::wstring inMeaning);

	std::wstring& GetSymbol();
	std::wstring& GetReading();
	std::wstring& GetMeaning();

	void SetIsLearnt(bool inIsLearnt);
};


class Module
{
private:
	std::wstring fromFile;
	std::string moduleName;
	std::vector<Symbol> wordList;
	std::vector<Symbol> kanjiList;


public:

	int timesAsked = 0;			// how many symbols from module were asked
	int answeredCorrectly = 0;	// how many of those symbols were answered correctly

	Module() = default;
	Module(std::string inModuleName);
	Module(std::wstring inFromFile, std::wstring inModuleName);

	void AddToWords(Symbol inWord);
	void AddToKanji(Symbol inKanji);

	void SetFromFile(std::wstring inFromFile);
	void SetModuleName(std::wstring inModuleName);

	//void SetStats(int inAsked, int inCorrect);

	std::wstring& GetFileName();
	std::string& GetModuleName();

	std::vector<Symbol>& GetWordList();
	std::vector<Symbol>& GetKanjiList();

	int GetTimesAsked();
	int GetAnsweredCorrectly();

};




class FileHandler
{
private:

	

public:
	

	static void ReadTsvFiles(std::vector<Module>& modules);

	static void Split(const std::string& s, char delim, std::vector<std::string>& elems);
	static void SplitWide(const std::wstring& s, wchar_t delim, std::vector<std::wstring>& elems);
	//static void ReadTablesFile(std::vector<Module>& modules);


	static void ReadUserSettingsFile(std::unordered_map<std::string, std::string>& userSettings);
	static void UpdateUserSettingsMap(std::string inSetting, std::string inOption, 
		std::unordered_map<std::string, std::string>& userSettings); // inSetting - setting name, inOption - chosen option to replace
	static void UpdateUserSettingsFile(std::unordered_map<std::string, std::string>& userSettings);

	static void ReadLocFile(std::unordered_map<std::wstring, std::wstring>& currentLang,
								const std::unordered_map<std::string, std::string> userSettings);

	static void SaveStatsToFile(std::vector<Module>& modules);
	
};

//stores modules
static std::vector<Module> modules;

//stores user settings
static std::unordered_map<std::string, std::string> userSettings;

//LOC DATA
//stores current selected language
static std::unordered_map<std::wstring, std::wstring> currentLang;

static int moduleCounter = -1;