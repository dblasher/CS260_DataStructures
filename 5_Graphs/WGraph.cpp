//	WGraph.cpp
//	Daniel Blasher
//	CS260 Lab 7

#include "WGraph.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

//using Jim's graph.cpp code, just added minCostTree()

// to create formatted strings to return
#include <sstream>
#include <iomanip>

// for breadth first and depth first traversals
#include <queue>
#include <stack>


#pragma region PriorityQueue
PQ::PQ() {
	myarray = new wEdge[size];
	//theTable = new int[size];
}

PQ::PQ(int n) {
	if (n < 1)
		myarray = new wEdge[size];
	else {
		myarray = new wEdge[n];
		size = n;
	}
}

PQ::~PQ() {
	delete[] myarray;
}

bool PQ::isEmpty() {
	if (count <= 0)
		return true;
	else
		return false;
}

bool PQ::isFull() {
	if (count >= size)
		return true;

	else
		return false;

}

wEdge PQ::removeLow() {
	wEdge item = myarray[0];
	shiftDown();
	count--;
	return item;
}

void PQ::shiftUp(int index) {
	//myarray[index] is temporarily duplicated, it should be overwritten with a new value in addItem
	while (index < count) {
		myarray[index + 1] = myarray[index++];
	}
}

void PQ::shiftDown() {
	//after removing smallest edge weight, shift everything down one index, overwriting the previous value at index 0
	int index = 0;
	while (index < count - 1) {
		myarray[index] = myarray[++index];
	}
}

void PQ::addItem(wEdge e) {
	//comparing incoming item weight starting at the beginning, move up until you find something bigger
	for (int i = 0; i < count; i++) {
		if (e.weight <= myarray[i].weight) {
			shiftUp(i);
			myarray[i] = e;
			count++;
			return;
		}
	}
	//this is the biggest Edge, add it the end
	myarray[count++] = e;
	return;
}
#pragma endregion PriorityQueue
 // constructor
WGraph::WGraph()
{
	// initialize number of nodes in list
	numNodes = 0;

	// initialize nodeList to nullptrs
	for (int i = 0; i < SIZE; i++)
		nodeList[i] = nullptr;

	// set up edge Matrix to start with no edges
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			edgeMatrix[i][j] = 0;
}

// destructor
WGraph::~WGraph()
{
	// delete all connections from each node in nodeList
	for (int i = 0; i < numNodes; i++)
	{
		// similar to destructor on linked list
		wEdge * ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			wEdge * temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}
}

// add a new node to the graph
// only failure is if graph arrays are full
void WGraph::addNode(char name)
{
	// alternately, double the size of everything and start over
	if (numNodes >= SIZE)
		throw std::overflow_error("Graph size exceeded!!");

	// create a node with this name
	// initialize it with no edges and not yet visited
	wNode * temp = new wNode;
	temp->name = name;
	temp->visited = false;
	temp->connects = nullptr;

	// add to the list of nodes in graph
	nodeList[numNodes++] = temp;
}


// add a new edge to the graph
// return false and do nothing if either end is invalid
// otherwise add to both nodes edge lists and to the matrix
bool WGraph::addWEdge(char starts, char ends, int weight)
{
	if (starts == ends)
		return false;

	int startIndex = findNode(starts);
	int endIndex = findNode(ends);

	if (startIndex == -1 or endIndex == -1)
		return false;

	// set both links in edgeMatrix
	edgeMatrix[startIndex][endIndex] = 1;
	edgeMatrix[endIndex][startIndex] = 1;

	// create two new edges (one for each direction)
	// and add one to each nodes list of edges
	wEdge * startEnd = new wEdge;
	startEnd->beginIndex = startIndex;
	startEnd->endIndex = endIndex;
	startEnd->weight = weight;
	startEnd->next = nullptr;
	startEnd->next = nodeList[startIndex]->connects;
	nodeList[startIndex]->connects = startEnd;

	wEdge * endStart = new wEdge;
	endStart->beginIndex = startIndex;
	endStart->endIndex = startIndex;
	endStart->weight = weight;
	endStart->next = nullptr;
	endStart->next = nodeList[endIndex]->connects;
	nodeList[endIndex]->connects = endStart;

	return true;
}

//new method written by Daniel
//breadth first	search that uses a priority queue of edges instead	of a FIFO of nodes.	
std::string	WGraph::minCostTree(char name) {
	std::stringstream ss;
	//ss << name << ":";
	ss << "Hey Jim, I couldn't get my priority queue working with Edge pointers, let me know when the solution gets posted"
		<< std::endl << "Thank you for all you taught me!"<< std::endl << "- Daniel Blasher";
	//std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
	PQ pq;
	//get the starting node and mark it as visited
	wNode * start = nodeList[findNode(name)];
	start->visited = true;
	//add its edges to the PQ
	wEdge * ptr = start->connects;
	while (ptr != nullptr) {
		//pq.addItem(ptr); //can't figure how to get this method to accept pointers to Edges, class was written on an array of Edges, not pointers
		ptr = ptr->next;
	}
	//get an edge, take its endIndex and check its edges
		while (!pq.isEmpty()) {
			wEdge temp = pq.removeLow();
			wNode * end = nodeList[temp.endIndex];
			end->visited = true;
			ss << end->name;
			wEdge * endPtr = end->connects;
			while (endPtr != nullptr) {
				if (nodeList[endPtr->endIndex]->visited != true) {
					for (int i = 0; i < pq.count; i++) {
						//if (pq[i]->endIndex == endPtr->beginIndex) {
							//compare the weights and keep the lowest one
							//if (pq[i]->weight > endPtr->weight)
							//	pq[i] = endPtr;
						//}
					}
				}
				endPtr = endPtr->next;
			}
		}
	return ss.str();
}

// linear search for a node with this name
// return -1 if not found
// otherwise return its index in the nodeList
int WGraph::findNode(char name)
{
	for (int i = 0; i < numNodes; i++)
		if (nodeList[i]->name == name)
			return i;
	return -1;
}


// listing of nodes in the order
// they were added to the graph
std::string WGraph::listNodes()
{
	std::string theList = "";
	for (int i = 0; i < numNodes; i++)
	{
		theList += nodeList[i]->name;
		theList += " ";
	}
	return theList;
}


// for each node in graph,
// display its edges, using the edgelist
std::string WGraph::displayEdges()
{
	std::stringstream ss;
	for (int i = 0; i < numNodes; i++)
	{
		// add the node name to the display
		ss << nodeList[i]->name;
		ss << "-";

		// walk down its list of edges and add them also
		wEdge * ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			ss << nodeList[ptr->endIndex]->name;
			ss << ptr->weight;
			ss << " ";
			ptr = ptr->next;
		}
		// end this line of output
		ss << std::endl;
	}
	return ss.str();
}


// display the adjacency matrix
// as 0 for no connection and 1 for connection
std::string WGraph::displayMatrix()
{
	std::stringstream ss;

	// output header line of destinations
	ss << std::setw(2) << " ";
	for (int i = 0; i < numNodes; i++)
		ss << std::setw(4) << nodeList[i]->name;
	ss << std::endl;

	// now output the array
	for (int i = 0; i < numNodes; i++)
	{
		// add the starting node
		ss << std::setw(2) << nodeList[i]->name;

		// now add its connections
		for (int j = 0; j < numNodes; j++)
			ss << std::setw(4) << edgeMatrix[i][j];

		// end the row
		ss << std::endl;
	}
	return ss.str();
}

// depth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string WGraph::depthFirst(char name)
{
	std::stringstream ss;
	ss << "Depth First Traversal starting at " << name << std::endl;

	// uses a stack to keep track of nodes to visit
	// could use Node * pointers to the nodes or names of nodes
	// instead am using index into nodeList
	std::stack<int> theStack;

	// get index of starting node
	int index = findNode(name);

	// if node does not exist, quit with error
	if (index == -1)
		return "Invalid starting node for Depth First Traversal";

	// set all nodes to not yet visited
	resetVisited();

	// process node (mark visited, add to stack, output name)
	nodeList[index]->visited = true;
	theStack.push(index);
	ss << name << " : ";

	// as long as stack is not empty of nodes
	while (not theStack.empty())
	{
		// get the node at the top of the stack
		index = theStack.top();

		// walk down list of edges for that node
		// see if any are unvisited
		// if they are, add to stack and repeat
		wEdge * ptr = nodeList[index]->connects;
		while (ptr != nullptr)
		{
			int neighborIndex = ptr->endIndex;

			// found one, add to stack, mark as visited, & output
			if (!nodeList[neighborIndex]->visited)
			{
				theStack.push(neighborIndex);
				nodeList[neighborIndex]->visited = true;
				ss << nodeList[neighborIndex]->name << " ";

				// stop traversal of edgelist for now
				break;
			}
			ptr = ptr->next;

		}   // end of nodeList traversal

			// no new neighbors added to queue,
			//  so remove this one from stack
		if (ptr == nullptr)
			theStack.pop();

	}   // end stack not empty

		// add terminating endline and return string
	ss << std::endl;
	return ss.str();
}

// breadth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string WGraph::breadthFirst(char name)
{
	std::stringstream ss;
	ss << "Breadth First Traversal starting at " << name << std::endl;

	// set all visited flags to false
	resetVisited();

	// get index of starting node
	int index = findNode(name);

	// if node does not exist, quit with error
	if (index == -1)
		return "Invalid starting node for Breadth First Traversal";

	// use a FIFO to keep track of nodes to check out
	// this time using a pointer to the node
	std::queue <wNode *> theQueue;

	// process this node, add to queue, mark as visited, output
	wNode * nodePtr = nodeList[index];
	theQueue.push(nodePtr);
	nodePtr->visited = true;
	ss << nodePtr->name << " : ";

	// as long as queue not empty
	while (!theQueue.empty())
	{
		// take the first one off
		nodePtr = theQueue.front();
		theQueue.pop();

		// add all unvisited neighbors to the queue
		wEdge * edgePtr = nodePtr->connects;
		while (edgePtr != nullptr)
		{
			// get a neigbor
			int neighborIndex = edgePtr->endIndex;

			// if not visited, process
			if (!nodeList[neighborIndex]->visited)
			{
				wNode* neighbor = nodeList[neighborIndex];
				theQueue.push(neighbor);
				neighbor->visited = true;
				ss << neighbor->name << " ";
			}
			edgePtr = edgePtr->next;

		}   // end of traversing edge list

	}   // end of processing queue

		// add terminal endline and return string
	ss << std::endl;
	return ss.str();
}

// helper function to reset all nodes to not visited
void WGraph::resetVisited()
{
	for (int i = 0; i < numNodes; i++)
		nodeList[i]->visited = false;
}
