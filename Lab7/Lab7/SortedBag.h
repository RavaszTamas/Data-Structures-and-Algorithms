#pragma once
#include <utility>
#include <climits>

typedef int TComp;


typedef std::pair<TComp, int> TElem;
typedef bool(*Relation)(TComp, TComp);

struct Node
{
	TElem info;
	int left;
	int right;
	int parent;
};

class SortedBag {

	friend class SortedBagIterator;

private:

	/*representation of Bag*/
	int root = -1;
	int firstEmpty = 0;
	int capacity = 2;
	int sizeOfBag;
	int uniqueNum = 0;
	Node* elements;
	Relation r;
	void resize();

public:

	//constructor

	SortedBag(Relation r);



	//adds an element to the bag
	void fileBag() const;
	void printBag() const;

	void add(TComp e);

	//counts and returns the number of unique elements in the SortedBag

	int uniqueCount()const;


	//removes one occurrence of an element from a bag

	//returns true if an element was removed, false otherwise (if e was not part of the bag)

	bool remove(TComp e);



	//checks if an element appearch is the bag

	bool search(TComp e) const;



	//returns the number of occurrences for an element in the bag

	int nrOccurrences(TComp e) const;

	//remove all occurences of elem fromthe Bag
	//returns the number of elements removed



	//returns the number of elements from the bag

	int size() const;



	//returns an iterator for this bag

	SortedBagIterator iterator() const;



	//checks if the bag is empty

	bool isEmpty() const;



	//destructor

	~SortedBag();

};