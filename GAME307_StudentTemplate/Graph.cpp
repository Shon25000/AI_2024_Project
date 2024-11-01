#include "Graph.h"
#include <queue>


Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{

    int numNodes = nodes_.size();

    cost.resize(numNodes);
    for (int i = 0; i < numNodes; i++)
    {
        if (i != nodes_[i]->getLabel()) {

            std::cerr << "node with label 'i' not in the 'i' position for " << i << "\n";
            return false;

        }
        node[i] = nodes_[i];


        cost[i].resize(numNodes);

        for (int j = 0; j < numNodes; j++)
        {
            cost[i][j] = 0.0f;
        }
    }

    return true;
}

int Graph::numNodes()
{
    return node.size();
}

void Graph::addWeightedConnection(Node* fromNode, Node* toNode, float weight)
{
    cost[fromNode->getLabel()][toNode->getLabel()] = weight;
}

std::vector<Node*> Graph::neighbours(Node* fromNode)
{
    std::vector<Node*> result = {};
    int from = fromNode->getLabel();
    for (int j = 0; j < numNodes(); j++)
    {
        if (cost[from][j] > 0.0f) {
            result.push_back(getNode(j));
        }
    }
    return result;
}

struct NodeAndPariority
{
    Node* node;
    float priority;

    bool operator()(NodeAndPariority const& lhs, NodeAndPariority const& rhs)
    {
        return lhs.priority > rhs.priority;
    }
};

std::vector<Node*> Graph::findPath(Node* startNode, Node* goalNode)
{
    std::vector<Node*> result;

    float new_const;
    float priority;
    Node* currentNode = startNode;

    std::priority_queue<NodeAndPariority, std::deque<NodeAndPariority>, NodeAndPariority > frontier;
    frontier.push(NodeAndPariority{ currentNode, 0.0f });


    std::vector<int> came_from;

    came_from.resize(numNodes(), -1);


    int start = startNode->getLabel();
    int goal = goalNode->getLabel();

        std::map<int, float> cost_so_far;
        cost_so_far[start] = 0.0f;

        //loop through the frontier
        {
            //get top node, save it in current node
            //pop the top node
            //if its the goal, then break out

            // for the naighburs of current node
            {
                //caluculate new cost
                //if naighbur us bit index in cost_so_far or new_cost is lower
                {
                    //found a better path, so update
                }
            }

        }

    return result;
}
