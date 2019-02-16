#include <iostream>
#include <memory>
#include "NodeMgr.h"
#include "Adapter.h"
#include "Node.h"
#include "Node3.h"

template <typename T>
NodeMgr<T>::NodeMgr() = default;

template <typename T>
NodeMgr<T>::~NodeMgr()
{
    T* node = pop();
    while (node != nullptr)
    {
        delete node;
        node = pop();
    }
}

template <typename T>
void NodeMgr<T>::push(T* p)
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

template <typename T>
T* NodeMgr<T>::popBack()
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

template <typename T>
T* NodeMgr<T>::getHead() const
{
    return getHead_inner()->obj;
}

template <typename T>
T* NodeMgr<T>::getTail() const
{
    return getTail_inner()->obj;
}

template <typename T>
T* NodeMgr<T>::pop()
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

template <typename T>
void NodeMgr<T>::pushBack(T* p)
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

template <typename T>
T* NodeMgr<T>::search(int n) const
{
    auto* node_inner = search_inner(n);
    if (node_inner == nullptr)
    {
        return nullptr;
    }
    return node_inner->obj;
}

template <typename T>
bool NodeMgr<T>::insert(int n, T* p)
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

template <typename T>
T* NodeMgr<T>::remove(int n)
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

template <typename T>
void NodeMgr<T>::print() const
{
    auto const* inner_node = getHead_inner();

    while (inner_node != nullptr)
    {
        std::cout << inner_node->obj->data << ',';

        inner_node = inner_node->next;
    }

    std::cout << std::endl;
}

template <typename T>
void NodeMgr<T>::printReverse() const
{
    auto const* inner_node = getTail_inner();

    while (inner_node != nullptr)
    {
        std::cout << inner_node->obj->data << ',';

        inner_node = inner_node->prev;
    }

    std::cout << std::endl;
}

template <typename T>
typename NodeMgr<T>::ListNode* NodeMgr<T>::getHead_inner() const
{
    return head;
}

template <typename T>
typename NodeMgr<T>::ListNode* NodeMgr<T>::getTail_inner() const
{
    return tail;
}

template <typename T>
typename NodeMgr<T>::ListNode* NodeMgr<T>::search_inner(int n) const
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
