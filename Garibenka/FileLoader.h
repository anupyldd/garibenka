#pragma once

//#include <C:/Program Files/Python311/include/Python.h>  //put it in properties additional include libs

#include <Python.h>

#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#define PY_SSIZE_T_CLEAN

class FileLoader
{
private:
	
	class Symbol
	{
	private:
		std::string symbol = "phSymbol";
		std::string reading = "phReading";
		std::string meaning = "phMeaning";
		bool isLearnt = false;

	public:
		Symbol(std::string inSymbol, std::string inReading, std::string inMeaning);
		
		virtual std::string_view GetSymbol() = 0;
		virtual std::string_view GetReading() = 0;
		virtual std::string_view GetMeaning() = 0;

		virtual void SetIsLearnt() = 0;
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

		virtual void AddToWords() = 0;
		virtual void AddToKanji() = 0;

		virtual std::string_view GetFileName() = 0;
		virtual std::string_view GetModuleName() = 0;
	};


public:
	//std::unordered_map<std::string, std::string> 

	static void RunPythonScript(int argc, const char* argv[]);
	static void ReadTablesFile();

	static void ReadUserSettingsFile();


};