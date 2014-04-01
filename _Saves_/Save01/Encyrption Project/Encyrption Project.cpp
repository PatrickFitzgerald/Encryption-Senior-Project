#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "time.h"
using namespace std;


//* * * * * * * * * * * * * * * * * * * * * * * * * *  Variables  * * * * * * * * * * * * * * * * * * * * * * * * * *//

string ConfigLineMemory[1024];
string FileDataLineMemory[4096];


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
		printf("%.3d: %s\n", varTestNum, varNameInFile.c_str());
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
	*/

	cin.get();

	return 0;
}

