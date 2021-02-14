#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <typeinfo>
#include <cstring>

template<typename Val, typename Key>
class Tree {

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
    Tree() : m_rootNode(nullptr) {
        if(typeid (Key) == typeid (const char *)
                || typeid (Key) == typeid (char *))
            equalFunc = std::strcpy;
        else equalFunc = nullptr;
    }
    ~Tree();

    const Val find(const Key key) const;
    void insert(const Val &val);
    void erace(const Key key);
    void clear();

    bool (*equalFunc)(Key, Key);

private:
    Node *m_rootNode;
};


}



#endif // SEARCHTREE_H
