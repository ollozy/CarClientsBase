#ifndef LINK_LIST
#define LINK_LIST

#include <QObject>

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

    ~node() { delete m_data; }

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
    Node *operator->() { return m_ptr; }
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

    LinkList() : m_end(m_begin), m_begin(new Node(new T(), m_end, m_begin)), m_size(0) {}
    LinkList(const LinkList<T>& li)
    {
        LinkList<T>::iterator it = li.begin();
        LinkList<T>::iterator thisIt;
        thisIt = insert(begin(), *it++);
        while (it != li.begin())
            thisIt = insert(thisIt, *it++);
    }
    ~LinkList()
    {
        clear();
    }

    int size() const { return m_size; }
    bool isEmpty() const { return m_begin == m_end; }
    iterator begin() const { return iterator(m_begin); }
    iterator end() const { return iterator(m_end);}

    LinkList<T>& operator=(const LinkList<T>& li)
    {
        if (this == &li)
            return *this;

        for(LinkList<T>::iterator it = li.begin(); it != li.end(); ++it)
            append(*it);

        return *this;
    }
    T& operator[](int i)
    {
        Q_ASSERT_X(i < m_size, "LinkList<T>::operator[]", "index out of range");
        if(!(i < m_size))
            return *m_end->data();
        Node *pNode = m_begin;
        for(int j = 0; i != j; ++j)
            pNode = pNode->next();
        return *pNode->data();
    }
    const T& operator[](int i) const
    {
        Q_ASSERT_X(i < m_size, "LinkList<T>::operator[]", "index out of range");
        if(!(i < m_size))
            return *m_end->data();
        Node *pNode = m_begin;
        for(int j = 0; i != j; ++j)
            pNode = pNode->next();
        return *pNode->data();
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
        if(isEmpty())
            append(val);
        else {
            Node *newBegin = new Node(new T(val), m_begin, nullptr);
            m_begin->setPrevious(newBegin);
            m_begin = newBegin;
        }
        ++m_size;
    }

    iterator insert(const T& val, iterator before)
    {
        Q_ASSERT_X(before.__getNode(), "LinkList::insert", "The specified iterator argument 'before' is invalid");
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

	iterator erase(iterator pos)
	{
		if (pos == begin())
			m_begin = m_begin->next();

		Node* iter = pos._getPtr();
        //            m_begin = m_begin->next();
		while (pos != iter->next())
			iter = iter->next();

        //        Node* iter = pos._getPtr();
		Node* newNext = iter->next()->next();
        //            iter = iter->next();
		delete iter->next();
        //        delete iter->next();
		iter->setNext(newNext);
		--m_size;
		return iterator(newNext);
	}

	void clear()
	{
		Node* iter = m_begin;
		while (!isEmpty()) {
			if (iter->next() == m_begin) {
				m_begin = m_begin->next();
			}

			Node* newNext = iter->next()->next();
			delete iter->next();
			iter->setNext(newNext);
			--m_size;
		}
	}

        //            Node* newNext = iter->next()->next();
        //            delete iter->next();
        //            iter->setNext(newNext);
        //            --m_size;
	*/
	iterator find(const T& elem)
	{
		if (isEmpty())
			return begin();
		if (elem == *m_begin->data())
			return begin();
		iterator beg = begin();
		iterator it = beg;
		while (++it != beg) {
			if(*it == elem)
				return it;
		}
		return beg;
	}

private:
    Node *m_begin;
    Node *m_end;
    int m_size;
};
#endif //LINK_LIST