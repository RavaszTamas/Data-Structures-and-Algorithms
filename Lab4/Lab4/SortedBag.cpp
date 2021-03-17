#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

int SortedBag::allocateElem()
{
	int newElem = this->sortedBag.firstEmpty;
	if (newElem != -1)
	{
		this->sortedBag.firstEmpty = this->sortedBag.nodes[this->sortedBag.firstEmpty].next;
		if (this->sortedBag.firstEmpty != -1)
		{
			this->sortedBag.nodes[this->sortedBag.firstEmpty].prev = -1;
		}

		this->sortedBag.nodes[newElem].next = -1;
		this->sortedBag.nodes[newElem].prev = -1;

	}
	return newElem;
}

void SortedBag::freeElem(int poz)
{
	this->sortedBag.nodes[poz].next = this->sortedBag.firstEmpty;
	this->sortedBag.nodes[poz].prev = -1;
	if (this->sortedBag.firstEmpty != -1)
	{
		this->sortedBag.nodes[this->sortedBag.firstEmpty].prev = poz;
	}
	this->sortedBag.firstEmpty = poz;
}

void SortedBag::insertELem(TElem e, int poz)
{
	int newElem = this->allocateElem();
	if (newElem == -1)
	{
		this->resize();
		newElem = this->allocateElem();
	}

	this->sortedBag.nodes[newElem].info = e;

	if (poz == 0)
	{
		if (this->sortedBag.head == -1)
		{
			this->sortedBag.head = newElem;
			this->sortedBag.tail = newElem;
		}
		else
		{
			this->sortedBag.nodes[newElem].next = this->sortedBag.head;
			this->sortedBag.nodes[this->sortedBag.head].prev = newElem;
			this->sortedBag.head = newElem;
		}
	}
	else
	{
		int nodC = this->sortedBag.head;
		int pozC = 0;
		while (nodC != -1 && pozC < poz - 1)
		{
			nodC = this->sortedBag.nodes[nodC].next;
			pozC = pozC + 1;
		}
		int nodNext = -10000000;
		if (nodC != -1)
		{
			nodNext = this->sortedBag.nodes[nodC].next;
			this->sortedBag.nodes[newElem].next = nodNext;
			this->sortedBag.nodes[newElem].prev = nodC;
			this->sortedBag.nodes[nodC].next = newElem;
			if (nodNext == -1)
			{
				this->sortedBag.tail = newElem;
			}
			else
			{
				this->sortedBag.nodes[nodNext].prev = newElem;
			}
		}
		else
			throw;
	}

}

int SortedBag::searchPozElem(TComp e)
{
	int current = this->sortedBag.head;
	while (current != -1 && this->sortedBag.nodes[current].info.first != e)
	{
		current = this->sortedBag.nodes[current].next;
	}
	return current;
}
/*
void SortedBag::addToEnd(TElem e)
{

	int newElem = this->allocateElem();
	if (newElem == -1)
	{
		this->resize();
		newElem = this->allocateElem();
	}

	this->sortedBag.nodes[newElem].info = e;

	this->sortedBag.nodes[newElem].prev = this->sortedBag.tail;
	this->sortedBag.nodes[this->sortedBag.tail].next = newElem;
	this->sortedBag.tail = newElem;
}
*/
void SortedBag::resize()
{
	DLLANode* newNodes = new DLLANode[(this->sortedBag.capacity) * 2];
	for (int i = 0; i < this->sortedBag.capacity; ++i)
		newNodes[i] = this->sortedBag.nodes[i];
	for (int i = this->sortedBag.capacity; i < this->sortedBag.capacity * 2 - 1; ++i)
	{
		newNodes[i].next = i + 1;
		newNodes[i + 1].prev = i;
	}
	newNodes[this->sortedBag.capacity * 2 - 1].next = -1;
	newNodes[this->sortedBag.capacity].prev = -1;

	delete[] this->sortedBag.nodes;

	this->sortedBag.nodes = newNodes;
	this->sortedBag.firstEmpty = this->sortedBag.capacity;
	this->sortedBag.capacity *= 2;


}

void SortedBag::printBag()
{
	cout << endl;

	int current = this->sortedBag.head;
	while (current != -1)
	{
		cout << this->sortedBag.nodes[current].info.first << " " << this->sortedBag.nodes[current].info.second << endl;
		current = this->sortedBag.nodes[current].next;
	}
	cout << endl;
}

SortedBag::SortedBag(Relation r)
{
	this->relation = r;
	this->sortedBag.capacity = 10;
	this->sortedBag.nodes = new DLLANode[10];
	this->sortedBag.head = -1;
	for (int i = 0; i < this->sortedBag.capacity-1; ++i)
	{
		this->sortedBag.nodes[i].next = i + 1;
		this->sortedBag.nodes[i+1].prev = i;
	}
	this->sortedBag.nodes[this->sortedBag.capacity-1].next = -1;
	this->sortedBag.nodes[0].prev = -1;


	this->sortedBag.firstEmpty = 0;
	this->sortedBag.size = 0;
	this->sortedBag.actualSize = 0;
}

void SortedBag::add(TComp e)
{
	int poz = this->searchPozElem(e);
	
	if (poz == -1)
	{
		
		poz = this->sortedBag.head;
		if (poz != -1)
		{
			int index = 0;
			while (poz != -1 && this->relation(this->sortedBag.nodes[poz].info.first,e))
			{
				poz = this->sortedBag.nodes[poz].next;
				++index;
			}

			if (poz == -1)
			{
				this->insertELem(TElem{ e, 1}, this->sortedBag.actualSize);
			}
			else
			{
				this->insertELem(TElem{ e, 1 }, index);
			}
			
		}
		else
		{
			poz = 0;
			this->insertELem(TElem{ e, 1 }, poz);
		}
		
		this->sortedBag.actualSize += 1;
	}
	else
	{
		this->sortedBag.nodes[poz].info.second += 1;
	}
	


	this->sortedBag.size += 1;
	/*
	cout << endl;

	int current = this->sortedBag.head;
	while (current != -1)
	{
		cout << this->sortedBag.nodes[current].info.first << " " <<  this->sortedBag.nodes[current].info.second << endl;
		current = this->sortedBag.nodes[current].next;
	}
	cout << endl;
	*/
}

bool SortedBag::remove(TComp e)
{

	int pos = this->searchPozElem(e);
	if (pos == -1)
		return false;
	if(this->sortedBag.nodes[pos].info.second == 1)
	{
		int nodC = this->sortedBag.head;
		int prevNode = -1;

		while (nodC != -1 && this->sortedBag.nodes[nodC].info.first != e)
		{
			prevNode = nodC;
			nodC = this->sortedBag.nodes[nodC].next;
		}

		if (nodC != -1)
		{
			this->sortedBag.size -= 1;
			this->sortedBag.actualSize -= 1;
			if (nodC == this->sortedBag.head)
				this->sortedBag.head = this->sortedBag.nodes[this->sortedBag.head].next;
			else
				this->sortedBag.nodes[prevNode].next = this->sortedBag.nodes[nodC].next;

			this->freeElem(nodC);
			
			return true;

		}
		else
			return false;
	}
	else
	{
		this->sortedBag.size -= 1;
		this->sortedBag.nodes[pos].info.second--;
		return true;
	}
}

bool SortedBag::search(TComp e) const
{

	bool search;
	int current = this->sortedBag.head;
	while (current != -1 && this->sortedBag.nodes[current].info.first != e)
	{
		current = this->sortedBag.nodes[current].next;
	}
	if (current != -1)
	{
		search = true;
	}
	else
	{
		search = false;
	}
	return search;
}

int SortedBag::nrOccurrences(TComp e) const
{
	int current = this->sortedBag.head;
	while (current != -1 && this->sortedBag.nodes[current].info.first != e)
	{
		current = this->sortedBag.nodes[current].next;
	}
	if (current == -1)
		return 0;
	else
		return this->sortedBag.nodes[current].info.second;

}

int SortedBag::size() const
{
	return 	this->sortedBag.size;

}

SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}



bool SortedBag::isEmpty() const
{
	return this->sortedBag.size == 0;
}

int SortedBag::elementsWithThisFrequency(int frequency) const
{
	if (frequency <= 0)
	{
		throw exception();
	}
	int poz = this->sortedBag.head;
	int numberOfElemets = 0;
	while (poz != -1)
	{
		if (this->sortedBag.nodes[poz].info.second == frequency)
			++numberOfElemets;
		poz = this->sortedBag.nodes[poz].next;
	}
	return numberOfElemets;
}

SortedBag::~SortedBag()
{
	delete[] this->sortedBag.nodes;
}
