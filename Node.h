#pragma once

struct Node
{
    int data = 0;
    static int getCount();
    Node();
    Node(int d);
    ~Node();
    
private:
    Node(Node const &) = delete;
    Node& operator = (Node const &)= delete;
    static int count;
};
