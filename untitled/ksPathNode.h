#ifndef KS_PATH_NODE_H
#define KS_PATH_NODE_H

struct ksPathNode
{
	int move_cost;
	int heuristic;
	int total;

	ksPathNode * parent;
	ksPathNode * up;
	ksPathNode * down;
	ksPathNode * left;
	ksPathNode * right;
};

#endif