#pragma warning(disable : 4996)

#include "FileLoader.h"

//#include <Python.h>

#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <locale>
#include <codecvt>


//#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
//#define _CRT_SECURE_NO_WARNINGS

using namespace std::literals;



//void FileHandler::RunPythonScript(int argc, const char* argv[])
//{
//	wchar_t* program = Py_DecodeLocale(argv[0], NULL);
//
//	if (program == NULL)
//	{
//		exit(1);
//	}
//
//	//Py_SetProgramName(program);
//
//	Py_Initialize();
//
//	//PyConfig config;
//	//PyConfig_InitPythonConfig(&config);
//	//config.isolated = 1;
//	////std::filesystem::path cwd;
//	////cwd = std::filesystem::current_path();
//	////cwd.c_str();
//	//wchar_t pyPath[] = { L'\\Python\\' };
//	//config.pythonpath_env = pyPath;
//
//	PyObject* obj = Py_BuildValue("s", "Tables.py");
//	FILE* file = _Py_fopen_obj(obj, "r+");
//
//	a = PyRun_SimpleFile(file, "Tables.py");
//	std::cout << a;
//
//	//PyRun_SimpleFileExFlags(file, "Tables.py", 1, )
//
//	/*if (file != NULL) 
//	{
//	}*/
//
//	if (Py_FinalizeEx() < 0)
//	{
//		exit(120);
//	}
//
//	PyMem_RawFree(program);
//
//}

void FileHandler::ReadTsvFiles(std::vector<Module>& inModules)
{
	std::filesystem::path pathToCwd = std::filesystem::current_path();
	std::filesystem::path pathToTables = pathToCwd / "Tables";
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::vector<Module> readModules;

	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(pathToTables))
	{

		if (dirEntry.exists())
		{
			std::filesystem::path filePath = dirEntry.path();
			std::string strFilePath = filePath.string();
			std::string baseFilename = strFilePath.substr(strFilePath.find_last_of("/\\") + 1);
			std::string::size_type const p(baseFilename.find_last_of('.'));
			std::string fileWithoutExtention = baseFilename.substr(0, p);
			//std::wstring wFilePath = std::wstring(filePath);
			//std::wstring revFilePath = 
			//std::wstring wBaseName = wFilePath.substr(wFilePath.find_last_of("/\\") + 1)
			//std::string strFilePath = filePath.string();
			/*std::string baseFilename = strFilePath.substr(strFilePath.find_last_of("/\\") + 1);
			std::string::size_type const p(baseFilename.find_last_of('.'));
			std::string fileWithoutExtention = baseFilename.substr(0, p);
			std::wstring wFileWithoutExtention;
			wFileWithoutExtention = converter.from_bytes(fileWithoutExtention.c_str());*/
			

			/*int wchars_num = MultiByteToWideChar(CP_UTF8, 0, fileWithoutExtention.c_str(), -1, NULL, 0);
			wchar_t* wFileWithoutExtention = new wchar_t[wchars_num];
			MultiByteToWideChar(CP_UTF8, 0, fileWithoutExtention.c_str(), -1, wFileWithoutExtention, wchars_num);
			std::wstring wFileName(wFileWithoutExtention);*/

			readModules.push_back(Module{ fileWithoutExtention });
			moduleCounter++;
			
			//delete[] wFileWithoutExtention;

			std::wifstream infile(dirEntry.path());
			infile.imbue(std::locale("en_US.UTF8"));
			std::wstring line;
			std::vector<std::wstring> allFileContents;

			while (std::getline(infile, line))
			{
				SplitWide(line, '\t', allFileContents);
			}

			allFileContents.erase(allFileContents.begin(), allFileContents.begin() + 13);
			allFileContents.shrink_to_fit();

			
			for (int i = 0; i < allFileContents.size(); i += 6)
			{
				readModules[moduleCounter].AddToWords(Symbol{ allFileContents[i], allFileContents[i + 1], allFileContents[i + 2] });
				readModules[moduleCounter].AddToKanji(Symbol{ allFileContents[i + 3], allFileContents[i + 4], allFileContents[i + 5] });
			}
		}
	}



	inModules = readModules;
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


//void FileHandler::ReadTablesFile(std::vector<Module>& modules)
//{
//	std::wifstream infile("./Tables/PyOutput.txt");
//	infile.imbue(std::locale("en_US.UTF8"));
//	std::wstring line;
//	std::vector<std::wstring> allFileContents;
//
//	while (std::getline(infile, line))
//	{
//		
//		SplitWide(line, '\t', allFileContents);
//
//	}
//	
//	int moduleCounter = -1; //counts modules in the for loop for referencing
//	int size = allFileContents.size();
//
//	for (size_t i = 0; i < size; i++)
//	{
//		if (allFileContents[i].at(0) == '@')
//		{
//			modules.push_back(Module{ allFileContents[i].substr(1) });
//			moduleCounter++;
//		}
//
//		else if (allFileContents[i].at(0) == '#')
//		{
//			modules[moduleCounter].SetFromFile(allFileContents[i].substr(1));
//		}
//
//		else if (allFileContents[i].at(0) == '!')
//		{
//			modules[moduleCounter].AddToWords(Symbol{ allFileContents[i].substr(1), 
//				allFileContents[i + 1],allFileContents[i + 2] });
//		}
//		
//		else if (allFileContents[i].at(0) == '?')
//		{
//			modules[moduleCounter].AddToKanji(Symbol{ allFileContents[i].substr(1), 
//				allFileContents[i + 1],allFileContents[i + 2] });
//		}
//
//		else
//		{
//			continue;
//		}
//
//	}
//
//
//}

//void FileHandler::LoadModuleStats(std::vector<Module>& inModules)
//{
//	
//
//	std::wifstream infile("./Settings/stats.tsv");
//	//infile.imbue(std::locale("en_US.UTF8"));
//	std::wstring line;
//	std::vector<std::wstring> statsFileContents;
//
//	while (std::getline(infile, line))
//	{
//
//		SplitWide(line, '\t', statsFileContents);
//
//	}
//
//	
//	for (auto mod : inModules)
//	{
//		int size = statsFileContents.size();
//		for (size_t i = 0; i < size; i += 4)
//		{
//			if (statsFileContents[i] == mod.GetFileName() &&
//				statsFileContents[i + 1] == mod.GetModuleName())
//			{
//				mod.timesAsked = stoi(statsFileContents[i + 2]);
//				mod.answeredCorrectly = stoi(statsFileContents[i + 3]);
//
//			}
//		}
//	}
//}


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



void FileHandler::UpdateUserSettingsMap(std::string inSetting, std::string inOption,
	std::unordered_map<std::string, std::string>& userSettings)
{
	for (auto iter = userSettings.begin(); iter != userSettings.end(); ++iter)
		if (iter->first == inSetting)
		{
			iter->second = inOption;
		}
	UpdateUserSettingsFile(userSettings);
}

void FileHandler::UpdateUserSettingsFile(std::unordered_map<std::string, std::string>& userSettings)
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

void FileHandler::SaveStatsToFile(std::vector<Module>& modules)
{
	std::wofstream outfile;
	outfile.open("./Settings/stats.tsv");

	if (!outfile.fail())
	{
		for (auto mod : modules)
		{
			outfile << mod.GetFileName() << '\t' << mod.GetModuleName() << '\t' << 
							mod.GetTimesAsked() << '\t' << mod.GetAnsweredCorrectly() << '\n';
		}
	}
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


Symbol::Symbol(std::wstring inSymbol, std::wstring inReading, std::wstring inMeaning)
	:
	symbol(inSymbol),
	reading(inReading),
	meaning(inMeaning)
{
}

std::wstring& Symbol::GetSymbol()
{
	return symbol;
}

std::wstring& Symbol::GetReading()
{
	return reading;
}

std::wstring& Symbol::GetMeaning()
{
	return meaning;
}

void Symbol::SetIsLearnt(bool inIsLearnt)
{
	isLearnt = inIsLearnt;
}

Module::Module(std::string inModuleName)
	:
	moduleName(inModuleName)
{
}

Module::Module(std::wstring inFromFile, std::wstring inModuleName)
	:
	fromFile(inFromFile)
	//moduleName(inModuleName)
{
}

void Module::AddToWords(Symbol inWord)
{
	wordList.push_back(inWord);
}

void Module::AddToKanji(Symbol inKanji)
{
	kanjiList.push_back(inKanji);
}

void Module::SetFromFile(std::wstring inFromFile)
{
	fromFile = inFromFile;
}

void Module::SetModuleName(std::wstring inModuleName)
{
	//moduleName = inModuleName;
}

std::wstring& Module::GetFileName()
{
	return fromFile;
}

std::string& Module::GetModuleName()
{
	return moduleName;
}

//void Module::SetStats(int inAsked, int inCorrect)
//{
//	timesAsked += inAsked;
//	answeredCorrectly += inCorrect;
//}

std::vector<Symbol>& Module::GetWordList()
{
	return wordList;
}

int Module::GetAnsweredCorrectly()
{
	return answeredCorrectly;
}

int Module::GetTimesAsked()
{
	return timesAsked;
}

std::vector<Symbol>& Module::GetKanjiList()
{
	return kanjiList;
}
