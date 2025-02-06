#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <stdint.h>

const uint8_t MAX_CAPACITY{255};

// Resizeable array
// max size is 256
template <typename T> class Arraylist
{
  public:
    Arraylist();
    // Creates an ArrayList with a given initial capacity to store elements
    Arraylist(uint8_t initial_capacity);
    ~Arraylist();
    bool add(T* t);
    // Returns the element at the index if 0 <= index < size
    T* get(uint8_t index);
    uint8_t size();
    // Removes the entity at the index and shifts the other entities
    T* remove_index(uint8_t index);
    // Removes the first occurance of the Entity
    bool remove_element(T* t);
    // Clears the arraylist/makes it empty
    void clear();
    bool add_all(Arraylist* arraylist);

  private:
    T** head;
    // The amount non-NULL elements in the array
    uint8_t array_size;
    // The maximum amount of non-NULL elements in the array before it needs to be
    // resized
    uint8_t capacity;
    // Expands the array if possible
    void reallocate();
};

template <typename T> Arraylist<T>::Arraylist() : head{new T*[1]}, array_size{0}, capacity{1}
{
}

template <typename T>
Arraylist<T>::Arraylist(uint8_t initial_capacity)
    : head{new T*[initial_capacity]}, array_size{0}, capacity{initial_capacity}
{
}

template <typename T> Arraylist<T>::~Arraylist()
{
    delete[] head;
}

template <typename T> bool Arraylist<T>::add(T* t)
{
    if (array_size <= capacity - 1)
    {
        head[array_size] = t;
        array_size++;
        return true;
    }
    else if (array_size <= MAX_CAPACITY - 1)
    {
        reallocate();
        head[array_size] = t;
        array_size++;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T> void Arraylist<T>::reallocate()
{
    // We double the capacity if we can
    if (capacity <= MAX_CAPACITY / 2)
    {
        capacity *= 2;
        // Create new array
        T** new_head = new T*[capacity];
        // copy old array to new array
        for (uint8_t i = 0; i < array_size; i++)
        {
            new_head[i] = head[i];
        }
        delete[] head;
        head = new_head;
    }
    // If doubling the array is to much we increase it to the maximum capacty if
    // it isnt already the max capacity
    else if (capacity != MAX_CAPACITY)
    {
        capacity = MAX_CAPACITY;
        // Create new array
        T** new_head = new T*[capacity];
        // copy old array to new array
        for (uint8_t i = 0; i < array_size; i++)
        {
            new_head[i] = head[i];
        }
        delete[] head;
        head = new_head;
    }
}

template <typename T> T* Arraylist<T>::get(uint8_t index)
{
    return (index >= 0 && index < array_size) ? head[index] : nullptr;
}

template <typename T> uint8_t Arraylist<T>::size()
{
    return array_size;
}

template <typename T> T* Arraylist<T>::remove_index(uint8_t index)
{
    if (index < 0 || index >= array_size)
    {
        return nullptr;
    }

    T* temp = head[index];
    for (uint8_t i = index; i < array_size - 1; i++)
    {
        head[i] = head[i + 1];
    }
    head[array_size - 1] = nullptr;
    array_size--;
    return temp;
}

template <typename T> bool Arraylist<T>::remove_element(T* t)
{
    bool removed{false};
    for (uint8_t i = 0; i < array_size; i++)
    {
        // If this element is the given element
        if (!removed && head[i] == t)
        {
            removed = true;
            head[i] = head[i + 1];
        }
        // If we have found the element we can start shifting the elements
        else if (removed && i < array_size - 1)
        {
            head[i] = head[i + 1];
        }
        // The last element will become a nullptr
        else if (removed)
        {
            head[i] = nullptr;
        }
    }
    // if we removed an item we have to reduce the array size, we cant do this in
    // the loop because it needs the original size
    if (removed)
        array_size--;

    return removed;
}

template <typename T> void Arraylist<T>::clear()
{
    for (uint8_t i = 0; i < array_size; i++)
    {
        head[i] = nullptr;
    }
    array_size = 0;
}

template <typename T> bool Arraylist<T>::add_all(Arraylist* arraylist)
{
    // If the array will overflow we will not add it
    if (array_size + arraylist->size() > MAX_CAPACITY)
    {
        return false;
    }
    // Create extra capacity until we can store the new array
    while (array_size + arraylist->size() > capacity)
    {
        reallocate();
    }

    for (uint8_t i = array_size; i < array_size + arraylist->size(); i++)
    {
        head[i] = arraylist->get(i - array_size);
    }
    array_size += arraylist->size();
    return true;
}

#endif
