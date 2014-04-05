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
const int BitsPerCharacter = 8;
const int MaxCharactersPerLine = 8192;
const int BitsPerKey = 8;

string configLineDelineator = " = ";
string nullString = "Null";
int nullInt = -347;
float nullFloat = -22.459;

int retrievedValueINT;
float retrievedValueFLOAT;
string retrievedValueSTR;

clock_t generalTimeRecord;

int FileDataActualLineCount = 0;



//				Config defaults:
int start_key_length = 1;
int key_expansion_enabled = 0;
int expanded_key_length = 2;
int key_expansion_method = 1;
string file_path = nullString;



//				Variables that should not need to be variable
string ConfigLineMemory[ConfigMemoryMaxLines];
string FileDataLineMemory[FileDataMemoryMaxLines];
bitset<BitsPerCharacter> NotManipulatedDataBitset[FileDataMemoryMaxLines][MaxCharactersPerLine];
bitset<BitsPerCharacter> ManipulatedDataBitset[FileDataMemoryMaxLines][MaxCharactersPerLine];

//* * * * * * * * * * * * * * * * * * * * * * * * * *  Functions  * * * * * * * * * * * * * * * * * * * * * * * * * *//


//				File Systems:
bool LoadConfiguration()
{
	fstream configFile ("config.txt", std::ios::in);
	bool fileStatusReturn = false;
	if (configFile.good())
	{
		fileStatusReturn = true;
		for (int lineNum = 0; ((!configFile.eof()) && (lineNum < ConfigMemoryMaxLines)); lineNum++)
		{
			getline(configFile, ConfigLineMemory[lineNum]);
		}
	}
	configFile.close();

	return fileStatusReturn;
}

bool LoadFile(string filePathInput)
{
	fstream dataFile (filePathInput, std::ios::in);
	bool fileStatusReturn = false;
	if (dataFile.good())
	{
		fileStatusReturn = true;
		for (int lineNum = 0; ((!dataFile.eof()) && (lineNum < FileDataMemoryMaxLines)); lineNum++)
		{
			getline(dataFile, FileDataLineMemory[lineNum]);
			FileDataActualLineCount = lineNum;
		}
	}
	dataFile.close();

	return fileStatusReturn;
}

void SaveAlteredFile()
{



}


int RetrieveVarFromConfigINT(string varNameInFile)
{
	string Located, Cleaned = nullString;
	int valueRetrieved = nullInt;
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != nullString) && (varTestNum < ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			Cleaned = Located.substr( configLineDelineator.length() );

			if ( Cleaned.c_str() != nullString )
			{
				valueRetrieved = atoi( Cleaned.c_str() );
			}
			else 
			{
				valueRetrieved = nullInt;
			}
			break;
		}
	}
	return valueRetrieved;
}

float RetrieveVarFromConfigFLOAT(string varNameInFile)
{
	string Located, Cleaned = nullString;
	float valueRetrieved = nullFloat;
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != nullString) && (varTestNum < ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			Cleaned = Located.substr( configLineDelineator.length() );

			if ( Cleaned.c_str() != nullString )
			{
				valueRetrieved = atof( Cleaned.c_str() );
			}
			else 
			{
				valueRetrieved = nullFloat;
			}
			break;
		}
	}
	return valueRetrieved;
}

string RetrieveVarFromConfigSTR(string varNameInFile)
{
	string Located, Cleaned = nullString;
	for (int varTestNum = 1; (ConfigLineMemory[varTestNum] != nullString) && (varTestNum < ConfigMemoryMaxLines); varTestNum++)
	{
		if (ConfigLineMemory[varTestNum].find(varNameInFile) == 0)
		{
			Located = ConfigLineMemory[varTestNum].substr( ConfigLineMemory[varTestNum].find( configLineDelineator ) ).c_str();
			Cleaned = Located.substr( configLineDelineator.length() );

			break;
		}
	}
	return Cleaned.c_str();
}


//				Data Manipulation:
void FileToBinary()
{
	for ( size_t lineNum = 0; (lineNum <= FileDataActualLineCount); lineNum++)
	{
		for (size_t characterPos = 0; (characterPos <= FileDataLineMemory[lineNum].length()); characterPos++)
		{
			NotManipulatedDataBitset[lineNum][characterPos] = FileDataLineMemory[lineNum].c_str()[characterPos];
		}
	}
}

void XOR_WithKey(bitset<BitsPerKey> keyBitset)
{
	for ( size_t lineNum = 0; (lineNum <= FileDataActualLineCount); lineNum++)
	{
		for (size_t characterPos = 0; (characterPos <= FileDataLineMemory[lineNum].length()); characterPos++)
		{
			ManipulatedDataBitset[lineNum][characterPos] = NotManipulatedDataBitset[lineNum][characterPos] ^ keyBitset;
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
	return (float)((clock_t)(clock() - clockTimeFromStartTimer)/1000.0);
}


//				Boot Necesary Information:
void BootSystem()
{
	// Pre-define the config memory to only search filled lines for variables
	for (int configCount = 1; configCount < ConfigMemoryMaxLines; configCount++)
	{
		ConfigLineMemory[configCount] = nullString;
	}

	// Read the configuration file and save the data
	LoadConfiguration();
	
	
	// Retrieve integers from Config
	//		start_key_length
	retrievedValueINT = RetrieveVarFromConfigINT("start_key_length"); if (retrievedValueINT != nullInt){ start_key_length = retrievedValueINT; }
	//		key_expansion_enabled
	retrievedValueINT = RetrieveVarFromConfigINT("key_expansion_enabled"); if (retrievedValueINT != nullInt){ key_expansion_enabled = retrievedValueINT; }
	//		expanded_key_length
	retrievedValueINT = RetrieveVarFromConfigINT("expanded_key_length"); if (retrievedValueINT != nullInt){ expanded_key_length = retrievedValueINT; }
	//		key_expansion_method
	retrievedValueINT = RetrieveVarFromConfigINT("key_expansion_method"); if (retrievedValueINT != nullInt){ key_expansion_method = retrievedValueINT; }


	// Retrieve floats from Config


	// Retrieve strings from Config
	//		file_path
	retrievedValueSTR = RetrieveVarFromConfigSTR("file_path"); if (retrievedValueSTR != nullString){ file_path = retrievedValueSTR.c_str(); }


	// Read the focus file and save the data
	LoadFile(file_path);


}


//http://www.cplusplus.com/reference/bitset/bitset/
//http://www.cplusplus.com/reference/bitset/bitset/to_string/
//http://msdn.microsoft.com/en-us/library/3akey979.aspx
//http://www.cplusplus.com/reference/bitset/bitset/hash/
//http://www.cplusplus.com/reference/bitset/bitset/flip/


int main()
{
		generalTimeRecord = StartTimer();

	BootSystem();

		printf("Boot system in %.3f seconds\n\n", EndTimer(generalTimeRecord));
		generalTimeRecord = StartTimer();

	FileToBinary();

		printf("File to binary in %.3f seconds\n\n", EndTimer(generalTimeRecord));
		generalTimeRecord = StartTimer();

	XOR_WithKey(123);

	printf("%d", ManipulatedDataBitset[22][3]);

	//string bcd = "hi there, ";
	//string bcc = "how are you?";

	//printf("%s", (bcd.c_str() + bcc).c_str());                 <-- concatenation

	//printf("%s", a.to_string());
	///printf("%s", (a ^ b).to_string().c_str() );


	cin.get();

	return 0;
}

