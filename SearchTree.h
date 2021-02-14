#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <typeinfo>
#include <cstring>

template<typename Val, typename Key>
class Tree {

    typedef unsigned int uint ;
    struct Node {
        Node(Val data = Val(), Key key = Key(), Node *right = nullptr, Node *left = nullptr)
            : m_data(data)
            , m_rightChild(right)
            , m_key(key)
            , m_leftChild(left) {}
        Val m_data;
        Key m_key;
        Node *m_rightChild;
        Node *m_leftChild;
    };

public:
    Tree() : m_rootNode(nullptr)
    {
        if(typeid (Key) == typeid (const char *)
                || typeid (Key) == typeid (char *))
            cmpFunc = std::strcmp;
        else cmpFunc = [&](Key left, Key right)->uint{
            if(left > right)
                return 1;
            else if(right > left)
                return -1;
            else
                return 0;
        };
    }
    ~Tree();

    const Val find(const Key key) const;
    void insert(const Val &val, const Key &key);
    void erace(const Key key);
    void clear();


private:
    Node *m_rootNode;
    uint (*cmpFunc)(Key, Key);
};

template<typename Val, typename Key>
void Tree<Val, Key>::insert(const Val &val, const Key &key)
{
    Node *newNode = new Node(val, key);
    if(!m_rootNode->m_data) {
        m_rootNode->m_data = newNode;
        return;
    }
    Node *searchNode = m_rootNode;
    while((cmpFunc(key, searchNode->m_key) > 0 && !searchNode->m_rightChild)
          || (cmpFunc(key, searchNode->m_key) < 0 && !searchNode->m_leftChild)) {
        if(cmpFunc(key, searchNode->m_key) > 0)
            searchNode = searchNode->m_rightChild;
        else if(cmpFunc(key, searchNode->m_key) < 0)
            searchNode = searchNode->m_leftChild;
    }
    if(cmpFunc(key, searchNode->m_key) > 0)
        searchNode->m_rightChild = newNode;
    else if(cmpFunc(key, searchNode->m_key) < 0)
        searchNode->m_leftChild = newNode;
}





#endif // SEARCHTREE_H
