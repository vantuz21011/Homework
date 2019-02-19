#include "Node.h"

int Node::count = 0;

int Node::getCount()
{
    return count;
}

Node::Node()
:data(0)
{
    ++Node::count;
}

Node::Node(int d)
:data (d)
{
    ++count;
}

Node::~Node()
{
	--count;
}
