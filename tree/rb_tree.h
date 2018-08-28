#include <sstream>
template<typename _Key, typename _Val>
class RBTree
{
public:
    struct Node
    {
        enum CLR
        {
            RED,
            BLACK
        };

        Node()
        {
            _clr = BLACK;
            _parent = _left = _right = NULL;
        }

        ~Node()
        {
        }

        CLR     _clr;
        _Key    _key;
        _Val    _value;
        Node*   _parent;
        Node*   _left;
        Node*   _right;
    };

    RBTree();
    ~RBTree();

    void tree_walk(Node* n);
    Node* getNode(const _Key& k);
    Node* insert(const _Key& k, const _Val& v);
    void erase(const _Key& k);
    Node* modify(const _Key& k, const _Val& v);

    bool Check()
    {
        if (_root->_clr == Node::RED)
            return false;
        int count = 0;//统计出一条路径的黑色节点的个数
        int num = 0;//需要与count比较的其他路径黑色节点个数
        Node* cur = _root;
        while (cur != _NIL)
        {
            if (cur->_clr == Node::BLACK)
                count++;
            cur = cur->_left;
        }
        return _Check(_root, count, num);
    }
    bool _Check(Node* root, int BlackNum, int CurBlackNum)
    {
        if (root == _NIL)
            return true;
        if (root->_clr == Node::RED && root->_parent->_clr == Node::RED)//存在两个连续的红节点
            return false;
        if (root->_clr == Node::BLACK)//黑节点就CurBlackNum++
            CurBlackNum++;
        if (root->_left == _NIL && root->_right == _NIL)
        {
            if (CurBlackNum == BlackNum)
                return true;
            else//黑色节点不相等返回false
                return false;
        }
        if (root->_left != _NIL)
        {
            if (root->_left->_parent != root)
            {
                printf("wrong\n");
                return false;
            }
        }
        if (root->_right != _NIL)
        {
            if (root->_right->_parent != root)
            {
                printf("wrong\n");
                return false;
            }
        }
        return _Check(root->_left, BlackNum, CurBlackNum)
            && _Check(root->_right, BlackNum, CurBlackNum);//进行左右递归
    }

    Node* _root;
private:
    Node* getNIL();
    void delTree(Node* p);
    void rightRotate(Node* p);
    void leftRotate(Node* p);
    Node* createNode(const _Key& k, const _Val& v);
    void insertFixUp(Node* p);
    Node* maximum(Node *p);
    Node* minimum(Node *p);
    void deleteFixUp(Node* p);
    void transPlant(Node* pDel, Node* pNew);
private:
    
    const Node* _NIL = new Node;
};

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::tree_walk(Node* n)
{
    if (n == _NIL)
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
RBTree<_Key, _Val>::RBTree()
{
    _root = getNIL();
}

template<typename _Key, typename _Val>
RBTree<_Key, _Val>::~RBTree()
{
    delTree(_root);
    delete _NIL;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::getNIL()
{
    return const_cast<Node*>(_NIL);
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::delTree(Node* p)
{
    if (p == _NIL)
        return;

    delTree(p->_left);
    delTree(p->_right);
    delete p;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::createNode(const _Key& k, const _Val& v)
{
    Node *pNode = new Node;
    pNode->_clr = Node::RED;
    pNode->_left = getNIL();
    pNode->_right = getNIL();
    pNode->_parent = getNIL();
    pNode->_key = k;
    pNode->_value = v;
    return pNode;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::getNode(const _Key& k)
{
    Node* pCur = _root;
    while (pCur != _NIL)
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
void RBTree<_Key, _Val>::leftRotate(Node* p)
{
    Node *pR = p->_right;
    p->_right = pR->_left;
    if (pR->_left != _NIL)
        pR->_left->_parent = p;
    pR->_parent = p->_parent;
    if (p->_parent == _NIL)
        _root = pR;
    else if (p == p->_parent->_left)
        p->_parent->_left = pR;
    else
        p->_parent->_right = pR;
    pR->_left = p;
    p->_parent = pR;
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::rightRotate(Node* p)
{
    Node *pL = p->_left;
    p->_left = pL->_right;
    if (pL->_right != _NIL)
        pL->_right->_parent = p;

    pL->_parent = p->_parent;
    if (p->_parent == _NIL)
        _root = pL;
    else if (p == p->_parent->_left)
        p->_parent->_left = pL;
    else
        p->_parent->_right = pL;
    pL->_right = p;
    p->_parent = pL;
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::insertFixUp(Node* p)
{
    while (p->_parent->_clr == Node::RED)
    {
        if (p->_parent == p->_parent->_parent->_left)
        {
            Node* pUncle = p->_parent->_parent->_right;
            if (pUncle->_clr == Node::RED)
            {
                p->_parent->_clr = Node::BLACK;
                pUncle->_clr = Node::BLACK;
                p->_parent->_parent->_clr = Node::RED;
                p = p->_parent->_parent;
            }
            else if (p == p->_parent->_right)
            {
                p = p->_parent;
                leftRotate(p);
            }
            else
            {
                p->_parent->_clr = Node::BLACK;
                p->_parent->_parent->_clr = Node::RED;
                rightRotate(p->_parent->_parent);
            }
        }
        else
        {
            Node* pUncle = p->_parent->_parent->_left;
            if (pUncle->_clr == Node::RED)
            {
                p->_parent->_clr = Node::BLACK;
                pUncle->_clr = Node::BLACK;
                p->_parent->_parent->_clr = Node::RED;
                p = p->_parent->_parent;
            }
            else if (p == p->_parent->_left)
            {
                p = p->_parent;
                rightRotate(p);
            }
            else
            {
                p->_parent->_clr = Node::BLACK;
                p->_parent->_parent->_clr = Node::RED;
                leftRotate(p->_parent->_parent);
            }
        }
    }
    _root->_clr = Node::BLACK;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::insert(const _Key& k, const _Val& v)
{
    Node *pNode = createNode(k, v);
    Node *pCur = _root, *pre = getNIL();
    while (pCur != _NIL)
    {
        pre = pCur;
        if (pCur->_key < k)
            pCur = pCur->_right;
        else if (pCur->_key > k)
            pCur = pCur->_left;
        else
            return pCur;
    }
    pNode->_parent = pre;
    if (pre == _NIL)
        _root = pNode;
    else if (k < pre->_key)
        pre->_left = pNode;
    else
        pre->_right = pNode;
    insertFixUp(pNode);
    return pNode;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::maximum(Node *p)
{
    Node* pCur = p;
    while (pCur->_right != _NIL)
        pCur = pCur->_right;
    return pCur;
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::minimum(Node *p)
{
    Node* pCur = p;
    while (pCur->_left != _NIL)
        pCur = pCur->_left;
    return pCur;
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::transPlant(Node* pDel, Node* pNew)
{
    if (pDel->_parent == _NIL)
        _root = pNew;
    else if (pDel == pDel->_parent->_left)
        pDel->_parent->_left = pNew;
    else
        pDel->_parent->_right = pNew;
    pNew->_parent = pDel->_parent;
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::deleteFixUp(Node* p)
{
    while (p != _root && p->_clr == Node::BLACK)
    {
        if (p == p->_parent->_left)
        {
            Node* pUncle = p->_parent->_right;
            if (pUncle->_clr == Node::RED)
            {
                p->_parent->_clr = Node::RED;
                pUncle->_clr = Node::BLACK;
                leftRotate(p->_parent);
                pUncle = p->_parent->_right;
            }

            if (pUncle->_left->_clr == Node::BLACK
                && pUncle->_right->_clr == Node::BLACK)
            {
                pUncle->_clr = Node::RED;
                p = p->_parent;
            }
            else if (pUncle->_right->_clr == Node::BLACK)
            {
                pUncle->_clr = Node::RED;
                pUncle->_left->_clr = Node::BLACK;
                rightRotate(pUncle);
                pUncle = p->_parent->_right;
            }
            else
            {
                pUncle->_clr = p->_parent->_clr;
                p->_parent->_clr = Node::BLACK;
                pUncle->_right->_clr = Node::BLACK;
                leftRotate(p->_parent);
                p = _root;
            }
        }
        else
        {
            Node *pUncle = p->_parent->_left;
            if (pUncle->_clr == Node::RED)
            {
                p->_parent->_clr = Node::RED;
                pUncle->_clr = Node::BLACK;
                rightRotate(p->_parent);
                pUncle = p->_parent->_left;
            }

            if (pUncle->_left->_clr == Node::BLACK
                && pUncle->_right->_clr == Node::BLACK)
            {
                pUncle->_clr = Node::RED;
                p = p->_parent;
            }
            else if (pUncle->_left->_clr == Node::BLACK)
            {
                pUncle->_clr = Node::RED;
                pUncle->_right->_clr = Node::BLACK;
                leftRotate(pUncle);
                pUncle = p->_parent->_left;
            }
            else
            {
                pUncle->_clr = p->_parent->_clr;
                p->_parent->_clr = Node::BLACK;
                pUncle->_left->_clr = Node::BLACK;
                rightRotate(p->_parent);
                p = _root;
            }
        }
    }
    p->_clr = Node::BLACK;
}

template<typename _Key, typename _Val>
void RBTree<_Key, _Val>::erase(const _Key& k)
{
    Node* pCur = getNode(k);
    if (!pCur)
        return;
    Node* pSucceed = getNIL();
    Node* pNext;
    Node::CLR curClr = pCur->_clr;
    if (pCur->_left == _NIL)
    {
        pSucceed = pCur->_right;
        transPlant(pCur, pCur->_right);
    }
    else if (pCur->_right == _NIL)
    {
        pSucceed = pCur->_left;
        transPlant(pCur, pCur->_left);
    }
    else
    {
        pNext = minimum(pCur->_right);
        curClr = pNext->_clr;
        pSucceed = pNext->_right;
        if (pNext->_parent == pCur)
            pSucceed->_parent = pNext;
        else
        { 
            transPlant(pNext, pNext->_right);
            pNext->_right = pCur->_right;
            pNext->_right->_parent = pNext;
        }
        transPlant(pCur, pNext);
        pNext->_left = pCur->_left;
        pNext->_left->_parent = pNext;
        pNext->_clr = pCur->_clr;
    }

    if (curClr == Node::BLACK)
        deleteFixUp(pSucceed);
}

template<typename _Key, typename _Val>
typename RBTree<_Key, _Val>::Node* RBTree<_Key, _Val>::modify(const _Key& k, const _Val& v)
{
    Node* pCur = getNode(k);
    if (!pCur)
        return NULL;

    pCur->_value = v;
    return pCur;
}
