#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <typeinfo>
#include <cstring>
#include <iostream>

template<typename Val, uint KeyLen>
class Tree {

    typedef unsigned int uint;

    struct Node {
        Node(Val data = Val(), const char *key = nullptr, Node *right = nullptr, Node *left = nullptr)
            : m_data(data)
            , m_key(new char[KeyLen])
            , m_rightChild(right)
            , m_leftChild(left) { if(key) std::strncpy(m_key, key, KeyLen); }
        ~Node() { delete[] m_key; }
        Val m_data;
        char *m_key;
        Node *m_rightChild;
        Node *m_leftChild;
    };

public:
    Tree() : m_rootNode(nullptr) {}
    ~Tree() {};

    const Val find(const char *key) const;
    void insert(const char *key, const Val &val);
    void erace(const char *key);
    void clear();


private:
    Node *m_rootNode;
};

template<typename Val, uint KeyLen>
void Tree<Val, KeyLen>::insert(const char *key, const Val &val)
{
    Node *newNode = new Node(val, key);
    if(!m_rootNode) {
        m_rootNode = newNode;
        return;
    }
    Node *searchNode = m_rootNode;
    while((std::strncmp(key, searchNode->m_key, KeyLen) > 0 && searchNode->m_rightChild)
          || (std::strncmp(key, searchNode->m_key, KeyLen) < 0 && searchNode->m_leftChild)) {
        if(std::strncmp(key, searchNode->m_key, KeyLen) > 0)
            searchNode = searchNode->m_rightChild;
        else if(std::strncmp(key, searchNode->m_key, KeyLen) < 0)
            searchNode = searchNode->m_leftChild;
    }
    if(std::strncmp(key, searchNode->m_key, KeyLen) > 0)
        searchNode->m_rightChild = newNode;
    else if(std::strncmp(key, searchNode->m_key, KeyLen) < 0)
        searchNode->m_leftChild = newNode;
}





#endif // SEARCHTREE_H
