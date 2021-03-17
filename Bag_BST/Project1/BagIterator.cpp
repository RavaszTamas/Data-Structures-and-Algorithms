#include "BagIterator.h"
#include <exception>
#define empty INT_MIN

BagIterator::BagIterator(const Bag & c) : c{ c }
{
	this->currentElem = 0;
	this->currentAmount = 0;
	while (this->c.Table[currentElem].first == empty && currentElem < this->c.m)
		currentElem++;
	this->currentAmount = this->c.Table[this->currentElem].second;

}

void BagIterator::first()
{
	this->currentElem = 0;
	this->currentAmount = 0;
	while (this->c.Table[currentElem].first == empty && currentElem < this->c.m)
		currentElem++;
	this->currentAmount = this->c.Table[this->currentElem].second;

}

void BagIterator::next()
{
	if (this->valid())
	{
		if (this->currentAmount > 0)
		{
			this->currentAmount--;
		}
		else 
		{
			this->currentElem += 1;
			while (this->c.Table[currentElem].first == empty && currentElem < this->c.m)
				currentElem++;
			this->currentAmount = this->c.Table[this->currentElem].second;
		}
	}
	else
		throw std::exception();
}

bool BagIterator::valid() const
{
	if (currentElem < this->c.m)
		return true;
	return false;
}

TElem BagIterator::getCurrent() const
{
	if (this->valid())
	{
		return this->c.Table[this->currentElem].first;
	}
	else
		throw std::exception();
}
