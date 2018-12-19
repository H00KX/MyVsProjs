#pragma once

#define T_LIST



//回文序列 abcdcba


class CMyList
{

//private:
public:
    struct CMyNode
    {
        CMyNode(T_LIST int data)
        {
            m_data = data;
            m_pNext = nullptr;
            m_pPre = nullptr;
        }

        CMyNode* m_pNext;
        CMyNode* m_pPre;
        T_LIST int m_data;
    };

public:
    CMyList();
    ~CMyList();

    //Adds an element to the end of a list
    void push_back(const T_LIST int& n);
    //Adds an element to the beginning of a list
    void push_front(const T_LIST int& n);

    //Deletes the element at the beginning of a list.
    void pop_front();
    //Deletes the element at the end of a list
    void pop_back();

    //Inserts an element or a number of elements or a range of elements into a list at a specified position
    //iterator insert(iterator position, const value_type& val);
    //Removes an element or a range of elements in a list from specified positions
    //iterator erase(iterator position);

    //Returns a reference to the first element in a list.
    CMyNode& front();
    //Returns a reference to the last element of a list
    CMyNode& back();

    //Returns an iterator addressing the first element in a list
    //iterator begin();
    //Returns an iterator that addresses the location succeeding the last element in a list
    //iterator end();

    //Tests if a list is empty
    bool empty() const;
    //Returns the number of elements in a list.
    size_t size() const;
    //Reverses the order in which the elements occur in a list.
    //void reverse();



//private:
public:
    CMyNode* m_pHead; //表示头结点
    int m_nSize;
};

