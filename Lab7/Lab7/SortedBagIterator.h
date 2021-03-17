#pragma once

#include "SortedBag.h"
#include <stack> 

//unidirectional iterator for a container

class SortedBagIterator {

	friend class SortedBag;

private:

	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty

	int current;
	int currentAmount;
	std::stack<int> inorderParse;
	SortedBagIterator(const SortedBag& c);



	//contains a reference of the container it iterates over

	const SortedBag& c;


	/* representation specific for the iterator*/



public:

	void indorderPrint();


	//sets the iterator to the first element of the container

	void first();



	//moves the iterator to the next element

	//throws exception if the iterator is not valid

	void next();



	//checks if the iterator is valid

	bool valid() const;



	//returns the value of the current element from the iterator

	// throws exception if the iterator is not valid

	TComp getCurrent() const;



};


