#include "MultiMapIterator.h"

MultiMapIterator::MultiMapIterator(const MultiMap& c):c(c)
{
	currentNode = c.list.head;
	currentIteration = 0;
}


void MultiMapIterator::first()
{
	//Sets the iterator to the first element in the SLL of the multimap
	currentNode = c.list.head;

}

void MultiMapIterator::next()
{
	//Moves to the next position in the SLL if the current position is valid
	//Throws: if the current position is not valid
	if (valid())
	{
		currentNode = currentNode->next;

	}
	else
	{
		throw;
	}


}

bool MultiMapIterator::valid() const
{
	//Checks if the current position is valid
	//Post: True if the current position is valid, smaller than the size of the list,
	//      otherwise false
	if (currentNode != NULL)
		return true;
	return false;
}

TElem MultiMapIterator::getCurrent() const
{
	//Returns the current element of the list
	//pre: the current iteration is valid
	//post: the element
	//throws: if the current position is not valid
	if (valid())
	{
		return TElem{ currentNode->element.first,currentNode->element.second };
	}
	else
	{
		throw;
	}
}
