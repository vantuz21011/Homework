#include <iostream>
#include <memory>

struct Node
{
	Node* prev = nullptr;
	int data = 0;
	Node* next = nullptr;
	static int getCount()
	{
		return count;
	}
	Node() :
			prev(nullptr), data(0), next(nullptr)
	{
		++Node::count;
	}
	Node(int d) :
			prev(nullptr), data(d), next(nullptr)
	{
		++count;
	}
	~Node()
	{
		--count;
	}
private:
	Node(Node const &) = delete;
	Node& operator =(Node const &) = delete;
private:
	static int count;
};

int Node::count = 0;

class NodeMgr
{
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	NodeMgr() = default;
	NodeMgr& operator =(NodeMgr const &) = delete;
	NodeMgr(NodeMgr const &) = delete;
	~NodeMgr();
	void push(Node* p);
	Node* popBack();
	Node* getHead()
	{
		return head;
	}
	Node* getTail()
	{
		return tail;
	}
	Node* pop();
	void pushBack(Node* p);
	Node* search(int n);
	bool insert(int n, Node* p);
	Node* remove(int n);
};

Node* NodeMgr::search(int n)
{
	if (n >= 0)
	{
		Node* node = getHead();
		int count = 0;
		while (node != nullptr && count != n)
		{
			node = node->next;
			count++;
		}
		return node;
	}
	else
	{
		Node* node = getTail();
		int count = -1;
		while (node != nullptr && count != n)
		{
			node = node->prev;
			count--;
		}
		return node;
	}

}

void NodeMgr::push(Node* p)
{
	if (p == nullptr)
	{
		return;
	}

	if (head == nullptr)
	{
		tail = head = p;
	}
	else
	{
		p->next = head;
		head = p;
	}
}

void NodeMgr::pushBack(Node* p)
{
	if (p == nullptr)
	{
		return;
	}

	if (tail == nullptr)
	{
		tail = head = p;
	}
	else
	{
		tail->next = p;
		p->prev = tail;
		tail = p;

	}
}

bool NodeMgr::insert(int n, Node* p)
{
	if (n >= 0)
	{
		Node* node = search(n);
		if (node == nullptr)
		{
			return false;
		}

		p->next = node->next;
		node->next = p;
		p->prev = node;

		if (tail == node)
		{
			tail = p;
		}
		else
		{
			p->next->prev = p;
		}
		return true;
	}
	else
	{
		return false;
	}
}


Node* NodeMgr::remove(int n)
{
if (n == 0)
{
	return pop();
}
Node* node = search(n - 1);
if (node == nullptr)
{
	return nullptr;
}
Node* toDel = node->next;
if (toDel == nullptr)
{
	return nullptr;
}
node->next = toDel->next;
if (toDel->next == nullptr)
{
	tail = node;
}
return toDel;
if (n < 0)
{
	return popBack();
}
}

Node* NodeMgr::pop()
{
if (head == nullptr)
{
	return nullptr;
}
if (head == tail)
{
	Node* node = head;
	head = tail = nullptr;
	return node;
}
Node* node = head;
head = head->next;

return node;
}

NodeMgr::~NodeMgr()
{
Node* node = pop();
while (node != nullptr)
{
	delete node;
	node = pop();
}
}

int main()
{
std::cout << Node::getCount() << std::endl;

NodeMgr mgr;

int nodeData = 0;

mgr.pushBack(new Node(nodeData++));

mgr.push(new Node(nodeData++));
mgr.push(new Node(nodeData++));

std::cout << Node::getCount() << std::endl;

std::unique_ptr<Node> n1(new Node(nodeData++));

std::cout << Node::getCount() << std::endl;

bool rezult = mgr.insert(100, n1.get());

if (rezult == true)
{
	n1.release();
}
else
{
	n1.reset(new Node());
}
rezult = mgr.insert(1, n1.get());
std::cout << Node::getCount() << std::endl;

if (rezult == true)
{
	n1.release();
}
else
{
	n1.reset();
}

std::cout << Node::getCount() << std::endl;

std::unique_ptr<Node> n2(mgr.remove(2));
std::unique_ptr<Node> n3(mgr.pop());
std::cout << Node::getCount() << std::endl;
n2.reset();
n3.reset();
std::cout << Node::getCount() << std::endl;
return 0;
}
