#include "Bag.h"
#include <cmath>
#include "BagIterator.h"
#define empty INT_MIN


int Bag::hash(TKey k) const
{
	return abs(k) % m;
}

void Bag::resize()
{
	TComp* newTable = new TComp[this->m * 2];
	int* newNext = new int[this->m * 2];
	for (int i = 0; i < this->m * 2; i++)
	{
		newTable[i].first = empty;
		newTable[i].second = 0;
		newNext[i] = -1;
	}
	int newFirstFree = 0;
	this->m *= 2;
	for (int i = 0; i < this->m/2; i++)
	{
		if (this->Table[i].first != empty)
		{
			int pos = hash(this->Table[i].first);

			if (newTable[pos].first == empty)
			{
				newTable[pos].first = this->Table[i].first;
				newTable[pos].second = 1;
				newNext[pos] = -1;
			}
			else
			{
				int current = pos;
				while (newNext[current] != -1 && newTable[current].first != this->Table[i].first)
				{
					current = newNext[current];
				}
				if (newNext[current] == -1)
				{
					newTable[newFirstFree].first = this->Table[i].first;
					newTable[newFirstFree].second = 1;

					newNext[newFirstFree] = -1;
					newNext[current] = newFirstFree;

					newFirstFree += 1;
					while (newFirstFree < this->m && newTable[newFirstFree].first != empty)
						newFirstFree += 1;
				}
				else
				{
					newTable[current].second += 1;
				}


			}

		}
	}

	delete this->Table;
	delete this->next;
	this->Table = newTable;
	this->next = newNext;
	this->firstFree = newFirstFree;
	

}


Bag::Bag()
{
	this->sizeOfBag = 0;
	this->m = 16;
	this->Table = new TComp[this->m];
	this->next = new int[this->m];
	for (int i = 0; i < this->m; ++i)
	{
		this->Table[i].first = empty;
		this->Table[i].second = 0;
		this->next[i] = -1;
	}
	this->firstFree = 0;
}

void Bag::add(TElem e)
{
	/*
	if (loadFactor < this->size/this->m)
	{
		this->resize();
	}
	*/
	int pos = this->hash(e);

	if (this->Table[pos].first == empty)
	{
		this->Table[pos].first = e;
		this->Table[pos].second = 1;
		this->next[pos] = -1;
	}
	else
	{
		if (this->m == this->firstFree)
			this->resize();

		int current = pos;
		while (this->next[current] != -1 && this->Table[current].first != e)
		{
			current = this->next[current];
		}
		if (this->Table[current].first == empty)
		{
			this->Table[this->firstFree].first = e;
			this->Table[this->firstFree].second = 1;

			this->next[this->firstFree] = -1;
			this->next[current] = this->firstFree;

			this->firstFree += 1;
			while (this->firstFree < this->m && this->Table[this->firstFree].first != empty)
				this->firstFree += 1;
		}
		else
		{
			this->Table[current].second += 1;
		}


	}


	this->sizeOfBag++;
}

bool Bag::remove(TElem e)
{
	int current = this->hash(e);
	int prev = -1;
	while (current != -1 && this->Table[current].first != e)
	{
		prev = current;
		current = this->next[current];
	}

	if (current == -1)
		return false;
	else
	{
		if (this->Table[current].second != 1)
		{
			this->Table[current].second -= 1;
		}
		else
		{
			this->next[prev] = this->next[current];
			this->next[current] = -1;
			this->Table[current].first = empty;
			this->Table[current].second = 0;
		}
	}
	this->sizeOfBag -= 1;
	return true;
}

bool Bag::search(TElem e) const
{
	int current = this->hash(e);
	while (current != -1 && this->Table[current].first != e)
	{
		current = this->next[current];
	}
	return current != -1;
}

int Bag::nrOccurrences(TElem e) const
{
	int current = this->hash(e);
	while (current != -1 && this->Table[current].first != e)
	{
		current = this->next[current];
	}
	if (current == -1)
		return 0;
	else
		return this->Table[current].second;
}

int Bag::size() const
{
	return this->sizeOfBag;
}
BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}


bool Bag::isEmpty() const
{
	return this->sizeOfBag == 0;
}

Bag::~Bag()
{
	delete this->Table;
	delete this->next;
}
