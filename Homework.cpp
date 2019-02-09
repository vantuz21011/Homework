#include <iostream>
#include <memory>

struct Node
{
//    Node* prev = nullptr;
    int data = 0;
//    Node* next = nullptr;
    static int getCount()
    {
        return count;
    }
    Node()
//    : prev(nullptr), data(0), next(nullptr)
            : data(0)
    {
        ++Node::count;
    }
    Node(int d)
//    : prev(nullptr), data(d), next(nullptr)
            : data(d)
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

struct Node3
{
    long long data = 0;
};

template<typename T>
struct Adapter
{
    T* obj = nullptr;
    Adapter* next = nullptr;
    Adapter* prev = nullptr;
};

template<typename T>
class NodeMgr
{
    using ListNode = Adapter <T>;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

public:
    NodeMgr() = default;
    NodeMgr& operator =(NodeMgr const &) = delete;
    NodeMgr(NodeMgr const &) = delete;
    ~NodeMgr()
    {
        T* node = pop();
        while (node != nullptr)
        {
            delete node;
            node = pop();
        }
    }

    void push(T* p)
    {
        if (p == nullptr)
        {
            return;
        }

        auto* a = new ListNode;
        a->obj = p;

        if (head == nullptr)
        {
            head = tail = a;
        }
        else
        {
            a->next = head;
            head->prev = a;
            head = a;
        }
    }

    T* popBack()
    {
        if (tail == nullptr)
        {
            return nullptr;
        }

        if (tail == head)
        {
            return pop();
        }

        auto* node = tail->obj;
        ListNode* newtail = tail->prev;
        delete tail;
        tail = newtail;
        tail->next = nullptr;
        return node;
    }

    T* getHead() const
    {
        return getHead_inner()->obj;
    }

    T* getTail() const
    {
        return getTail_inner()->obj;
    }

    T* pop()
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        if (head == tail)
        {
            auto* node = head->obj;
            delete head;
            head = tail = nullptr;
            return node;
        }

        auto* node = head->obj;
        ListNode* newhead = head->next;
        delete head;
        head = newhead;
        head->prev = nullptr;
        return node;
    }

    void pushBack(T* p)
    {
        if (p == nullptr)
        {
            return;
        }

        auto* a = new ListNode;
        a->obj = p;

        if (tail == nullptr)
        {
            tail = head = a;
        }
        else
        {
            a->next = nullptr;
            a->prev = tail;
            tail = a;
        }
    }

    T* search(int n) const
    {
        auto* node_inner = search_inner(n);
        if (node_inner == nullptr)
        {
            return nullptr;
        }
        return node_inner->obj;
    }

    bool insert(int n, T* p)
    {
        if (n >= 0)
        {
            auto* inner_node = search_inner(n);
            if (inner_node == nullptr)
            {
                return false;
            }
            auto* a = new ListNode;
            a->obj = p;
            a->next = inner_node->next;
            inner_node->next = a;
            a->prev = inner_node;

            if (tail == inner_node)
            {
                tail = a;
            }
            else
            {
                a->next->prev = a;
            }
            return true;
        }
        else
        {
            auto* inner_node = search_inner(n);
            if (inner_node == nullptr)
            {
                return false;
            }
            auto* a = new ListNode;
            a->obj = p;
            a->next = inner_node;
            a->prev = inner_node->prev;
            inner_node->prev = a;

            if (head == inner_node)
            {
                head = a;
            }
            else
            {
                a->prev->next = a;
            }

            return true;
        }
    }

    T* remove(int n)
    {
        if (n == 0)
        {
            return pop();
        }

        if (n == -1)
        {
            return popBack();
        }

        auto* inner_node = search_inner(n);
        if (inner_node == nullptr)
        {
            return nullptr;
        }

        if (inner_node == head)
        {
            return remove(0);
        }
        else if (inner_node == tail)
        {
            return remove(-1);
        }
        else
        {
            inner_node->prev->next = inner_node->next;
            inner_node->next->prev = inner_node->prev;
            return inner_node->obj;
        }
    }

    void print() const
    {
        auto const* inner_node = getHead_inner();

        while (inner_node != nullptr)
        {
            std::cout << inner_node->obj->data << ',';

            inner_node = inner_node->next;
        }

        std::cout << std::endl;
    }

    void printReverse() const
    {
        auto const* inner_node = getTail_inner();

        while (inner_node != nullptr)
        {
            std::cout << inner_node->obj->data << ',';

            inner_node = inner_node->prev;
        }

        std::cout << std::endl;
    }

private:
    ListNode* getHead_inner() const
    {
        return head;
    }

    ListNode* getTail_inner() const
    {
        return tail;
    }

    ListNode* search_inner(int n) const
    {
        if (n >= 0)
        {
            auto* inner_node = getHead_inner();
            int count = 0;
            while (inner_node != nullptr && count != n)
            {
                inner_node = inner_node->next;
                count++;
            }
            return inner_node;
        }
        else
        {
            auto* inner_node = getTail_inner();
            int count = -1;
            while (inner_node != nullptr && count != n)
            {
                inner_node = inner_node->prev;
                count--;
            }
            return inner_node;
        }
    }
};

int main()
{
    std::cout << Node::getCount() << std::endl;

    NodeMgr<Node> mgr;
    mgr.print();
    mgr.printReverse();

    int nodeData = 0;

    mgr.pushBack(new Node(nodeData++));
    mgr.print();
    mgr.printReverse();

    mgr.push(new Node(nodeData++));
    mgr.print();
    mgr.printReverse();

    mgr.push(new Node(nodeData++));
    mgr.print();
    mgr.printReverse();

    std::cout << Node::getCount() << std::endl;

    std::unique_ptr<Node> n1(new Node(nodeData++));

    std::cout << Node::getCount() << std::endl;

    bool rezult = mgr.insert(100, n1.get());
    mgr.print();
    mgr.printReverse();

    if (rezult == true)
    {
        n1.release();
        n1.reset(new Node(nodeData++));
    }

    std::cout << Node::getCount() << std::endl;

    std::unique_ptr<Node> n2(mgr.remove(2));
    mgr.print();
    mgr.printReverse();

    std::unique_ptr<Node> n3(mgr.pop());
    mgr.print();
    mgr.printReverse();

    std::unique_ptr<Node> n4(mgr.popBack());
    mgr.print();
    mgr.printReverse();

    std::cout << Node::getCount() << std::endl;
    n2.reset();
    n3.reset();
    std::cout << Node::getCount() << std::endl;

    return 0;
}
