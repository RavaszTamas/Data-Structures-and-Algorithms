#include "SortedBag.h"
#include <cmath>
#include "SortedBagIterator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define emptyVal -1

using namespace std;



void SortedBag::resize()
{

	Node* newElements = new Node[this->capacity*2];

	for (int i = 0; i < this->capacity; ++i)
	{
		newElements[i] = this->elements[i];
	}

	for (int i = this->capacity; i < this->capacity*2; ++i)
	{
		newElements[i].info.first = emptyVal;
		newElements[i].info.second = 0;
		newElements[i].left = i + 1;
		newElements[i].right = -1;
		newElements[i].parent = -1;

	}
	delete this->elements;
	this->elements = newElements;
	elements[this->capacity*2 - 1].left = -1;
	this->firstEmpty = this->capacity;
	this->capacity *= 2;
	//this->printBag();
}



SortedBag::SortedBag(Relation r)
{
	this->r = r;
	this->capacity = 20;
	this->firstEmpty = 0;
	elements = new Node[this->capacity];
	for (int i = 0; i < this->capacity; ++i)
	{
		elements[i].info.first = emptyVal;
		elements[i].info.second = 0;
		elements[i].left = i+1;
		elements[i].right = -1;
		elements[i].parent = -1;

	}
	elements[this->capacity - 1].left= -1;
}

void SortedBag::fileBag() const
{
	ofstream out("out.txt");
	out << setw(10) << "Value: ";
	for (int i = 0; i < this->capacity; i++)
	{
		out << this->elements[i].info.first << " ";
	}
	out << endl;
	out << setw(10) << "Amount: ";

	for (int i = 0; i < this->capacity; i++)
	{
		out << this->elements[i].info.second << " ";;
	}
	out << endl;
	out << setw(10) << "Left: ";
	for (int i = 0; i < this->capacity; i++)
	{
		out << this->elements[i].left << " ";;
	}
	out << endl;
	out << setw(10) << "Right: ";
	for (int i = 0; i < this->capacity; i++)
	{
		out << this->elements[i].right << " ";;
	}
	out << endl;
	out << setw(10) << "Parent: ";
	for (int i = 0; i < this->capacity; i++)
	{
		out << this->elements[i].parent << " ";;
	}
	out << endl << "Empty: " << this->firstEmpty << endl;


}

void SortedBag::printBag() const
{
	cout << setw(10) << "Value: ";
	for (int i = 0; i < this->capacity; i++)
	{
		cout  << this->elements[i].info.first << " ";
	}
	cout << endl;
	cout << setw(10) << "Amount: ";

	for (int i = 0; i < this->capacity; i++)
	{
		cout <<  this->elements[i].info.second << " ";;
	}
	cout << endl;
	cout << setw(10) << "Left: ";
	for (int i = 0; i < this->capacity; i++)
	{
		cout  << this->elements[i].left << " ";;
	}
	cout << endl;
	cout << setw(10) << "Right: ";
	for (int i = 0; i < this->capacity; i++)
	{
		cout  << this->elements[i].right << " ";;
	}
	cout << endl;
	cout << setw(10) << "Parent: ";
	for (int i = 0; i < this->capacity; i++)
	{
		cout  << this->elements[i].parent << " ";;
	}
	cout<<endl << "Empty: " << this->firstEmpty << endl;


}

void SortedBag::add(TComp e)
{
	int current = this->root;
	int parent = -1;
	while (current != -1 && this->elements[current].info.first != e)
	{
		parent = current;
		if (this->r(this->elements[current].info.first, e))
		{
			current = this->elements[current].right;
		}
		else
		{
			current = this->elements[current].left;
		}

	}
	if (parent == -1 && current == -1)
	{
		this->root = 0;
		this->firstEmpty = this->elements[this->firstEmpty].left;
		this->elements[this->root].info.first = e;
		this->elements[this->root].info.second = 1;
		this->elements[this->root].left = -1;
		this->elements[this->root].right = -1;
		this->uniqueNum++;
	}
	else if (current != -1)
	{
		this->elements[current].info.second++;
	}
	else
	{
		if (this->firstEmpty == -1)
			this->resize();
		int occupiedPos = this->firstEmpty;
		this->firstEmpty = this->elements[this->firstEmpty].left;

		this->elements[occupiedPos].info.first = e;
		this->elements[occupiedPos].info.second = 1;
		this->elements[occupiedPos].left = -1;
		this->elements[occupiedPos].right = -1;
		this->elements[occupiedPos].parent = parent;

		if (this->r(this->elements[parent].info.first, e))
		{
			this->elements[parent].right = occupiedPos;
		}
		else
		{
			this->elements[parent].left = occupiedPos;

		}
		this->uniqueNum++;

	}
	this->sizeOfBag++;
}

int SortedBag::uniqueCount() const
{
	return this->uniqueNum;


	std::stack<int> auxs;
	int curr = this->root;
	int result = 0;
	if (curr != -1)
	{
		while (curr != -1 || auxs.empty() == false)
		{
			while (curr != -1)
			{
				auxs.push(curr);
				curr = this->elements[curr].left;
			}
			curr = auxs.top();
			auxs.pop();
			++result;
			curr = this->elements[curr].right;

		}
	}
	return result;
}



bool SortedBag::remove(TComp e)
{
	bool found = false;
	int current = this->root;
	while (current != -1 && !found)
	{
		if (this->elements[current].info.first == e)
		{
			found = true;
		}
		else if (this->r(this->elements[current].info.first, e))
		{
			current = this->elements[current].right;
		}
		else
		{
			current = this->elements[current].left;
		}
	}
	if (found)
	{
		if (this->elements[current].info.second > 1)
		{
			this->elements[current].info.second--;
		}
		else
		{
			if (this->elements[current].right == -1 && this->elements[current].left == -1)
			{
				if (this->elements[current].parent == -1)
				{
					this->elements[current].info.first = emptyVal;
					this->elements[current].info.second = 0;
					this->elements[current].left = this->firstEmpty;
					this->firstEmpty = current;

				}
				else
				{
					if (this->elements[this->elements[this->elements[current].parent].right].info.first == this->elements[current].info.first)
					{
						this->elements[this->elements[current].parent].right = -1;
					}
					else
					{
						this->elements[this->elements[current].parent].left = -1;

					}
					this->elements[current].info.first = emptyVal;
					this->elements[current].info.second = 0;
					this->elements[current].left = -1;
					this->elements[current].right = -1;
					this->elements[current].parent = -1;
					this->elements[current].left = this->firstEmpty;
					this->firstEmpty = current;

				}
			}
			else if (this->elements[current].right == -1)
			{
				int toDelete = this->elements[current].left;
				this->elements[current].info = this->elements[toDelete].info;
				this->elements[current].right = this->elements[toDelete].right;
				this->elements[current].left = this->elements[toDelete].left; // set move up element

				if (this->elements[current].left != -1)
				{
					this->elements[this->elements[current].left].parent = current; //set new parents
				}
				if (this->elements[current].right != -1)
				{
					this->elements[this->elements[current].right].parent = current; //set new parents

				}
				this->elements[toDelete].info.first = emptyVal;
				this->elements[toDelete].info.second = 0;
				this->elements[toDelete].right = -1;
				this->elements[toDelete].left = -1;
				this->elements[toDelete].parent = -1;

				this->elements[toDelete].left = this->firstEmpty;//ADD TO first empty
				this->firstEmpty = toDelete;

			}
			else if (this->elements[current].left == -1)
			{
				int toDelete = this->elements[current].right;
				this->elements[current].info = this->elements[toDelete].info;
				this->elements[current].right = this->elements[toDelete].right;
				this->elements[current].left = this->elements[toDelete].left;

				if (this->elements[current].left != -1)
				{
					this->elements[this->elements[current].left].parent = current;
				}
				if (this->elements[current].right != -1)
				{
					this->elements[this->elements[current].right].parent = current;

				}

				this->elements[toDelete].info.first = emptyVal;
				this->elements[toDelete].info.second = 0;
				this->elements[toDelete].right = -1;
				this->elements[toDelete].left = -1;
				this->elements[toDelete].parent = -1;

				this->elements[toDelete].left = this->firstEmpty;
				this->firstEmpty = toDelete;

			}
			else
			{
				int nextItem = this->elements[current].right;
				while (nextItem != -1 && this->elements[nextItem].left != -1)
				{
					nextItem = this->elements[nextItem].left;
				}
				this->elements[current].info = this->elements[nextItem].info;

				if (this->elements[this->elements[current].right].info.first == this->elements[current].info.first)
				{
					if(this->elements[this->elements[current].right].right != -1)
						this->elements[this->elements[this->elements[current].right].right].parent = current;
					this->elements[current].right = this->elements[this->elements[current].right].right;
				}
				else
				{
					if (this->elements[nextItem].right != -1)
						this->elements[this->elements[nextItem].right].parent = this->elements[nextItem].parent;
					this->elements[this->elements[nextItem].parent].left = this->elements[nextItem].right;
				}

				/*

				if (this->r(this->elements[this->elements[nextItem].parent].info.first, this->elements[nextItem].info.first))
				{
					this->elements[this->elements[nextItem].parent].right = -1;
				}
				else
				{
					this->elements[this->elements[nextItem].parent].left = -1;
				}
				*/


				this->elements[nextItem].info.first = emptyVal;
				this->elements[nextItem].info.second = 0;
				this->elements[nextItem].right = -1;
				this->elements[nextItem].left = -1;
				this->elements[nextItem].parent = -1;


				this->elements[nextItem].left = this->firstEmpty;
				this->firstEmpty = nextItem;

			}
			this->uniqueNum--;
		}
		this->sizeOfBag--;
	}
	//if (firstEmpty == 6400)
	//	cout << endl << "FAIL" << endl << current << endl << e << endl;
	return found;

}

bool SortedBag::search(TComp e) const
{
	bool found = false;
	int current = this->root;
	while (current != -1 && !found)
	{
		if (this->elements[current].info.first == e)
		{
			found = true;
		}
		else if (this->r(this->elements[current].info.first , e))
		{
			current = this->elements[current].right;
		}
		else
		{
			current = this->elements[current].left;
		}
	}
	return found;
}

int SortedBag::nrOccurrences(TComp e) const
{
	int occurences = 0;
	int current = this->root;
	while (current != -1 && occurences == 0)
	{
		if (this->elements[current].info.first == e)
		{
			occurences = elements[current].info.second;
		}
		else if (this->r(this->elements[current].info.first, e))
		{
			current = this->elements[current].right;
		}
		else
		{
			current = this->elements[current].left;
		}
	}
	return occurences;
}



int SortedBag::size() const
{
	return this->sizeOfBag;
}
SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}


bool SortedBag::isEmpty() const
{
	return this->sizeOfBag == 0;
}

SortedBag::~SortedBag()
{
	delete this->elements;
}
