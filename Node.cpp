#include "Node.h"

Node::Node()
{
	X = 0;
	Y = 0;
	nodeStatEnum = NodeStatEnum::empty;
}

void Node::clear()
{
	X = 0;
	Y = 0;
	nodeStatEnum = NodeStatEnum::empty;
}
