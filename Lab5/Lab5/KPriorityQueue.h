#include <utility>

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

struct binaryHeap
{
	Element* elements;
	int cap;
	int len;
};

class KPriorityQueue {

private:

	//representation of the K PriorityQueue	
	int k;
	int size;
	binaryHeap endHeap;
	binaryHeap kHeap;
	Relation relation;

	void resizeEndHeap();


	void bubbleDownKHeap(int p);


	void bubbleDownEndHeap(int p);


	void bubbleUpKHeap(int p);

	void bubbleUpEndHeap(int p);

	void resize();

public:

	//throws an exception if k is less than or equal to 0
	KPriorityQueue(Relation r, int k);

	//adds an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the kth highest priority with respect to the order relation
	//throws exception if the queue has less than k elements
	Element top()  const;


	//removes and returns the element with the kth highest priority
	//throws exception if the queue has less than k elements
	Element pop();

	//checks if the queue has less than k elements
	bool atMostKMinusOne() const;


	//destructor
	~KPriorityQueue();



};