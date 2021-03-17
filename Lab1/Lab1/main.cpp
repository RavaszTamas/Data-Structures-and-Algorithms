#include <iostream>
#include "Test.h"
#include <crtdbg.h>
using namespace std;


int main()
{
	testAll();
	testAllExtended();
	_CrtDumpMemoryLeaks();
	return 0;
}