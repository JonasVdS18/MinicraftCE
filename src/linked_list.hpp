#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T> class Linked_list
{
  public:
    Linked_list(T* item);
    Linked_list();
    ~Linked_list();
    void add(T* t);
    void add(int index, T* t);
    T* get(int index);
    void remove(int index);
    void remove(T* t);
    int size();

  private:
    T* item;
    Linked_list* next;
};

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

template <typename T> Linked_list<T>::~Linked_list()
{
    /*
    if (next != nullptr) {
      delete next;
    }
    if (item != nullptr) {
      delete item;
    }
    */
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

template <typename T> void Linked_list<T>::add(int index, T* t)
{
    if (index == 0)
    {
        if (next != nullptr)
        {
            T* temp = item;
            item = t;
            next->add(0, t);
        }
        else // end of the list.
        {
            T* temp = item;
            item = t;
            if (item != nullptr)
            {
                next = new Linked_list(temp);
            }
        }
    }
    else
    {
        if (next == nullptr)
        {
            next = new Linked_list();
        }
        next->add(index - 1, t);
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
            Linked_list<T>* temp{next};
            next = next->next;
            temp->remove(index);
            // Shorten the list when a part is empty.
            if (temp->next == nullptr && temp->item == nullptr)
            {
                delete temp;
            }
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
            Linked_list<T>* temp{next};
            next = next->next;
            temp->remove(0);
            // Shorten the list when a part is empty.
            if (temp->next == nullptr && temp->item == nullptr)
            {
                delete temp;
            }
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

#endif
