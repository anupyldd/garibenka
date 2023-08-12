#include "FileLoader.h"

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


void FileHandler::RunPythonScript(int argc, const char* argv[])
{
	wchar_t* program = Py_DecodeLocale(argv[0], NULL);

	if (program == NULL)
	{
		exit(1);
	}

	//Py_SetProgramName(program);

	Py_Initialize();

	//PyRun_SimpleString("exec('Tables.py')");

	PyObject* obj = Py_BuildValue("s", "Tables.py");
	FILE* file = _Py_fopen_obj(obj, "r+");
	if (file != NULL) 
	{
		PyRun_SimpleFile(file, "Tables.py");
	}

	if (Py_FinalizeEx() < 0)
	{
		exit(120);
	}

	PyMem_RawFree(program);

}

void FileHandler::Split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream sStream;
	sStream.str(s);
	std::string item;
	while (std::getline(sStream, item, delim))
	{
		elems.push_back(item);
	}
}


void FileHandler::ReadTablesFile()
{
	std::ifstream infile("./Tables/PyOutput.txt");
	std::string line;
	std::vector<std::string> allFileContents;

	while (std::getline(infile, line))
	{
		
		Split(line, '\t', allFileContents);

		for (auto v : allFileContents)
			std::cout << v << ',';

		std::cout << std::endl;
	}
}


void FileHandler::ReadUserSettingsFile()
{
}


Symbol::Symbol(std::string inSymbol, std::string inReading, std::string inMeaning)
	:
	symbol(inSymbol),
	reading(inReading),
	meaning(inMeaning)
{
}

std::string_view Symbol::GetSymbol()
{
	return symbol;
}

std::string_view Symbol::GetReading()
{
	return reading;
}

std::string_view Symbol::GetMeaning()
{
	return meaning;
}

void Symbol::SetIsLearnt(bool inIsLearnt)
{
	isLearnt = inIsLearnt;
}

Module::Module(std::string inFromFile, std::string inModuleName)
	:
	fromFile(inFromFile),
	moduleName(inModuleName)
{
}

void Module::AddToWords(Symbol& inWord)
{
	wordList.push_back(inWord);
}

void Module::AddToKanji(Symbol& inKanji)
{
	kanjiList.push_back(inKanji);
}

std::string_view Module::GetFileName()
{
	return fromFile;
}

std::string_view Module::GetModuleName()
{
	return moduleName;
}
