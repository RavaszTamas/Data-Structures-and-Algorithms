#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>
using namespace std;

int main()
{
	testAll();
	testAllExtended();
	_CrtDumpMemoryLeaks();
	return 0;
}