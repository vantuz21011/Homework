#include <iostream>
#include <memory>
#include "NodeMgr.h"
#include "Adapter.h"
#include "Node.h"
#include "Node3.h"


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
