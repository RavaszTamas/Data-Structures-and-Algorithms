#include <exception>
#include "DynamicArray.h"
#include <iostream>
#include "DAIterator.h"

using namespace std;

typedef int TElem;


class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "Invalid value!";
  }
} myexception;




void DynamicArray::resize(int newSize)
{
			TElem* newDynamicArray = new TElem[newSize];
			for(int i = 0; i < lengthOfArray && i < newSize; ++i)
			{
				newDynamicArray[i] = dynamicArray[i];
			}

			delete[] dynamicArray;

			dynamicArray = newDynamicArray;
			cappacityOfArray = newSize;
}


	//constructor

	//throws exception if capacity is 0 or negative

DynamicArray::DynamicArray(int capacity)
	{
		if (capacity <= 0)
			throw myexception;
		dynamicArray = new TElem[capacity];
		lengthOfArray = 0;
		cappacityOfArray = capacity;
	}


	//returns the size (number of elements) from the DynamicArray

	int DynamicArray::size() const
	{
		return lengthOfArray;
	}



	//returns the element from a given position (indexing starts from 0)

	//throws exception if pos is not a valid position

	TElem DynamicArray::getElement(int pos) const
	{
		if (pos < 0 || pos >= lengthOfArray)
			throw myexception;

		return dynamicArray[pos];
	}



	//changes the element from a pozition to a different value

	//returns the old element from pozition poz

	//throws exception if pos is not a valid position

	TElem DynamicArray::setElement(int pos, TElem newElem)
	{
		if (pos < 0 || pos >= lengthOfArray)
			throw myexception;

		TElem oldElement = dynamicArray[pos];
		
		dynamicArray[pos] = newElem;
		return oldElement;
	}


	//adds a new element to the end of the DynamicArray

	void DynamicArray::addToEnd(TElem newElem)
	{
		if (lengthOfArray == cappacityOfArray)
		{
			resize(cappacityOfArray*2);
		}
		dynamicArray[lengthOfArray] = newElem;
		lengthOfArray +=1;
		
	}



	//adds a new element to a given position in a DynamicArray

	//throws exception if pos is not a valid position

	void DynamicArray::addToPosition(int pos, TElem newElem)
	{
		if (pos < 0 || pos > lengthOfArray)
			throw myexception;

		if(lengthOfArray == cappacityOfArray)
		{
			resize(cappacityOfArray*2);
		}
		for(int i = lengthOfArray; i > pos; --i)
		{
			dynamicArray[i] = dynamicArray[i-1];
		}

		lengthOfArray += 1;
		dynamicArray[pos] = newElem;
	}


	//removes an element from a given position

	//returns the removed element

	//throws exception if pos is not a valid position

	TElem DynamicArray::remove(int pos)
	{
		if (pos < 0 || pos >= lengthOfArray)
			throw myexception;

		if(lengthOfArray <= cappacityOfArray/4)
		{
			resize(lengthOfArray);
		}

		TElem tempElem = dynamicArray[pos];

		for(int i = pos; i < lengthOfArray; ++i)
		{
			dynamicArray[i] = dynamicArray[i+1];
		}

		--lengthOfArray;

		return tempElem;
	}

	DAIterator DynamicArray::iterator() const
	{
		return DAIterator(*this);
	}



	//returns an iterator for the DynamicArray




	//destructor

	DynamicArray::~DynamicArray()
	{
	  delete [] dynamicArray;
	}

