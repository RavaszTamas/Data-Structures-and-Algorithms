#include "SortedBagIterator.h"
#include <exception>
#include <stack> 
#include <fstream>

#define emptyVal INT_MIN


SortedBagIterator::SortedBagIterator(const SortedBag & c) : c{ c }
{
	this->current = this->c.root;
	this->currentAmount = 0;
	if (current != -1)
	{
		while (current != -1)
		{
			this->inorderParse.push(current);
			this->current = this->c.elements[current].left;
		}
		this->current = this->inorderParse.top();
		this->inorderParse.pop();

	}
}

void SortedBagIterator::indorderPrint()
{
	std::stack<int> auxs;
	std::ofstream out("indorder.txt");
	int curr = this->c.root;
	if (curr != -1)
	{
		while (curr != -1 || auxs.empty() == false)
		{
			while (curr != -1)
			{
				auxs.push(curr);
				curr = this->c.elements[curr].left;
			}
			curr = auxs.top();
			auxs.pop();
			out << this->c.elements[curr].info.first << " " << this->c.elements[curr].info.second << std::endl;
			curr = this->c.elements[curr].right;

		}
	}
}

void SortedBagIterator::first()
{
	this->current = this->c.root;
	this->currentAmount = 0;
	if (current != -1)
	{
		while (current != -1)
		{
			this->inorderParse.push(current);
			this->current = this->c.elements[current].left;
		}
		this->current = this->inorderParse.top();
		this->inorderParse.pop();
	}

}

void SortedBagIterator::next()
{
	if (this->valid())
	{
		if (this->currentAmount < this->c.elements[this->current].info.second-1)
		{
			this->currentAmount++;
		}
		else
		{
			this->current = this->c.elements[this->current].right;
			this->currentAmount = 0;
			while (current != -1)
			{
				this->inorderParse.push(current);
				this->current = this->c.elements[current].left;
			}
			if (!inorderParse.empty())
			{
				this->current = this->inorderParse.top();
				this->inorderParse.pop();
			}
		}

	}
	else
		throw std::exception();
}

bool SortedBagIterator::valid() const
{
	return current != -1;
}

TComp SortedBagIterator::getCurrent() const
{
	if (this->valid())
	{
		return this->c.elements[current].info.first;
	}
	else
		throw std::exception();
}
