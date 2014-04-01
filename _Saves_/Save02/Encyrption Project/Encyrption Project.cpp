#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "time.h"
using namespace std;


//* * * * * * * * * * * * * * * * * * * * * * * * * *  Variables  * * * * * * * * * * * * * * * * * * * * * * * * * *//

const int ConfigMemoryMaxLines = 1024;
const int FileDataMemoryMaxLines = 4096;

string ConfigLineMemory[ConfigMemoryMaxLines];
string FileDataLineMemory[FileDataMemoryMaxLines];


//* * * * * * * * * * * * * * * * * * * * * * * * * *  Functions  * * * * * * * * * * * * * * * * * * * * * * * * * *//

//				File Systems:
void LoadConfiguration()
{
	fstream configFile ("config.txt", std::ios::in);
	for (int lineNum = 1; !configFile.eof(); lineNum++)
	{
		getline(configFile, ConfigLineMemory[lineNum]);
	}
	configFile.close();
};

void RetrieveVarFromConfig(string varNameInFile)
{
	for (int varTestNum = 1; ConfigLineMemory[varTestNum] != "Null"; varTestNum++)
	{
		/*
		while ( getline (file,line) )
       {
    		
    		char *ptr = strtok((char*)(line.data()), (" ="));
    		while (ptr != NULL && index <= 30)
    		  {
    		    valList[index].name.assign(ptr);
    		    ptr = strtok (NULL, " =");
    		    valList[index].value = atof(ptr);
    		    index++;
    		  }
       }
		*/
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
	for (int configCount = 1; configCount<=1024; configCount++)
	{
		ConfigLineMemory[configCount] = "Null";
	}

	LoadConfiguration();
}


//printf("%.3d: %s\n", varTestNum, varNameInFile.c_str());
//printf("%s\n", TemporaryLineMemory[lineNum].c_str());

int main()
{
	
	BootSystem();
	RetrieveVarFromConfig("HiThere");
	/*
	clock_t HelloTesting= StartTimer();
	int actualAmountCounted;
	for (int tempCounter = 0; tempCounter < 1073741824; tempCounter++)
	{
		actualAmountCounted = tempCounter;
	}
	printf("%15.15f, %f", EndTimer(HelloTesting) / ( (float)1073741824 ) , EndTimer(HelloTesting));
	

	while (true)
	{
		printf("%c", cin.get());
	}
	*/

	cin.get();

	return 0;
}

