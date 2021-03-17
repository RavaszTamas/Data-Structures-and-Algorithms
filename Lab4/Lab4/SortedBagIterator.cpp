#include "SortedBagIterator.h"
#include <exception>

SortedBagIterator::SortedBagIterator(const SortedBag & c):c(c)
{
	this->currentElement = c.sortedBag.head;
	this->currentAmount = 0;
}

void SortedBagIterator::first()
{
	this->currentElement = c.sortedBag.head;
	this->currentAmount = 0;
}

void SortedBagIterator::next()
{
	if (this->valid())
	{
		if (this->currentAmount < this->c.sortedBag.nodes[this->currentElement].info.second-1)
			this->currentAmount++;
		else
		{
			this->currentAmount = 0;

			this->currentElement = this->c.sortedBag.nodes[this->currentElement].next;
		}
	}
	else
		throw std::exception();
}

bool SortedBagIterator::valid() const
{
	if (currentElement == -1)
		return false;
	return true;
}

TComp SortedBagIterator::getCurrent() const
{
	if (this->valid())
	{
		return this->c.sortedBag.nodes[this->currentElement].info.first;
	}
	else
		throw std::exception();
}
