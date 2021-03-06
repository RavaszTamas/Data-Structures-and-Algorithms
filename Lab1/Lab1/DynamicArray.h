#pragma once

typedef int TElem;
using namespace std;



class DynamicArray {

		friend class DAIterator;


private:

	/*representation of Dynamic Array*/
	int cappacityOfArray;
	int lengthOfArray;
	TElem* dynamicArray;

	void resize(int newSize);


public:



	//constructor

	//throws exception if capacity is 0 or negative

	DynamicArray(int capacity);



	//returns the size (number of elements) from the DynamicArray

	int size() const;



	//returns the element from a given position (indexing starts from 0)

	//throws exception if pos is not a valid position

	TElem getElement(int pos) const;



	//changes the element from a pozition to a different value

	//returns the old element from pozition poz

	//throws exception if pos is not a valid position

	TElem setElement(int pos, TElem newElem);



	//adds a new element to the end of the DynamicArray

	void addToEnd(TElem newElem);



	//adds a new element to a given position in a DynamicArray

	//throws exception if pos is not a valid position

	void addToPosition(int pos, TElem newElem);



	//removes an element from a given position

	//returns the removed element

	//throws exception if pos is not a valid position

	TElem remove(int pos);



	//returns an iterator for the DynamicArray

	DAIterator iterator() const;



	//destructor

	~DynamicArray();

};