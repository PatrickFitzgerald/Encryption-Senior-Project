#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <istream>
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
const int BitsInKey = 8;

bool programStatusHealthy = true;

string configLineDelineator = " = ";
string fileExtensionENC = ".enc";
string fileExtensionKEY = ".key";
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
	fstream configFile ("config.txt", ios::in);
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
	fstream dataFile (filePathInput, ios::in | ios::binary);
	bool fileStatusReturn = false;
	string tempNewLine = "\n";
	if (dataFile.good())
	{
		fileStatusReturn = true;
		for (int lineNum = 0; ((!dataFile.eof()) && (lineNum < FileDataMemoryMaxLines)); lineNum++)
		{
			//getline(dataFile, FileDataLineMemory[lineNum]);
			dataFile>>FileDataLineMemory[lineNum];
			FileDataActualLineCount = lineNum;
		}
	}
	dataFile.close();
	return fileStatusReturn;
}

void SaveAlteredFile( string filePathInput )
{
	string newFilePath;

	if (( filePathInput.find( fileExtensionENC ) != -1) && ( filePathInput.length() - filePathInput.find( fileExtensionENC ) == fileExtensionENC.length()))
	{
		newFilePath = filePathInput.substr(0, filePathInput.find( fileExtensionENC ));
	}
	else
	{
		newFilePath = filePathInput.c_str() + fileExtensionENC;
	}

	fstream saveFile ( newFilePath, ios::out );

	for ( size_t lineNum = 0; (lineNum <= FileDataActualLineCount); lineNum++)
	{
		for (size_t characterPos = 0; (characterPos < FileDataLineMemory[lineNum].length()); characterPos++)
		{
			saveFile << static_cast<char> ((ManipulatedDataBitset[lineNum][characterPos]).to_ulong());
		}
		//saveFile  << endl;
	}

	saveFile.close();
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

void XOR_WithKey(bitset<BitsInKey> keyBitset)
{
	for ( size_t lineNum = 0; (lineNum <= FileDataActualLineCount); lineNum++)
	{
		for (size_t characterPos = 0; (characterPos < FileDataLineMemory[lineNum].length()); characterPos++)
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
bool BootSystem()
{
	// Some variables to represent the status of functions called in BootSystem()
	bool subProgramStatusHealthy1 = true;
	bool subProgramStatusHealthy2 = true;

	// Pre-define the config memory to only search filled lines for variables
	for (int configCount = 1; configCount < ConfigMemoryMaxLines; configCount++)
	{
		ConfigLineMemory[configCount] = nullString;
	}

	// Read the configuration file and save the data, while checking if the action was successful
	subProgramStatusHealthy1 = LoadConfiguration();
	
	if (subProgramStatusHealthy1)
	{
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
	}

	// Read the focus file and save the data
	subProgramStatusHealthy2 = LoadFile(file_path);

	// Returns whether or not the entirety of BootSystem() was successful
	if (subProgramStatusHealthy1 && subProgramStatusHealthy2) { return true; }
	else { return false; }
}


//http://www.cplusplus.com/reference/bitset/bitset/
//http://www.cplusplus.com/reference/bitset/bitset/to_string/
//http://msdn.microsoft.com/en-us/library/3akey979.aspx
//http://www.cplusplus.com/reference/bitset/bitset/hash/
//http://www.cplusplus.com/reference/bitset/bitset/flip/
//http://www.cplusplus.com/reference/cstdio/rename/
//http://www.cplusplus.com/reference/cstdio/remove/
//GET - http://stackoverflow.com/questions/17985320/reading-in-extended-ascii-with-cin-get
//http://www.daniweb.com/software-development/c/threads/366962/reading-extended-ascii-characters
//http://www.mobileread.com/forums/showthread.php?t=170409


int main()
{
		generalTimeRecord = StartTimer();

	if (programStatusHealthy)
	{
		programStatusHealthy = BootSystem();
	}

	
		printf("Booted system in %.3f seconds\n\n", EndTimer(generalTimeRecord));
		generalTimeRecord = StartTimer();

	FileToBinary();

		printf("File to binary in %.3f seconds\n\n", EndTimer(generalTimeRecord));
		generalTimeRecord = StartTimer();

	XOR_WithKey(123);

	//printf("%d", ManipulatedDataBitset[22][3]);

	//string bcd = "hi there, ";
	//string bcc = "how are you?";

	//printf("%s", (bcd.c_str() + bcc).c_str());                 <-- concatenation

	//printf("%s", a.to_string());
	//printf("%s", (a ^ b).to_string().c_str() );

	SaveAlteredFile(file_path);


	/*
	for (int i = 0; i < 5; i++)
	{
		printf("%s\n", FileDataLineMemory[0].c_str());
		printf("%d\n", NotManipulatedDataBitset[0][i]);
		printf("%d\n", ManipulatedDataBitset[0][i]);
	}
	*/
	cin.get();

	return 0;
}

