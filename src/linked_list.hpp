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
    void add_all(Linked_list<T>* list);
    T* get(int index);
    T* remove(int index);
    T* remove(T* t);
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

template <typename T> void Linked_list<T>::add_all(Linked_list<T>* list)
{
    if (list == nullptr)
    {
        return;
    }

    if (next == nullptr)
    {
        if (item == nullptr)
        {
            item = list->item;
            if (list->next != nullptr)
            {
                next = new Linked_list();
                next->add_all(list->next);
            }
        }
        else
        {
            next = new Linked_list();
            next->add_all(list);
        }
    }
    else
    {
        next->add_all(list);
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

template <typename T> T* Linked_list<T>::remove(int index)
{

    if (index < 0)
    {
        return nullptr;
    }

    if (index == 0) // if this item needs to be removed.
    {
        if (next != nullptr) // if there is a next list entry
        {
            // remove the item by overriding it with the next, this shifts the list to
            // the front
            T* temp{item};
            item = next->item;
            if (next->next != nullptr)
            {
                next->remove(0);
                return temp;
            }
            else // if the next item is the last in the list, remove it because we
                 // dont need it anymore.
            {
                delete next;
                next = nullptr;
                return temp;
            }
        }
        else // if this is the only item in the list (we know it is the only item
             // in the list because it doesnt have a next one but it is also the
             // last because it would have been deleted).
        {
            // create an empty list entry.
            T* temp{item};
            item = nullptr;
            return temp;
        }
    }
    else // if this item does not need to be removed.
    {
        // if the next item is the item that is going to be removed.
        if (index - 1 == 0)
        {
            // if the next item exists.
            if (next != nullptr)
            {
                // save the item in temp to return later
                T* temp = next->item;

                // if the next item is the last item in the list but not the first (we
                // know it is not the first because then index would have been 0).
                if (next->next == nullptr)
                {
                    // delete the next entry to shorten the list.
                    delete next;
                    next = nullptr;
                }
                else
                {
                    // remove the next item.
                    next->remove(0);
                }
                // return the removed item.
                return temp;
            }
            else
            {
                return nullptr;
            }
        }
        else // if the next item does not need to be removed.
        {
            if (next != nullptr) // if the next item exists.
            {
                return next->remove(index - 1);
            }
            else
            {
                return nullptr;
            }
        }
    }
}

template <typename T> T* Linked_list<T>::remove(T* t)
{
    if (item == t) // if we need to remove this item.
    {
        // remove the item using the normal remove function.
        remove(0);
        return t;
    }
    else // if this item does not need to be removed.
    {
        if (next != nullptr) // try to remove it from the remaining list.
        {
            return next->remove(t);
        }
        else // if the item is not in the list.
        {
            return nullptr;
        }
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
