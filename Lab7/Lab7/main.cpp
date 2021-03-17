#include <iostream>
#include "SortedBag.h"
#include "ShortTest.h"
//#include <vector>
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