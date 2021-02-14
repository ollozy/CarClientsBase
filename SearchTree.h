#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <typeinfo>
#include <cstring>

template<typename Val, uint KeyLen>
class Tree {

    typedef unsigned int uint;

    struct Node {
        Node(const Val &data = Val(), const char *key = nullptr, Node *right = nullptr, Node *left = nullptr)
            : m_data(data)
            , m_key(new char[KeyLen])
            , m_height(1)
            , m_rightChild(right)
            , m_leftChild(left) { if(key) std::strncpy(m_key, key, KeyLen); }
        ~Node() { delete[] m_key; }
        int balanceFactor() const
        {
            uint leftHeight = m_leftChild ? m_leftChild->m_height : 0;
            uint rightHeight = m_rightChild ? m_rightChild->m_height : 0;

            return rightHeight - leftHeight;
        }
        void fixHeight()
        {
            uint leftHeight = m_leftChild ? m_leftChild->m_height : 0;
            uint rightHeight = m_rightChild ? m_rightChild->m_height : 0;

            m_height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        }
        Node *rotateLeft() {
            Node *rotNode = m_rightChild;
            m_rightChild = rotNode->m_leftChild;
            rotNode->m_leftChild = this;
            fixHeight();
            rotNode->fixHeight();
            return rotNode;
        }
        Node *rotateRight() {
            Node *rotNode = m_leftChild;
            m_leftChild = rotNode->m_rightChild;
            rotNode->m_rightChild = this;
            fixHeight();
            rotNode->fixHeight();
            return rotNode;
        }
        Node *balance() {
            fixHeight();
            if(balanceFactor() == 2) {
                if(m_rightChild->balanceFactor() < 0)
                    m_rightChild = m_rightChild->rotateRight();
                return rotateLeft();
            }
            else if(balanceFactor() == -2) {
                if(m_leftChild->balanceFactor() > 0)
                    m_leftChild = m_leftChild->rotateLeft();
                return rotateRight();
            }
            return this;
        }
        Val m_data;
        char *m_key;
        uint m_height;
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
    Node *insertNode(const char *key, Node *node, const Val &val)
    {
        if(std::strncmp(key, node->m_key, KeyLen) < 0) {
            if(node->m_leftChild != nullptr)
                node->m_leftChild = insertNode(key, node->m_leftChild, val);
            else
                node->m_leftChild = new Node(val, key);
        }
        else if(std::strncmp(key, node->m_key, KeyLen) > 0) {
            if(node->m_rightChild != nullptr)
                node->m_rightChild = insertNode(key, node->m_rightChild, val);
            else
                node->m_rightChild = new Node(val, key);
        }
        return node->balance();
    }

private:
    Node *m_rootNode;
};

template<typename Val, uint KeyLen>
void Tree<Val, KeyLen>::insert(const char *key, const Val &val)
{
    if(!m_rootNode) {
        m_rootNode = new Node(val, key);
        return;
    }
    m_rootNode = insertNode(key, m_rootNode, val);
    return;
}

#endif // SEARCHTREE_H
