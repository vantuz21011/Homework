#pragma once

template<typename T>
struct Adapter
{
    T* obj = nullptr;
    Adapter* next = nullptr;
    Adapter* prev = nullptr;
};
