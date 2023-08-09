


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

	PyRun_SimpleString("exec('Tables.py')");


	if (Py_FinalizeEx() < 0)
	{
		exit(120);
	}

	PyMem_RawFree(program);

}
