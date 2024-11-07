#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <iostream>
#include "Node.h"

class Graph
{
private:

	std::map<int, Node*> node;

	std::vector< std::vector< float> > cost;

public:
	
	Graph();
	~Graph();
	bool OnCreate(std::vector< Node* > nodes_);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightedConnection(Node* fromNode, Node* toNode, float weight);
	std::vector <Node*> neighbours(Node* fromNode);
	std::vector <Node*> findPath(Node* startNode, Node* goalNode);
	
};




#endif