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
    Node()
            : prev(nullptr), data(0), next(nullptr)
    {
        ++Node::count;
    }
    Node(int d)
            : prev(nullptr), data(d), next(nullptr)
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

template <typename T>
class NodeMgr
{
    T* head = nullptr;
    T* tail = nullptr;
public:
    NodeMgr() = default;
    NodeMgr& operator =(NodeMgr const &) = delete;
    NodeMgr(NodeMgr const &) = delete;
    ~NodeMgr();
    void push(T* p);
    T* popBack();

    T* getHead() const
    {
        return head;
    }

    T* getTail() const
    {
        return tail;
    }

    T* pop();
    void pushBack(T* p);
    T* search(int n) const;
    bool insert(int n, T* p);
    T* remove(int n);

    void print() const;
};

template <typename T>
void NodeMgr::print() const
{
    T* node = getHead();
    while (node != nullptr)
    {
        std::cout << node->data << ',';
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
T* NodeMgr::search(int n) const
{
    if (n >= 0)
    {
        T* node = getHead();
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
        T* node = getTail();
        int count = -1;
        while (node != nullptr && count != n)
        {
            node = node->prev;
            count--;
        }
        return node;
    }

}

template <typename T>
void NodeMgr::push(T* p)
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

template <typename T>
void NodeMgr::pushBack(T* p)
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

template <typename T>
bool NodeMgr::insert(int n, T* p)
{
    if (n >= 0)
    {
        T* node = search(n);
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
        T* node = search(n);
        if (node == nullptr)
        {
            return false;
        }

        p->next = node;
        p->prev = node->prev;
        node->prev = p;

        if (head == node)
        {
            head = p;
        }
        else
        {
            p->prev->next = p;
        }
        return true;
    }
}

template <typename T>
T* NodeMgr::remove(int n)
{
    if (n == 0)
    {
        return pop();
    }

    if (n == -1)
    {
        return popBack();
    }

    T* node = search(n);
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node == head)
    {
        return remove(0);
    }
    else if (node == tail)
    {
        return remove(-1);
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        return node;
    }
}

template <typename T>
T* NodeMgr::pop()
{
    if (head == nullptr)
    {
        return nullptr;
    }

    if (head == tail)
    {
        T* node = head;
        head = tail = nullptr;
        return node;
    }

    T* node = head;
    head = head->next;
    head->prev = nullptr;

    return node;
}

template <typename T>
T* NodeMgr::popBack()
{
    if (tail == nullptr)
    {
        return nullptr;
    }

    if (tail == head)
    {
        return pop();
    }

    T* node = tail;
    tail = tail->prev;
    tail->next = nullptr;

    return node;
}

template <typename T>
NodeMgr::~NodeMgr()
{
    T* node = pop();
    while (node != nullptr)
    {
        delete node;
        node = pop();
    }
}

int main()
{
    std::cout << Node::getCount() << std::endl;

    NodeMgr <Node> mgr;

    int nodeData = 0;

    mgr.pushBack(new Node(nodeData++));

    mgr.push(new Node(nodeData++));
    mgr.push(new Node(nodeData++));

    std::cout << Node::getCount() << std::endl;

    std::unique_ptr<Node> n1(new Node(nodeData++));

    std::cout << Node::getCount() << std::endl;

    mgr.print();
    bool rezult = mgr.insert(100, n1.get());
    mgr.print();

    if (rezult == true)
    {
        n1.release();
        n1.reset(new Node(nodeData++));
    }

    mgr.print();
    rezult = mgr.insert(1, n1.get());
    mgr.print();
    std::cout << Node::getCount() << std::endl;

    if (rezult == true)
    {
        n1.release();
    }

    std::cout << Node::getCount() << std::endl;

    std::unique_ptr<Node> n2(mgr.remove(2));
    std::unique_ptr<Node> n3(mgr.pop());

    std::unique_ptr <Node> n4(mgr.popBack());

    std::cout << Node::getCount() << std::endl;
    n2.reset();
    n3.reset();
    std::cout << Node::getCount() << std::endl;

    return 0;
}
