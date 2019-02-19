#include <iostream>
#include <memory>
#include "NodeMgr.h"
#include "Node.h"

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
