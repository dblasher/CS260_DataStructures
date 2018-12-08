//	DGraph.h
//	Daniel Blasher
//	CS260 Lab 7

#ifndef DGraph_h
#define DGraph_h

#include <string>
//Using Jim's Edge and Node code
struct Edge
{
	int endIndex;
	Edge * next;
};

struct Node
{
	char name;
	bool visited;
	Edge * connects;
};

//Using Jim's graph, modified AddEdge and Display Edges
class DGraph {
public:
	DGraph();
	virtual ~DGraph();

	void addNode(char name);

	//Daniel's modified version of addEdge
	bool addEdge(char starts, char ends);

	std::string listNodes();
	std::string displayEdges();
	std::string displayMatrix();

	//new method for showing possible connections
	std::string connectTable();

	std::string breadthFirst(char name);
	std::string depthFirst(char name);

private:
	static const int SIZE = 20;
	int numNodes;
	Node * nodeList[SIZE];
	int edgeMatrix[SIZE][SIZE];

	int findNode(char name);
	void resetVisited();

};

#endif