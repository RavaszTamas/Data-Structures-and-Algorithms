#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

using namespace std;

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	//sb.printBag();
	sb.add(6);
	//sb.printBag();
	sb.add(0);
	//sb.printBag();
	sb.add(5);
	//sb.printBag();
	sb.add(10);
	//sb.printBag();
	sb.add(8);
	//sb.printBag();

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

	assert(sb.uniqueCount() == 5);
	sb.add(5);
	sb.add(5);
	sb.add(5);
	sb.add(5);
	sb.add(5);
	assert(sb.uniqueCount() == 5);
	sb.add(-1);
	assert(sb.uniqueCount() == 6);

}

