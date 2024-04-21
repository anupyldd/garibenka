#pragma warning(disable : 4996)

#include "FileLoader.h"

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


using namespace std::literals;


void FileHandler::ReadTsvFiles(std::vector<Module>& inModules)
{
	std::filesystem::path pathToCwd = std::filesystem::current_path();
	std::filesystem::path pathToTables = pathToCwd / "Tables";
	std::vector<Module> readModules;
	moduleCounter = -1;

	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(pathToTables))
	{

		if (dirEntry.exists())
		{
			if (dirEntry.file_size() != 0)
			{

				std::filesystem::path filePath = dirEntry.path();
				std::string strFilePath = filePath.string();
				std::string baseFilename = strFilePath.substr(strFilePath.find_last_of("/\\") + 1);
				std::string::size_type const p(baseFilename.find_last_of('.'));
				std::string fileWithoutExtention = baseFilename.substr(0, p);

				readModules.push_back(Module{ fileWithoutExtention });
				moduleCounter++;


				std::wifstream infile(dirEntry.path());
				infile.imbue(std::locale("en_US.UTF8"));
				std::wstring line;
				std::vector<std::wstring> allFileContents;

				while (std::getline(infile, line))
				{
					SplitWide(line, '\t', allFileContents);
				}

				if (allFileContents.size() > 13)
				{
					allFileContents.erase(allFileContents.begin(), allFileContents.begin() + 13);
					allFileContents.shrink_to_fit();

					for (int i = 0; i < allFileContents.size(); i += 6)
					{
						readModules[moduleCounter].AddToWords(Symbol{ allFileContents[i], allFileContents[i + 1], allFileContents[i + 2] });
						readModules[moduleCounter].AddToKanji(Symbol{ allFileContents[i + 3], allFileContents[i + 4], allFileContents[i + 5] });
					}
				}
				else
				{
					std::cout << "Wrong file structure. For more info on how files has to be structured refer to the Info section" << std::endl;
					readModules.pop_back();
					moduleCounter--;
				}


				
			}
		}
	}

	int iter = 0;
	for (auto& mod : readModules)
	{
		iter = 0;
		int wordSize = mod.GetWordList().size();
		for (int i = 0; i < wordSize; i++)
		{
			if (mod.GetWordList()[i].GetSymbol() == L"")
			{
				iter = i;
				break;
			}
		}
		if (iter != 0)
		{
			mod.GetWordList().erase(mod.GetWordList().begin() + iter, mod.GetWordList().end());
			mod.GetWordList().shrink_to_fit();
		}
		iter = 0;

		int kanjiSize = mod.GetKanjiList().size();
		for (int i = 0; i < kanjiSize; i++)
		{
			if (mod.GetKanjiList()[i].GetSymbol() == L"")
			{
				iter = i;
				break;
			}
		}
		if (iter != 0)
		{
			mod.GetKanjiList().erase(mod.GetKanjiList().begin() + iter, mod.GetKanjiList().end());
			mod.GetKanjiList().shrink_to_fit();
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
