#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "time.h"
#include <bitset>
using namespace std;


//* * * * * * * * * * * * * * * * * * * * * * * * * *  Variables  * * * * * * * * * * * * * * * * * * * * * * * * * *//


//				Variables relavant before completed startup:
const int ConfigMemoryMaxLines = 1024;
const int FileDataMemoryMaxLines = 4096;
string configLineDelineator = " = ";


//				Config defaults:
int start_key_length = 1;
int key_expansion_enabled = 0;
int expanded_key_length = 2;
int key_expansion_method = 1;


//				Variables that should not need to be variable
string ConfigLineMemory[ConfigMemoryMaxLines];
string FileDataLineMemory[FileDataMemoryMaxLines];


//* * * * * * * * * * * * * * * * * * * * * * * * * *  Functions  * * * * * * * * * * * * * * * * * * * * * * * * * *//


//				File Systems:
void LoadConfiguration()
{
	fstream configFile ("config.txt", std::ios::in);
	for (int lineNum = 1; ((!configFile.eof()) && (lineNum < ConfigMemoryMaxLines)); lineNum++)
	{
		getline(configFile, ConfigLineMemory[lineNum]);
	}
	configFile.close();
}

int RetrieveVarFromConfigINT(string varNameInFile)
{
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != "Null") && (varTestNum <= ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			string Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			string Cleaned = Located.substr( configLineDelineator.length() );

			int valueRetrieved = atoi( Cleaned.c_str() );

			return valueRetrieved;

			break;
		}
	}
}

float RetrieveVarFromConfigFLOAT(string varNameInFile)
{
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != "Null") && (varTestNum <= ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			string Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			string Cleaned = Located.substr( configLineDelineator.length() );

			float valueRetrieved = atof( Cleaned.c_str() );

			return valueRetrieved;

			break;
		}
	}
}

string RetrieveVarFromConfigSTR(string varNameInFile)
{
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != "Null") && (varTestNum <= ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			string Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			string Cleaned = Located.substr( configLineDelineator.length() );

			return Cleaned.c_str();

			break;
		}
	}
}




//				Clock Systems:
clock_t StartTimer()
{
	return clock();
}

float EndTimer(clock_t clockTimeFromStartTimer)
{
	return ((float)(clock() - clockTimeFromStartTimer)/1000.0);
}




//				Boot Necesary Information:
void BootSystem()
{
	for (int configCount = 1; configCount <= ConfigMemoryMaxLines; configCount++)
	{
		ConfigLineMemory[configCount] = "Null";
	}

	LoadConfiguration();
	
	// Integers from Config
	start_key_length = RetrieveVarFromConfigINT("start_key_length");
	key_expansion_enabled = RetrieveVarFromConfigINT("key_expansion_enabled");
	expanded_key_length = RetrieveVarFromConfigINT("expanded_key_length");
	key_expansion_method = RetrieveVarFromConfigINT("key_expansion_method");

	//Floats from Config

	//Strings from Config
}


//http://www.cplusplus.com/reference/bitset/bitset/
//http://www.cplusplus.com/reference/bitset/bitset/to_string/
//http://msdn.microsoft.com/en-us/library/3akey979.aspx
//http://www.cplusplus.com/reference/bitset/bitset/hash/


int main()
{
	bitset<2048> a = 2147483647;
	bitset<2048> b = 8;
	//string b = "HiThere47";
	//const size_t bitCount = max( a.length(), b.length());
	BootSystem();
	printf("%d", a.to_ullong());
	///printf("%s", (a ^ b).to_string().c_str() );

	cin.get();

	return 0;
}

