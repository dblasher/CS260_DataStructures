//	DGraph.cpp
//	Daniel Blasher
//	CS260 Lab 7

#include "DGraph.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

// for breadth first and depth first traversals
#include <queue>
#include <stack>

//using Jim's graph.cpp code, just modified AddEdge and wrote connectTable()

 // constructor
DGraph::DGraph()
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
DGraph::~DGraph()
{
	// delete all connections from each node in nodeList
	for (int i = 0; i < numNodes; i++)
	{
		// similar to destructor on linked list
		Edge * ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			Edge * temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}
}

// add a new node to the graph
// only failure is if graph arrays are full
void DGraph::addNode(char name)
{
	// alternately, double the size of everything and start over
	if (numNodes >= SIZE)
		throw std::overflow_error("Graph size exceeded!!");

	// create a node with this name
	// initialize it with no edges and not yet visited
	Node * temp = new Node;
	temp->name = name;
	temp->visited = false;
	temp->connects = nullptr;

	// add to the list of nodes in graph
	nodeList[numNodes++] = temp;
}


// add a new edge to the graph
// return false and do nothing if either end is invalid
// otherwise add to both nodes edge lists and to the matrix
bool DGraph::addEdge(char starts, char ends)
{
	if (starts == ends)
		return false;

	int startIndex = findNode(starts);
	int endIndex = findNode(ends);

	if (startIndex == -1 or endIndex == -1)
		return false;

	// set one link in edgeMatrix
	edgeMatrix[startIndex][endIndex] = 1;

	// create one new edges because this is a directed graph
	Edge * startEnd = new Edge;
	startEnd->endIndex = endIndex;
	startEnd->next = nullptr;
	startEnd->next = nodeList[startIndex]->connects;
	nodeList[startIndex]->connects = startEnd;

	return true;
}


// linear search for a node with this name
// return -1 if not found
// otherwise return its index in the nodeList
int DGraph::findNode(char name)
{
	for (int i = 0; i < numNodes; i++)
		if (nodeList[i]->name == name)
			return i;
	return -1;
}


// listing of nodes in the order
// they were added to the graph
std::string DGraph::listNodes()
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
std::string DGraph::displayEdges()
{
	std::stringstream ss;
	for (int i = 0; i < numNodes; i++)
	{
		// add the node name to the display
		ss << nodeList[i]->name;
		ss << "-";

		// walk down its list of edges and add them also
		Edge * ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			ss << nodeList[ptr->endIndex]->name;
			ss << " ";
			ptr = ptr->next;
		}
		// end this line of output
		ss << std::endl;
	}
	return ss.str();
}

//new method Daniel wrote
//use depth first traversal starting at nodeList[0]
std::string DGraph::connectTable() {
	std::stringstream ss;
	ss << "Connectivity Table using Depth First " << std::endl;
	//run depth first on each node
	for (int i = 0; i < numNodes; i++) {
		ss << depthFirst(nodeList[i]->name);
	}

	return ss.str();
}

// display the adjacency matrix
// as 0 for no connection and 1 for connection
std::string DGraph::displayMatrix()
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
std::string DGraph::depthFirst(char name)
{
	std::stringstream ss;
	//ss << "Depth First Traversal starting at " << name << std::endl;

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
		Edge * ptr = nodeList[index]->connects;
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
std::string DGraph::breadthFirst(char name)
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
	std::queue <Node *> theQueue;

	// process this node, add to queue, mark as visited, output
	Node * nodePtr = nodeList[index];
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
		Edge * edgePtr = nodePtr->connects;
		while (edgePtr != nullptr)
		{
			// get a neigbor
			int neighborIndex = edgePtr->endIndex;

			// if not visited, process
			if (!nodeList[neighborIndex]->visited)
			{
				Node* neighbor = nodeList[neighborIndex];
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
void DGraph::resetVisited()
{
	for (int i = 0; i < numNodes; i++)
		nodeList[i]->visited = false;
}


