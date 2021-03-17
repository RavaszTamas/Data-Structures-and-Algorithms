#include "KPriorityQueue.h"
#include <exception>

KPriorityQueue::KPriorityQueue(Relation r, int k)
{
	if (k <= 0)
		throw exception("Invalid k value! Most be positive!");
	this->relation = r;
	this->k = k;
	this->endHeap.cap = 16;
	this->endHeap.elements = new Element[this->endHeap.cap];
	this->endHeap.len = 0;
	this->kHeap.len = 0;
	this->kHeap.elements = new Element[k];
}//Theta(1)
/*
void KPriorityQueue::push3(TElem e, TPriority p)
{
	Element element(e, p);
	if (this->kHeap.len < this->k)
	{
		if (this->relation(p, this->kHeap.elements[0].second) == 0)
		{
			Element temporary = this->kHeap.elements[0];
			this->kHeap.elements[0] = element;
			this->kHeap.elements[this->kHeap.len] = temporary;
			this->kHeap.len++;
			bubbleUpKHeap(this->kHeap.len - 1);

		}
		else {
			this->kHeap.elements[this->kHeap.len] = element;
			this->kHeap.len++;
			bubbleUpKHeap(this->kHeap.len - 1);
		}
	}
	else {

		if (this->relation(element.second, this->kHeap.elements[0].second))
		{
			//put it in kHeap
			Element temporary = this->kHeap.elements[0];
			this->kHeap.elements[0] = element;
			bubbleDownKHeap(0);
			//put the first element in endHeap
			if (this->endHeap.len == this->endHeap.cap)
				resizeEndHeap();
			this->endHeap.elements[this->endHeap.len] = temporary;
			this->endHeap.len++;
			bubbleUpEndHeap(this->endHeap.len - 1);
		}
		else
		{
			//add in endHeap
			if (this->endHeap.len == this->endHeap.cap)
				resizeEndHeap();
			this->endHeap.elements[this->endHeap.len] = element;
			this->endHeap.len++;
			bubbleUpEndHeap(this->endHeap.len - 1);
		}
	}
	this->size++;
}//O(log2(n))
*/
//adds an element with priority to the queue
/*
void KPriorityQueue::push2(TElem e, TPriority p)
{
	Element element(e, p);
	if (this->kHeap.len < this->k)
	{
		this->kHeap.elements[this->kHeap.len] = element;
		this->kHeap.len++;
		bubbleUpKHeap(this->kHeap.len);
	}
	else {
		TPriority minim = 9999;
		int position = 0;
		for (int i = 0; i < this->k; i++)
		{
			if (this->relation(minim, this->kHeap.elements[i].second))
			{
				minim = this->kHeap.elements[i].second;
				position = i;
			}
		}
		if (this->relation(this->kHeap.elements[position].second, element.second))
		{
			//add in endHeap
			if (this->endHeap.len == this->endHeap.cap)
				resizeEndHeap();
			this->endHeap.elements[this->endHeap.len] = element;
			this->endHeap.len++;
			bubbleUpEndHeap(this->endHeap.len);
		}
		else
		{
			//add in kHeap
			if (this->endHeap.len == this->endHeap.cap)
				resizeEndHeap();
			this->endHeap.elements[this->endHeap.len] = this->kHeap.elements[position];
			this->endHeap.len++;
			bubbleUpEndHeap(this->endHeap.len);
			this->kHeap.elements[position] = element;
			bubbleUpKHeap(this->k);
		}
	}
	this->size++;
}//O(log2(n))
*/
void KPriorityQueue::push(TElem e, TPriority p)
{
	if (this->endHeap.len  == this->endHeap.cap)
		this->resize();

	if (this->atMostKMinusOne())
	{
		this->kHeap.elements[this->kHeap.len] = Element{ e,p };
		this->kHeap.len++;
		bubbleUpKHeap(this->kHeap.len - 1);
		
	}
	else
	{
		if (this->relation(p,this->kHeap.elements[0].second))
		{
			Element elemToSwitch = this->kHeap.elements[0];
			this->kHeap.elements[0] = Element{ e, p };
			///bubble-down for k heap queue
			
			//TODO
			this->bubbleDownKHeap(0);

			///new lement for the primary priority queue is that last k biggest priority element
			this->endHeap.elements[this->endHeap.len] = elemToSwitch;
		}
		else
		{
			this->endHeap.elements[this->endHeap.len] = Element{ e, p };
		}
		this->endHeap.len++;
		///bubble-up
		this->bubbleUpEndHeap(this->endHeap.len - 1);

		
	}
	this->size++;
}//O(log(n))

Element KPriorityQueue::top() const
{
	if (this->atMostKMinusOne())
	{
		throw exception("There are no enough elements in the queue!");
	}
	return this->kHeap.elements[0];
}//Theta(1)

Element KPriorityQueue::pop()
{
	if (this->atMostKMinusOne())
	{
		throw exception("There are no enough elements in the queue!");
	}
	Element topElem = this->kHeap.elements[0];
	
	this->kHeap.elements[0] = this->endHeap.elements[0];
	this->endHeap.elements[0] = this->endHeap.elements[this->endHeap.len - 1];
	this->endHeap.len--;

	bubbleDownKHeap(0);
	bubbleDownEndHeap(0);

	this->size--;
	return topElem;

}//O(log(n))

bool KPriorityQueue::atMostKMinusOne() const
{
	return this->size < this->k;
}//Theta(1)

void KPriorityQueue::resizeEndHeap()
{
	Element* newElems = new Element[this->endHeap.cap * 2];
	for (int i = 0; i < this->endHeap.cap; ++i)
		newElems[i] = this->endHeap.elements[i];

	this->endHeap.cap *= 2;
	delete[] this->endHeap.elements;
	this->endHeap.elements = newElems;

	/*
	this->endHeap.cap *= 2;
	Element* elements = (Element*)malloc(sizeof(Element)*(this->endHeap.cap));
	for (int i = 0; i < this->endHeap.len; i++)
	elements[i] = this->endHeap.elements[i];
	delete[] this->endHeap.elements;
	this->endHeap.elements = elements;
	*/
}

void KPriorityQueue::bubbleDownKHeap(int p)
{
	int poz = p;
	Element elem = this->kHeap.elements[poz];
	int maxChild = -1;
	while (poz < this->kHeap.len - 1)
	{
		maxChild = -1;
		if (poz * 2 <= this->kHeap.len - 1)
			maxChild = poz * 2;
		if (poz * 2 + 1 <= this->kHeap.len - 1 && !this->relation(this->kHeap.elements[2 * poz + 1].second, this->kHeap.elements[2 * poz].second))
			maxChild = poz * 2 + 1;
		if (maxChild != -1 && !this->relation(this->kHeap.elements[maxChild].second, elem.second))
		{
			Element temp = this->kHeap.elements[poz];
			this->kHeap.elements[poz] = this->kHeap.elements[maxChild];
			this->kHeap.elements[maxChild] = temp;
			poz = maxChild;
		}
		else
			poz = this->kHeap.len;
	}
}

void KPriorityQueue::bubbleDownEndHeap(int p)
{
	int poz = p;
	Element elem = this->endHeap.elements[poz];
	int maxChild = -1;
	while (poz < this->endHeap.len - 1)
	{
		maxChild = -1;
		if (poz * 2 <= this->endHeap.len - 1)
			maxChild = poz * 2;
		if (poz * 2 + 1 <= this->endHeap.len - 1 && this->relation(this->endHeap.elements[2 * poz + 1].second, this->endHeap.elements[2 * poz].second))
			maxChild = poz * 2 + 1;
		if (maxChild != -1 && this->relation(this->endHeap.elements[maxChild].second, elem.second))
		{
			Element temp = this->endHeap.elements[poz];
			this->endHeap.elements[poz] = this->endHeap.elements[maxChild];
			this->endHeap.elements[maxChild] = temp;
			poz = maxChild;
		}
		else
			poz = this->endHeap.len;
	}

}

void KPriorityQueue::bubbleUpKHeap(int p)
{
	int poz = p;
	Element element = this->kHeap.elements[p];
	int parent = p / 2;
	while (poz > 0 && !this->relation(element.second, this->kHeap.elements[parent].second))
	{
		this->kHeap.elements[poz] = this->kHeap.elements[parent];
		poz = parent;
		parent = poz / 2;
	}
	this->kHeap.elements[poz] = element;
}//O(log2(n))


void KPriorityQueue::bubbleUpEndHeap(int p)
{
	int poz = p;
	Element element = this->endHeap.elements[p];
	int parent = p / 2;
	while (poz > 0 && this->relation(element.second, this->endHeap.elements[parent].second))
	{
		this->endHeap.elements[poz] = this->endHeap.elements[parent];
		poz = parent;
		parent = poz / 2;
	}
	this->endHeap.elements[poz] = element;
}//O(log2(n))


void KPriorityQueue::resize()
{
	Element* newElems = new Element[this->endHeap.cap * 2];
	for (int i = 0; i < this->endHeap.cap; ++i)
		newElems[i] = this->endHeap.elements[i];

	this->endHeap.cap *= 2;
	delete[] this->endHeap.elements;
	this->endHeap.elements = newElems;
}//Theta(n)


KPriorityQueue::~KPriorityQueue()
{
	delete[] this->endHeap.elements;
	delete[] this->kHeap.elements;
}//Theta(1)
