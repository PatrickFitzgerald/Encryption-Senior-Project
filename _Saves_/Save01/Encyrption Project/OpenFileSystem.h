#ifndef __OPEN_FILE_SYSTEM__
#define __OPEN_FILE_SYSTEM__
#include <fstream>
#include <iostream>
#include <string>
#include "time.h"
#include "stdafx.h"

using namespace std;


void LoadConfiguration();
int openFile(char * filePath[255], int readMethod, int writeMethod);





#endif