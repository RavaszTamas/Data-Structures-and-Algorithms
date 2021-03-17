#include "DAIterator.h"

DAIterator::DAIterator(const DynamicArray& c): c(c)
{
	currentElem = c.dynamicArray;
	currentIteration = 0;
}


void DAIterator::first()
{
	currentElem = c.dynamicArray;
	currentIteration = 0;
}

void DAIterator::next()
{
	if(valid())
	{
		currentElem++;
		currentIteration++;
	}
	else
	{
		throw;
	}
}

bool DAIterator::valid() const
{
	if(currentIteration < c.lengthOfArray)
	{
		return true;
	}
	return false;
}

TElem DAIterator::getCurrent() const
{
	if(valid())
	{
		return *currentElem;
	}
	else
	{
		throw;
	}
}
