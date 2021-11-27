#pragma once

enum class NodeStatEnum
	{
		empty = 0,
		ocupied = 1,
		hit = 2
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

