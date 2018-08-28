#include <sstream>
//¶þ²æËÑË÷Ê÷
template<typename _Key, typename _Val>
class SearchTree
{
public:
    struct Node
    {
        Node()
        {
            _parent = _left = _right = NULL;
        }

        ~Node()
        {
        }

        _Key    _key;
        _Val    _value;
        Node*   _parent;
        Node*   _left;
        Node*   _right;
    };

    SearchTree();
    ~SearchTree();

    void tree_walk(Node* n);
    Node* getNode(const _Key& k);
    Node* insert(const _Key& k, const _Val& v);
    void erase(const _Key& k);
    Node* modify(const _Key& k, const _Val& v);
    Node* root(){ return _root; }
private:
    Node* pioneer(Node* n);
    Node* succeed(Node* n);
    Node* maximum(Node *n);
    Node* minimum(Node *n);
    void transPlant(Node* pDel, Node* pNew);
    void delTree(Node* n);
    Node* createNode(const _Key& k, const _Val& v);
private:
    Node* _root;
};

template<typename _Key, typename _Val>
void SearchTree<_Key, _Val>::delTree(Node* n)
{
    if (!n)
        return;
    
    delTree(n->_left);
    delTree(n->_right);
    delete n;
}

template<typename _Key, typename _Val>
SearchTree<_Key, _Val>::SearchTree()
{
    _root = NULL;
}

template<typename _Key, typename _Val>
SearchTree<_Key, _Val>::~SearchTree()
{
    delTree(_root);
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::createNode(const _Key& k, const _Val& v)
{
    Node *pNode = new Node;
    pNode->_left = NULL;
    pNode->_right = NULL;
    pNode->_parent = NULL;
    pNode->_key = k;
    pNode->_value = v;
    return pNode;
}

template<typename _Key, typename _Val>
void SearchTree<_Key, _Val>::tree_walk(Node* n)
{
    if (!n)
        return;

    //inorder
    tree_walk(n->_left);
    std::stringstream ss;
    ss << n->_key;
    std::string str;
    ss >> str;
    printf("%s ", str.c_str());
    tree_walk(n->_right);
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::getNode(const _Key& k)
{
    Node* pCur = _root;
    while (pCur)
    {
        if (pCur->_key < k)
            pCur = pCur->_right;
        else if (pCur->_key > k)
            pCur = pCur->_left;
        else
            return pCur;
    }
    return NULL;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::insert(const _Key& k, const _Val& v)
{
    Node *pNode = createNode(k, v);
    Node *pCur = _root, *pre = NULL;
    while (pCur)
    {
        pre = pCur;
        if (pCur->_key < k)
            pCur = pCur->_right;
        else
            pCur = pCur->_left;
    }
    if (pre == NULL)
        _root = pNode;
    else if (k < pre->_key)
        pre->_left = pNode;
    else if (k > pre->_key)
        pre->_right = pNode; 
    else
        return pre;
    pNode->_parent = pre;
    return pNode;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::modify(const _Key& k, const _Val& v)
{
    Node* pCur = getNode(k);
    if (!pCur)
        return NULL;

    pCur->_value = v;
    return pCur;
}

template<typename _Key, typename _Val>
void SearchTree<_Key, _Val>::erase(const _Key& k)
{
    Node* pCur = getNode(k);
    if (!pCur)
        return;

    if (pCur->_left == NULL)
        transPlant(pCur, pCur->_right);
    else if (pCur->_right == NULL)
        transPlant(pCur, pCur->_right);
    else
    {
        Node* pSucceed = minimum(pCur->_right);
        if (pSucceed->_parent != pCur)
        {
            transPlant(pSucceed, pSucceed->_right);
            pSucceed->_right = pCur->_right;
            pSucceed->_right->_parent = pSucceed;
        }
        transPlant(pCur, pSucceed);
        pSucceed->_left = pCur->_left;
        pSucceed->_left->_parent = pSucceed;
    }
}

template<typename _Key, typename _Val>
void SearchTree<_Key, _Val>::transPlant(Node* pDel, Node* pNew)
{
    if (pDel->_parent == NULL)
        _root = pNew;
    else if (pDel == pDel->_parent->_left)
        pDel->_parent->_left = pNew;
    else
        pDel->_parent->_right = pNew;

    if (pNew)
        pNew->_parent = pDel->_parent;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::pioneer(Node* n)
{
    Node* pCur = n;
    if (!pCur)
        return NULL;
    if (pCur->_left)
        return maximum(pCur->_left);
    Node* pParent = pCur->_parent;
    while (pParent && pCur = pParent->_left)
    {
        pCur = pParent;
        pParent = pCur->_parent;
    }
    return pParent;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::succeed(Node* n)
{
    Node* pCur = n;
    if (!pCur)
        return NULL;
    if (pCur->_right)
        return minimum(pCur->_right);
    Node* pParent = pCur->_parent;
    while (pParent && pCur = pParent->_right)
    {
        pCur = pParent;
        pParent = pCur->_parent;
    }
    return pParent;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::maximum(Node *n)
{
    Node* pCur = n;
    while (pCur->_right)
        pCur = pCur->_right;
    return pCur;
}

template<typename _Key, typename _Val>
typename SearchTree<_Key, _Val>::Node* SearchTree<_Key, _Val>::minimum(Node *n)
{
    Node* pCur = n;
    while (pCur->_left)
        pCur = pCur->_left;
    return pCur;
}
