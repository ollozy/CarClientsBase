#ifndef LINK_LIST
#define LINK_LIST

#include "global.h"

template<typename T> class LinkList;
template<typename Node> class ListIterator;

template<typename T>
class node
{
public:
    using Value = T;

    node() : m_data(nullptr), m_next(this) {}
    node(Value *data, node *next, node *prev)
        : m_data(data)
        , m_next(next)
        , m_previous(prev) {}

    ~node() { if(m_data) delete m_data; m_data = nullptr; }

    node *previous() const { return m_previous; }
    void setPrevious(node *prev) { m_previous = prev; }

    node *next() const { return m_next; }
    void setNext(node *next) { m_next = next; }

    Value *data() { return m_data; }
    void setData(Value *data) { m_data = data; }

private:
    node *m_next;
    node *m_previous;
    Value *m_data;
};

template<typename Node>
class ListIterator
{
    using Value = typename Node::Value;
public:

    explicit ListIterator(Node* node = nullptr) : m_ptr(node) {}
    ListIterator(const ListIterator &other) { m_ptr = other.m_ptr; }

    ListIterator &operator=(const ListIterator &other)
    {
        if(this == &other)
            return *this;

        m_ptr = other.m_ptr;
        return *this;
    }
    Value& operator*() { return *m_ptr->data(); }
    const Value &operator*() const { return *m_ptr->data(); }
    Value *operator->() { return m_ptr->data(); }
    bool operator==(const ListIterator &rightIter) const { return m_ptr == rightIter.m_ptr; }
    bool operator!=(const ListIterator &rightIter) const { return m_ptr != rightIter.m_ptr; }
    bool operator!() const { return m_ptr == nullptr; }
    operator Value () { return *m_ptr->data(); }
    ListIterator operator++(int)
    {
        if (m_ptr == nullptr) return *this;

        ListIterator temp = *this;
        ++(*this);
        return temp;
    }
    ListIterator operator++()
    {
        if (m_ptr == nullptr) return *this;
        m_ptr = m_ptr->next();
        return *this;
    }
    ListIterator operator--(int)
    {
        if (m_ptr == nullptr) return *this;

        ListIterator temp = *this;
        --(*this);
        return temp;
    }
    ListIterator operator--()
    {
        if (m_ptr == nullptr) return *this;
        m_ptr = m_ptr->previous();
        return *this;
    }

    bool isValid() const { return m_ptr->data() != nullptr; }

    Node *__getNode() const { return m_ptr; }

private:
    Node *m_ptr;
};

template<typename T> 
class LinkList
{
    typedef node<T> Node;

public:
    typedef ListIterator<Node> iterator;

    LinkList() : m_end(m_begin), m_begin(new Node(new T(), nullptr, nullptr)), m_size(0) {}
    LinkList(const LinkList<T>& li)
    {
        for(LinkList<T>::iterator iter = li.begin(); iter != li.end(); ++iter)
            append(*iter);
    }
    ~LinkList()
    {
        clear();
        delete m_begin;
    }

    int size() const { return m_size; }
    bool isEmpty() const { return m_begin == m_end; }
    iterator begin() const { return iterator(m_begin); }
    iterator end() const { return iterator(m_end);}

    LinkList<T>& operator=(const LinkList<T>& li)
    {
        if (this == &li)
            return *this;

        clear();

        for(LinkList<T>::iterator it = li.begin(); it != li.end(); ++it)
            append(*it);

        return *this;
    }
    T& operator[](int i)
    {
        assert(i < m_size);
        if(!(i < m_size))
            return *m_end->data();
        Node *pNode = m_begin;
        for(int j = 0; i != j; ++j)
            pNode = pNode->next();
        return *pNode->data();
    }
    const T& operator[](int i) const
    {
        assert(i < m_size);
        if(!(i < m_size))
            return *m_end->data();
        Node *pNode = m_begin;
        for(int j = 0; i != j; ++j)
            pNode = pNode->next();
        return *pNode->data();
    }

    bool contains(const T &val) const
    {
        for(LinkList<T>::iterator it = begin(); it != end(); ++it)
            if(*it == val)
                return true;
        return false;
    }
    void append(const T &val)
    {
        if(isEmpty()) {
            *m_begin->data() = val;
            m_end = new Node(new T(), nullptr, m_begin);
            m_begin->setNext(m_end);
        }
        else {
            *m_end->data() = val;
            Node *newEnd = new Node(new T(), nullptr, m_end);
            m_end->setNext(newEnd);
            m_end = newEnd;
        }
        ++m_size;
    }
    void prepend(const T &val)
    {
        if(isEmpty()) {
            append(val);
            return;
        }
        else {
            Node *newBegin = new Node(new T(val), m_begin, nullptr);
            m_begin->setPrevious(newBegin);
            m_begin = newBegin;
        }
        ++m_size;
    }

    iterator insert(const T& val, iterator before)
    {
        assert(before.__getNode());
        if(!before.__getNode())
            return iterator();
        else if(before.__getNode() == m_begin) {
            prepend(val);
            return iterator(m_begin);
        }
        else if(before.__getNode() == m_end) {
            append(val);
            return iterator(m_end->previous());
        }
        Node *next = before.__getNode();
        Node *prev = next->previous();
        Node *newNode = new Node(new T(val), next, prev);
        next->setPrevious(newNode);
        prev->setNext(newNode);
        ++m_size;
        return iterator(newNode);
    }
    iterator erase(iterator delIter)
    {
        assert(delIter.isValid());
        if(!delIter.isValid())
            return iterator();
        else if(delIter.__getNode() == m_begin) {
            Node *newBegin = m_begin->next();
            newBegin->setPrevious(nullptr);
            delete m_begin;
            m_begin = newBegin;
            --m_size;
            return iterator(m_begin);
        }
        else if(delIter.__getNode() == m_end)
            return delIter;

        Node *delNode = delIter.__getNode();
        Node *prev = delNode->previous();
        Node *next = delNode->next();
        prev->setNext(next);
        next->setPrevious(prev);
        delete delNode;
        --m_size;
        return iterator(next);
    }
    void clear()
    {
        while(!isEmpty())
            erase(begin());
    }
    void swap(iterator left, iterator right)
    {
        if(left == right)
            return;

        assert(right != nullptr && left != nullptr);

        Node *leftNode = left.__getNode();
        Node *rightNode = right.__getNode();

        leftNode->next()->setPrevious(rightNode);
        leftNode->previous()->setNext(rightNode);

        rightNode->next()->setPrevious(leftNode);
        rightNode->previous()->setNext(leftNode);
    }

private:
    Node *m_begin;
    Node *m_end;
    int m_size;
};
#endif //LINK_LIST
