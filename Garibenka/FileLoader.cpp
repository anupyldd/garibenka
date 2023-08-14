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
#include "sutfcpplib/utf_string.h"

using namespace std::literals;



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

void FileHandler::SplitWide(const std::wstring& s, wchar_t delim, std::vector<std::wstring>& elems)
{
	std::wstringstream sStream;
	sStream.str(s);
	std::wstring item;
	while (std::getline(sStream, item, delim))
	{
		elems.push_back(item);
	}
}


void FileHandler::ReadTablesFile(std::vector<Module>& modules)
{
	std::wifstream infile("./Tables/PyOutput.txt");
	infile.imbue(std::locale("en_US.UTF8"));
	std::wstring line;
	std::vector<std::wstring> allFileContents;

	while (std::getline(infile, line))
	{
		
		SplitWide(line, '\t', allFileContents);

	}
	
	
	for (auto entry : allFileContents)
	{
		if (entry.at(0) == '@')
		{
			modules.push_back(Module{ entry.substr(1) });
		}

	}

}


void FileHandler::ReadUserSettingsFile(std::unordered_map<std::string, std::string>& userSettings)
{
	std::ifstream infile("./Settings/settings.tsv");
	std::string line;
	std::vector<std::string> settingsFileContents;

	while (std::getline(infile, line))
	{

		Split(line, '\t', settingsFileContents);

	}
	
	int size = settingsFileContents.size();
	for (size_t i = 0; i < size; i+=2)
	{
		userSettings[settingsFileContents[i]] = settingsFileContents[i + 1];
	}

}

void FileHandler::UpdateUserSettingsMap(std::string inSetting, std::string inOption)
{
	for (auto iter = userSettings.begin(); iter != userSettings.end(); ++iter)
		if (iter->first == inSetting)
		{
			iter->second = inOption;
		}
	UpdateUserSettingsFile();
}

void FileHandler::UpdateUserSettingsFile()
{
	std::ofstream outfile;
	outfile.open("./Settings/settings.tsv");

	if (!outfile.fail())
	{
		for (auto iter = userSettings.begin(); iter != userSettings.end(); iter++)
		{
			outfile << iter->first << '\t' << iter->second << '\n';
		}
	}

	outfile.close();
}

void FileHandler::ReadLocFile(std::unordered_map<std::wstring, std::wstring>& currentLang,
								const std::unordered_map<std::string, std::string> userSettings)
{
	std::wifstream infile("./Settings/loc.tsv");
	infile.imbue(std::locale("en_US.UTF8"));
	std::wstring line;
	std::vector<std::wstring> locFileContents;

	while (std::getline(infile, line))
	{
		SplitWide(line, '\t', locFileContents);
	}

	int size = locFileContents.size();

	// loads lang according to settings, English by default
	if (userSettings.at("Language") == "ru")
	{
		for (size_t i = 0; i < size; i += 3)
		{
			currentLang[locFileContents[i]] = locFileContents[i + 1];
		}

	}
	else
	{
		for (size_t i = 0; i < size; i += 3)
		{
			currentLang[locFileContents[i]] = locFileContents[i + 2];
		}
	}

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

Module::Module(std::wstring inModuleName)
	:
	moduleName(inModuleName)
{
}

Module::Module(std::wstring inFromFile, std::wstring inModuleName)
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

void Module::SetFromFile(std::wstring& inFromFile)
{
	fromFile = inFromFile;
}

void Module::SetModuleName(std::wstring& inModuleName)
{
	moduleName = inModuleName;
}

std::wstring& Module::GetFileName()
{
	return fromFile;
}

std::wstring& Module::GetModuleName()
{
	return moduleName;
}
