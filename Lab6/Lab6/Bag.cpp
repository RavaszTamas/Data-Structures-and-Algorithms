#include "Bag.h"
#include <cmath>
#include "BagIterator.h"
#include <iostream>
#include <fstream>

#define empty INT_MIN

using namespace std;

int Bag::hash(TKey k) const
{
	return abs(k) % m;
}



void Bag::rehash()
{
	TComp* newTable = new TComp[this->m ];
	int* newNext = new int[this->m];
	for (int i = 0; i < this->m; i++)
	{
		newTable[i].first = empty;
		newTable[i].second = 0;
		newNext[i] = -1;
	}
	int newFirstFree = 0;
	for (int i = 0; i < this->m; i++)
	{
		if (this->Table[i].first != empty)
		{
			int pos = hash(this->Table[i].first);

			if (newTable[pos].first == empty)
			{
				newTable[pos].first = this->Table[i].first;
				newTable[pos].second = this->Table[i].second;
				newNext[pos] = -1;
				if (pos == newFirstFree)
				{
					newFirstFree += 1;
					while (newFirstFree < this->m && newTable[newFirstFree].first != empty)
						newFirstFree += 1;

				}

			}
			else
			{
				int current = pos;
				while (newNext[current] != -1 && newTable[current].first != this->Table[i].first)
				{
					current = newNext[current];
				}
				//if (newTable[current].first != this->Table[i].first)
				//{
				newTable[newFirstFree].first = this->Table[i].first;
				newTable[newFirstFree].second = this->Table[i].second;

				newNext[newFirstFree] = -1;
				newNext[current] = newFirstFree;

				newFirstFree += 1;
				while (newFirstFree < this->m && newTable[newFirstFree].first != empty)
					newFirstFree += 1;
				/*}
				else
				{
				newTable[current].second += 1;
				}*/


			}

		}
	}

	delete this->Table;
	delete this->next;
	this->Table = newTable;
	this->next = newNext;
	this->firstFree = newFirstFree;
}

void Bag::resize()
{
	int newm = nextprime(this->m);

	TComp* newTable = new TComp[newm];
	int* newNext = new int[newm];
	for (int i = 0; i < newm; i++)
	{
		newTable[i].first = empty;
		newTable[i].second = 0;
		newNext[i] = -1;
	}
	int newFirstFree = 0;
	int oldm = this->m;
	this->m = newm;

	for (int i = 0; i < oldm; i++)
	{
		if (this->Table[i].first != empty)
		{
			int pos = hash(this->Table[i].first);

			if (newTable[pos].first == empty)
			{
				newTable[pos].first = this->Table[i].first;
				newTable[pos].second = this->Table[i].second;
				newNext[pos] = -1;
				if (pos == newFirstFree)
				{
					newFirstFree += 1;
					while (newFirstFree < this->m && newTable[newFirstFree].first != empty)
						newFirstFree += 1;

				}

			}
			else
			{
				int current = pos;
				while (newNext[current] != -1 && newTable[current].first != this->Table[i].first)
				{
					current = newNext[current];
				}
				//if (newTable[current].first != this->Table[i].first)
				//{
				newTable[newFirstFree].first = this->Table[i].first;
				newTable[newFirstFree].second = this->Table[i].second;

				newNext[newFirstFree] = -1;
				newNext[current] = newFirstFree;

				newFirstFree += 1;
				while (newFirstFree < this->m && newTable[newFirstFree].first != empty)
					newFirstFree += 1;
				/*}
				else
				{
					newTable[current].second += 1;
				}*/


			}

		}
	}

	delete this->Table;
	delete this->next;
	this->Table = newTable;
	this->next = newNext;
	this->firstFree = newFirstFree;
	

}

void Bag::printTable()
{
	ofstream out("tempout.txt");
	for (int i = 0; i < this->m; ++i)
	{
		out << this->Table[i].first << " " << this->Table[i].second << " " << this->next[i] << endl;
	}
}

void Bag::coutTable()
{
	for (int i = 0; i < this->m; ++i)
	{
		cout << this->Table[i].first << " " << this->Table[i].second << " " << this->next[i] << endl;
	}

}




Bag::Bag()
{
	this->sizeOfBag = 0;
	this->m = 5;
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
	if (this->m == this->firstFree)
		this->resize();

	int pos = this->hash(e);

	if (this->Table[pos].first == empty)
	{
		this->Table[pos].first = e;
		this->Table[pos].second = 1;
		this->next[pos] = -1;

		if (pos == this->firstFree)
		{
			this->firstFree += 1;
			while (this->firstFree < this->m && this->Table[this->firstFree].first != empty)
				this->firstFree += 1;

		}
	}
	else
	{

		int current = pos;
		while (this->next[current] != -1 && this->Table[current].first != e)
		{
			current = this->next[current];
		}
		if (this->Table[current].first != e)
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

bool Bag::isPrime(int num)
{
	if (num == 0 || num == 1)
		return false;
	if (num == 2)
		return true;
	if (num % 2 == 0)
		return false;
	int root = sqrt(num);
	int i = 0;
	for (i = 3; i <= root; i = i + 2)
	{
		if (num % i == 0)
			return false;
	}
	return true;

}

int Bag::nextprime(int currs)
{
	currs++;
	while (!isPrime(currs))
	{
		currs++;
	}
	return currs;
	
}

bool Bag::remove(TElem e)
{
	int current = this->hash(e);
	int prev = -1;
	int idx = 0;
	while (idx < this->m && prev == -1)
	{
		if (this->next[idx] == current)
			prev = idx;
		else
			idx++;
	}

	while (current != -1 && this->Table[current].first != e)
	{
		prev = current;
		current = this->next[current];

	}
	int p;
	int pp;
	if (current == -1)
	{
		return false;
	}
	else if (this->Table[current].second > 1)
	{
		this->Table[current].second--;

	}
	else
	{
		bool over = false;
		do
		{
			p = this->next[current];
			pp = current;

			while (p != -1 && this->hash(this->Table[p].first) != current)
			{
				pp = p;
				p = this->next[p];
			}
			if (p == -1)
			{
				over = true;
			}
			else
			{
				this->Table[current] = this->Table[p];
				prev = pp;
				current = p;
			}
		} while (!over);
		if (prev != -1)
		{
			this->next[prev] = this->next[current];
		}
		
		this->Table[current].first = empty;
		this->Table[current].second = 0;
		this->next[current] = -1;
		if (this->firstFree > current)
			this->firstFree = current;
	}
	this->sizeOfBag--;
	return true;

}

bool Bag::search(TElem e) const
{
	int current = this->hash(e);
	while (current != -1 && this->Table[current].first != e)
	{
		current = this->next[current];
	}
	if (current == -1)
		return false;
	return true;
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

int Bag::removeAllOccurences(TElem elem)
{

	int current = this->hash(elem);
	int prev = -1;
	int idx = 0;
	while (idx < this->m && prev == -1)
	{
		if (this->next[idx] == current)
			prev = idx;
		else
			idx++;
	}

	while (current != -1 && this->Table[current].first != elem)
	{
		prev = current;
		current = this->next[current];

	}
	int p;
	int pp;
	if (current == -1)
	{
		return false;
	}
	else
	{
		bool over = false;
		do
		{
			p = this->next[current];
			pp = current;

			while (p != -1 && this->hash(this->Table[p].first) != current)
			{
				pp = p;
				p = this->next[p];
			}
			if (p == -1)
			{
				over = true;
			}
			else
			{
				this->Table[current] = this->Table[p];
				prev = pp;
				current = p;
			}
		} while (!over);
		if (prev != -1)
		{
			this->next[prev] = this->next[current];
		}

		this->Table[current].first = empty;
		this->Table[current].second = 0;
		this->next[current] = -1;
		if (this->firstFree > current)
			this->firstFree = current;
	}
	this->sizeOfBag--;
	return true;


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
