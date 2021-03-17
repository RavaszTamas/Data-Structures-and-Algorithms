#include "SortedBag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>
#include <iostream>
#include <exception>

using namespace std;

int main()
{
	testAll();
	_CrtDumpMemoryLeaks();
	testAllExtended();
	return 0;
}