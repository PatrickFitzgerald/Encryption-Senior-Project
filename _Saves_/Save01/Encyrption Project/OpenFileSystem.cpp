#include "stdafx.h"
#include "OpenFileSystem.h"


void LoadConfiguration()
{
	fstream configFile ("config.txt", std::ios::in);
	string TemporaryLineMemory[1000];

	for (int lineNum = 1; !configFile.eof(); lineNum++)
	{
		getline(configFile, TemporaryLineMemory[lineNum]);
		printf("%s\n", TemporaryLineMemory[lineNum].c_str());
	}
	configFile.close();
};