//	WGraph.h
//	Daniel Blasher
//	CS260 Lab 7

#ifndef WGraph_h
#define WGraph_h

#include <string>

//Using Jim's Edge and Node code
struct wEdge
{
	//added begin
	int beginIndex;
	int endIndex;
	//added weight
	int weight;
	wEdge * next;
};

struct wNode
{
	char name;
	bool visited;
	wEdge * connects;
};
//wrote a priorityQueue that works with Edges
class PQ {
private:
	int size = 30;
	int top = 0;
public:

	int count = 0;
	wEdge * myarray;
	//int * theTable;

	PQ();
	PQ(int);
	~PQ();
	bool isEmpty();
	bool isFull();
	//void resize();
	wEdge removeLow();
	void shiftUp(int index);
	void shiftDown();
	void addItem(wEdge e);
};

//Using Jim's graph, modified AddEdge and wrote minCostTree()
class WGraph {
public:
	WGraph();
	virtual ~WGraph();

	void addNode(char name);

	//modified and renamed this method
	bool addWEdge(char starts, char ends, int weight);

	std::string listNodes();

	//Daniel's version of displayEdges
	std::string displayEdges();
	std::string displayMatrix();

	//new method for showing minimum cost spanning tree
	std::string	minCostTree(char name);
	std::string breadthFirst(char name);
	std::string depthFirst(char name);

private:
	static const int SIZE = 20;
	int numNodes;
	wNode * nodeList[SIZE];
	int edgeMatrix[SIZE][SIZE];

	int findNode(char name);
	void resetVisited();

};

#endif