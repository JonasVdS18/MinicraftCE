#ifndef LIST_HPP
#define LIST_HPP

template <typename T> class Linked_list
{
  public:
    Linked_list(T* item);
    Linked_list();
    void add(T* t);
    T* get(int index);
    void remove(int index);
    void remove(T* t);
    int size();

  private:
    T* item;
    Linked_list* next;
};
/*
template <typename T> class List
{
  public:
    T* item;
    Linked_list* next;
    List();

    void add(T* t);
    T get(int index);
    void remove(int index);
    int size();

  private:
    int length;
};*/
#endif
