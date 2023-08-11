


#include "FileLoader.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>


void FileLoader::RunPythonScript(int argc, const char* argv[])
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


void FileLoader::ReadUserSettingsFile()
{
}

FileLoader::Symbol::Symbol(std::string inSymbol, std::string inReading, std::string inMeaning)
	:
	symbol(inSymbol),
	reading(inReading),
	meaning(inMeaning)
{
}

FileLoader::Module::Module(std::string inFromFile, std::string inModuleName)
	:
	fromFile(inFromFile),
	moduleName(inModuleName)
{
}
