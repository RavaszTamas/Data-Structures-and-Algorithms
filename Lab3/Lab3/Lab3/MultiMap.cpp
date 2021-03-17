#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <iostream>

MultiMap::MultiMap()
{
}

void MultiMap::add(TKey c, TValue v)
{
	//Adds the element to the start of the list
	//Pre: list is an SLL
	//Post: list' = list U <c,v>
	//Complexity: Theta(1)
	SLLNode* newNode = new SLLNode;
	newNode->element = TElem{ c,v };
	newNode->next = list.head;
	list.head = newNode;
	++list.size;
}

bool MultiMap::remove(TKey c, TValue v)
{
	//Complexity: O(n)
	//Removes an element from the list
	//pre: c,v are intgeres, list is and SLL
	//post: true if an element was removed false, otherwise
	SLLNode* current = list.head;
	SLLNode* prev = NULL;

	for (current; current != NULL; prev = current, current = current->next)
	{

		if (current->element.first== c)
		{
			if (current->element.second == v)
			{
				if (prev == NULL)
				{
					this->list.head = current->next;
				}
				else
				{
					prev->next = current->next;
				}
				delete current;
				--list.size;
				return true;
			}
		}
	}
	return false;
}

vector<TValue> MultiMap::search(TKey c) const
{
	//Complexity: O(n)
	/*
	Searches for values with a given key
	Pre: c is an integer number
	Post: a vector of type TElem, if no elements were found the vector is empty
	*/
	SLLNode* current = list.head;
	vector<TValue> elemets;
	while (current != NULL)
	{
		if (current->element.first == c)
			elemets.push_back(current->element.second);
		current = current->next;
		
	}
	return elemets;
}

int MultiMap::size() const
{
	//Complexity: Theta(1)
	//Returns the size of the MultiMap
	//Pre: true
	//Post: an integer representing the size of the SLL, the size should be larger than 0
	return list.size;
}

bool MultiMap::isEmpty() const
{
	//Complexity: Theta(1)
	//Returns the size of the MultiMap
	return list.size == 0;
}

MultiMapIterator MultiMap::iterator() const
{
	//Complexity: Theta(1)
	//Returns an iterator for the multimap
	return MultiMapIterator(*this);
}

void MultiMap::empty()
{
	//Complexity: Theta(n) - n size of SLL
	//Removes all elements from the list
	//Pre: list is an SLL
	//Post: |list'| = 0
	SLLNode* current = list.head;
	SLLNode* nextElem;
	while (current != NULL)
	{
		nextElem = current->next;
		delete current;
		current = nextElem;
	}
	list.head = NULL;
	list.size = 0;
}


MultiMap::~MultiMap()
{
	SLLNode* current = list.head;
	while (current != NULL)
	{
		SLLNode* aux = current->next;
		delete current;
		current = aux;
	}
}
