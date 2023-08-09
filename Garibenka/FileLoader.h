#pragma once

//#include <C:/Program Files/Python311/include/Python.h>  //put it in properties additional include libs

#include <Python.h>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define PY_SSIZE_T_CLEAN

class FileLoader
{
public:
	static void RunPythonScript(int argc, const char* argv[]);
	static void ReadTablesFile();

	static void ReadUserSettingsFile();
};