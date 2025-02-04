#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
// #include <debug.h>

template <typename T> class Linked_list_item
{
  public:
    Linked_list_item(T* item);
    Linked_list_item();
    ~Linked_list_item();
    T* item;
    Linked_list_item* next;
};

template <typename T> Linked_list_item<T>::Linked_list_item(T* item)
{
    // dbg_printf("CREATED A NEW ITEM\n");
    this->item = item;
    this->next = nullptr;
}

template <typename T> Linked_list_item<T>::Linked_list_item()
{
    this->item = nullptr;
    this->next = nullptr;
}

template <typename T> Linked_list_item<T>::~Linked_list_item()
{
    if (next != nullptr)
    {
        delete next;
    }
}

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
    T** to_array();

  private:
    Linked_list_item<T>* first;
    Linked_list_item<T>* last;
    int list_size;
};

template <typename T> Linked_list<T>::Linked_list(T* item)
{
    this->first = new Linked_list_item<T>(item);
    this->last = first;
    this->list_size = 1;
}

template <typename T> Linked_list<T>::Linked_list()
{
    this->first = nullptr;
    this->last = nullptr;
    this->list_size = 0;
}

template <typename T> Linked_list<T>::~Linked_list()
{
    if (first != nullptr)
    {
        delete first;
    }
    // last does not have to be deleted, because it will be deleted when first
    // deletes the next etc.
}

template <typename T> void Linked_list<T>::add(T* t)
{
    // dbg_printf("IN LIST ADD\n");
    if (last == nullptr)
    {
        // dbg_printf("LAST IS NULLPTR\n");
        first = new Linked_list_item<T>(t);
        last = first;
        list_size++;
        return;
    }
    if (last->item == nullptr)
    {
        // dbg_printf("LAST ITEM IS NULLPT\n");
        last->item = t;
    }
    else
    {
        // dbg_printf("LAST ITEM IS FULL\n");
        last->next = new Linked_list_item<T>(t);
        last = last->next;
    }
    list_size++;
}

template <typename T> void Linked_list<T>::add(int index, T* t)
{
    if (index < 0)
    {
        return;
    }
    Linked_list_item<T>* list_item{first};

    // this is only true when we are adding at the beginning of the list
    if (index == 0)
    {
        first = new Linked_list_item<T>(t);
        first->next = list_item;
        list_size++;
        return;
    }

    if (first == nullptr)
    {
        first = new Linked_list_item<T>();
        list_item = first;
        list_size++;
    }

    while (index != 1)
    {
        // this was the last item in the list
        if (list_item->next == nullptr)
        {
            list_item->next = new Linked_list_item<T>();
            last = list_item->next;
            list_size++;
        }
        list_item = list_item->next;
        index--;
    }

    // the index is now 1, so the next item needs to become t
    if (list_item->next == nullptr)
    {
        list_item->next = new Linked_list_item<T>(t);
        last = list_item->next;
        list_size++;
    }
    else
    {
        Linked_list_item<T>* temp{list_item->next};
        list_item->next = new Linked_list_item<T>(t);
        list_item->next->next = temp;
        list_size++;
    }
}

template <typename T> void Linked_list<T>::add_all(Linked_list<T>* list)
{
    Linked_list_item<T>* list_item{list->first};
    for (int i = 0; i < list->list_size; i++)
    {
        if (last == nullptr)
        {
            first = new Linked_list_item<T>(list_item->item);
            last = first;
        }
        else
        {
            if (last->item == nullptr)
            {
                last->item = list_item->item;
            }
            else
            {
                last->next = new Linked_list_item<T>(list_item->item);
                last = last->next;
            }
        }
        list_size++;
        list_item = list_item->next;
    }
}

template <typename T> T* Linked_list<T>::get(int index)
{
    if (index < 0)
    {
        return nullptr;
    }
    Linked_list_item<T>* list_item{first};
    if (list_item == nullptr)
    {
        return nullptr;
    }

    if (index == 0)
    {
        return list_item->item;
    }
    while (list_item->next != nullptr)
    {
        index--;
        if (index == 0)
        {
            return list_item->next->item;
        }
        list_item = list_item->next;
    }
    return nullptr;
}

template <typename T> T* Linked_list<T>::remove(int index)
{
    if (index < 0)
    {
        return nullptr;
    }
    Linked_list_item<T>* list_item{first};
    if (list_item == nullptr)
    {
        return nullptr;
    }

    // this is only true when we are deleting the first item of the list
    if (index == 0)
    {
        if (list_item->next != nullptr)
        {
            first = list_item->next;
        }
        // The first is also the last item
        else
        {
            first = nullptr;
            last = nullptr;
        }
        T* temp = list_item->item;
        // set next to nullptr so it wont get deleted
        list_item->next = nullptr;
        delete list_item;
        // update the list size
        list_size--;
        return temp;
    }
    while (list_item->next != nullptr)
    {
        if (index == 1)
        {
            Linked_list_item<T>* new_next{list_item->next->next};
            T* temp = list_item->next->item;
            // set next next to nullptr so it wont get deleted
            list_item->next->next = nullptr;
            delete list_item->next;
            // update the list size
            list_size--;
            list_item->next = new_next;
            // if there is no new next item we deleted the last item
            if (new_next == nullptr)
            {
                last = list_item;
            }
            return temp;
        }
        index--;
        list_item = list_item->next;
    }
    return nullptr;
}

template <typename T> T* Linked_list<T>::remove(T* t)
{
    Linked_list_item<T>* list_item{first};
    if (list_item == nullptr)
    {
        return nullptr;
    }

    // this is only true when we are deleting the first item of the list
    if (list_item->item == t)
    {
        if (list_item->next != nullptr)
        {
            first = list_item->next;
        }
        // The first is also the last item
        else
        {
            first = nullptr;
            last = nullptr;
        }
        T* temp = list_item->item;
        // set next to nullptr so it wont get deleted
        list_item->next = nullptr;
        delete list_item;
        // update the list size
        list_size--;
        return temp;
    }

    while (list_item->next != nullptr)
    {
        if (list_item->next->item == t)
        {
            Linked_list_item<T>* new_next{list_item->next->next};
            T* temp = list_item->next->item;
            // set next next to nullptr so it wont get deleted
            list_item->next->next = nullptr;
            delete list_item->next;
            // update the list size
            list_size--;
            list_item->next = new_next;
            // if there is no new next item we deleted the last item
            if (new_next == nullptr)
            {
                last = list_item;
            }
            return temp;
        }
        list_item = list_item->next;
    }

    return nullptr;
}

template <typename T> int Linked_list<T>::size()
{
    return this->list_size;
}

/*returns an array containing all the elements of the list.*/
template <typename T> T** Linked_list<T>::to_array()
{
    T** array{new T*[list_size]};
    Linked_list_item<T>* list_item{first};
    int index{0};
    while (list_item->next != nullptr)
    {
        array[index] = list_item->item;
        list_item = list_item->next;
        index++;
    }
    array[index] = list_item->item;
    return array;
}

#endif
