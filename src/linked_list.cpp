#include "linked_list.hpp"

template <typename T> Linked_list<T>::Linked_list(T* item)
{
    this->item = item;
    this->next = nullptr;
}

template <typename T> Linked_list<T>::Linked_list()
{
    this->item = nullptr;
    this->next = nullptr;
}

template <typename T> void Linked_list<T>::add(T* t)
{
    if (next == nullptr)
    {
        if (item == nullptr)
        {
            item = t;
        }
        else
        {
            next = new Linked_list(t);
        }
    }
    else
    {
        next->add(t);
    }
}

template <typename T> T* Linked_list<T>::get(int index)
{
    if (index == 0)
    {
        return item;
    }
    else
    {
        if (next != nullptr)
        {
            return next->get(index - 1);
        }
        else
        {
            return nullptr;
        }
    }
}

template <typename T> void Linked_list<T>::remove(int index)
{
    if (index < 0)
    {
        return;
    }

    if (index == 0)
    {
        if (next != nullptr)
        {
            item = next->item;
            next->remove(index);
            next = next->next;
        }
        // We reached the end.
        else
        {
            item = nullptr;
        }
    }
    else
    {
        return next->remove(index - 1);
    }
}

template <typename T> void Linked_list<T>::remove(T* t)
{
    if (item == t)
    {
        if (next != nullptr)
        {
            item = next->item;
            next->remove(0);
            next = next->next;
        }
        // We reached the end.
        else
        {
            item = nullptr;
        }
    }
    else
    {
        return next->remove(t);
    }
}

template <typename T> int Linked_list<T>::size()
{
    if (next != nullptr)
    {
        return 1 + next->size();
    }
    else
    {
        if (item == nullptr)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*
template <typename T> List<T>::List()
{
    this->item = NULL;
    this->next = NULL;
}

template <typename T> void List<T>::add(T* t)
{
    size++;
    if (next = NULL)
    {
        if (item == NULL)
        {
            item = t;
        }
        else
        {
            next = new Linked_list(t);
        }
    }
    else
    {
        next->add(t);
    }
}

template <typename T> T List<T>::get(int index)
{
    if (index == 0)
    {
        return item;
    }
    else
    {
        return next->get(index - 1)
    }
}

*/
