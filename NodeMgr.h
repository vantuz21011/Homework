#pragma once
#include "Adapter.h"


template<typename T>
class NodeMgr
{
public:
    using ListNode = Adapter <T>;

    NodeMgr();
    NodeMgr& operator =(NodeMgr const &) = delete;
    NodeMgr(NodeMgr const &) = delete;
	~NodeMgr();
    void push(T* p);
    T* popBack();
    T* getHead() const;
    T* getTail() const;
    T* pop();
    void pushBack(T* p);
    T* search(int n) const;
    bool insert(int n, T* p);
    T* remove(int n);
    void print() const;
    void printReverse() const;

private:
    ListNode* getHead_inner() const;
    ListNode* getTail_inner() const;
    ListNode* search_inner(int n) const;

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
};

#include "NodeMgr.impl"
