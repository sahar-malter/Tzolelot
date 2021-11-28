#pragma once

enum class NodeStatEnum
	{
		empty = 0,
		ocupied = 1,
		unplacable = 2,
		hit = 3
	};

class Node
{
public:
	Node();
	int X;
	int Y;
	NodeStatEnum nodeStatEnum;
	void clear();
};

