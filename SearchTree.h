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
        Node *rotateLeft()
        {
            Node *rotNode = m_rightChild;
            m_rightChild = rotNode->m_leftChild;
            rotNode->m_leftChild = this;
            fixHeight();
            rotNode->fixHeight();
            return rotNode;
        }
        Node *rotateRight()
        {
            Node *rotNode = m_leftChild;
            m_leftChild = rotNode->m_rightChild;
            rotNode->m_rightChild = this;
            fixHeight();
            rotNode->fixHeight();
            return rotNode;
        }
        Node *balance()
        {
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
        Node *findMinNode()
        {
            return m_leftChild ? m_leftChild->findMinNode() : this;
        };
        Node *removeMinNode()
        {
            if(!m_leftChild)
                return m_rightChild;
            m_leftChild = m_leftChild->removeMinNode();
            return balance();
        }
        Node *insertNode(const char *key, const Val &val)
        {
            if(std::strncmp(key, m_key, KeyLen) < 0) {
                if(m_leftChild != nullptr)
                    m_leftChild = m_leftChild->insertNode(key, val);
                else
                    m_leftChild = new Node(val, key);
            }
            else if(std::strncmp(key, m_key, KeyLen) > 0) {
                if(m_rightChild != nullptr)
                    m_rightChild = m_rightChild->insertNode(key, val);
                else
                    m_rightChild = new Node(val, key);
            }
            return balance();
        }
        Node *eraceNode(const char *key)
        {
            if(std::strncmp(key, m_key, KeyLen) < 0)  {
                if(m_leftChild != nullptr)
                    m_leftChild = m_leftChild->eraceNode(key);
                //            else
                //                return node;
            }
            else if(std::strncmp(key, m_key, KeyLen) > 0) {
                if(m_rightChild != nullptr)
                    m_rightChild = m_rightChild->eraceNode(key);
                //            else
                //                return node;
            }
            else  {
                Node *leftNode = m_leftChild;
                Node *rightNode = m_rightChild;

                delete this;

                if(!rightNode) return leftNode;

                Node *minNode = rightNode->findMinNode();
                minNode->m_rightChild = rightNode->removeMinNode();
                minNode->m_leftChild = leftNode;
                return minNode->balance();
            }
            return balance();
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

    const Val &operator[](const char *key) const;
    Val &operator[](const char *key);

    const Val &get(const char *key) const;
    void insert(const char *key, const Val &val);
    void erase(const char *key);
    void clear();

private:
    Node *m_rootNode;
};

template<typename Val, uint KeyLen>
const Val &Tree<Val, KeyLen>::get(const char *key) const
{
    Node *searchNode = m_rootNode;
    while(searchNode && std::strncmp(key, searchNode->m_key, KeyLen) != 0) {
        if(std::strncmp(key, searchNode->m_key, KeyLen) > 0) {
            if(!searchNode->m_rightChild)
                searchNode = nullptr;
            else
                searchNode = searchNode->m_rightChild;
        }
        else {
            if(!searchNode->m_leftChild)
                searchNode = nullptr;
            else
                searchNode = searchNode->m_leftChild;
        }
    }
    if(searchNode)
        return searchNode->m_data;
    else {
        Q_ASSERT_X(searchNode, "Tree::get", "Attemp access to nonexistent node");
        return Val();
    }
}

template<typename Val, uint KeyLen>
void Tree<Val, KeyLen>::insert(const char *key, const Val &val)
{
    if(!m_rootNode) {
        m_rootNode = new Node(val, key);
        return;
    }
    m_rootNode = m_rootNode->insertNode(key, val);
}

template<typename Val, uint KeyLen>
void Tree<Val, KeyLen>::erase(const char *key)
{
    if(!m_rootNode)
        return;
    m_rootNode = m_rootNode->eraceNode(key);
}

template<typename Val, uint KeyLen>
void Tree<Val, KeyLen>::clear()
{

}

#endif // SEARCHTREE_H
