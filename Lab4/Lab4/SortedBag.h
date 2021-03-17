#pragma once
#include <iostream>

typedef int TComp;

typedef std::pair<int, int> TElem;

typedef bool(*Relation)(TComp, TComp);

struct DLLANode
{
	 TElem info;
	 int next;
	 int prev;
};

struct DLLA
{
	DLLANode* nodes;
	int head;
	int tail;
	int capacity;
	int firstEmpty;
	int size;
	int actualSize;
};

class SortedBag {

	friend class SortedBagIterator;


private:

	/*representation of SortedBag*/

	DLLA sortedBag;
	Relation relation;

	int allocateElem();

	void freeElem(int poz);

	void insertELem(TElem e, int poz);

	int searchPozElem(TComp e);

	//void addToEnd(TElem e);

	void resize();

public:

	void printBag();

	//constructor

	SortedBag(Relation r);



	//adds an element to the sorted bag

	void add(TComp e);



	//removes one occurrence of an element from a sorted bag

	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)

	bool remove(TComp e);



	//checks if an element appearch is the sorted bag

	bool search(TComp e) const;



	//returns the number of occurrences for an element in the sorted bag

	int nrOccurrences(TComp e) const;



	//returns the number of elements from the sorted bag

	int size() const;



	//returns an iterator for this sorted bag

	SortedBagIterator iterator() const;



	//checks if the sorted bag is empty

	bool isEmpty() const;

	//returns the number of elements that have the given number of occurences

	//throws an exception if frequency is negative or zero

	int elementsWithThisFrequency(int frequency) const;


	//destructor

	~SortedBag();

};