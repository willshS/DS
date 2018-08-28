#include <vector>
#include <assert.h>

#define uint unsigned int

template<typename KEY, typename VAL>
class BTree
{
public:
    struct BData
    {
        KEY _key;
        VAL _val;

        BData(const KEY& k, const VAL& v) :_key(k), _val(v) {}
    };

    BTree(uint degree);
    ~BTree();

    BData* search(const KEY& k);
    BData* insert(const KEY& k, const VAL& v);
    void erase(const KEY& k);
//private:
    struct BNode
    {
        bool                    _leaf;
        uint                    _nums;      //min is _degree - 1; max is 2*_degree - 1;
        std::vector<BData*>     _keys;      //size is nums
        std::vector<BNode*>     _child;     //size is nums+1

        void setNums(uint nums) {
            _nums = nums;
            _keys.resize(nums, NULL/*new BTree<KEY, VAL>::BData()*/);
            if (!_leaf) //if it is leaf, it need not child;
                _child.resize(nums + 1, NULL);
        }
    };

    BNode* search(BNode* p, const KEY& k, int& index);  //index is the key i-th in the return value;
    BNode* newNode();
    void splitNode(BNode* p, uint index);  //split node p index-th child node; 
    void insert(BNode* pNode, BData* pData);  //insert pData to pNode if pNode is not full;
    BData* erase(BNode* p, const KEY& k);   //erase k from node p or p->_childs;
//private:
    uint    _degree;
    BNode*  _root;
    uint    _maxKeys;
    uint    _minKeys;
};

template<typename KEY, typename VAL>
BTree<KEY, VAL>::BTree(uint degree) {
    BNode *pNew = newNode();
    _degree = degree;
    _maxKeys = 2 * _degree - 1;
    _minKeys = _degree - 1;
    _root = pNew;
}

template<typename KEY, typename VAL>
BTree<KEY, VAL>::~BTree() {
#pragma message("BTree<KEY, VAL>::~BTree() : you need clean all node data here.")
}

template<typename KEY, typename VAL>
typename BTree<KEY, VAL>::BNode* BTree<KEY, VAL>::newNode() {
    BNode *pNew = new BNode;
    pNew->_leaf = true;
    pNew->_nums = 0;
    return pNew;
}

template<typename KEY, typename VAL>
typename BTree<KEY, VAL>::BData* BTree<KEY, VAL>::search(const KEY& k) {
    int index = 0;
    BNode* p = search(_root, k, index);
    return p->_keys[index];
}

template<typename KEY, typename VAL>
typename BTree<KEY, VAL>::BNode* BTree<KEY, VAL>::search(BNode* p, const KEY& k, int& index) {
    int i = 0;
    while (i < p->_nums && k > p->_keys[i]->_key) ++i;

    if (i < p->_nums && p->_keys[i]->_key == k) {
        index = i;
        return p;
    }

    if (p->_leaf)
        return NULL;

    return search(p->_child[i], k, index);
}

template<typename KEY, typename VAL>
void BTree<KEY, VAL>::splitNode(BNode* p, uint index) {
    BNode* pNew = newNode();
    BNode* pOld = p->_child[index];
    pNew->_leaf = pOld->_leaf;
    pNew->setNums(_degree - 1);
    //move t+1 to 2*t-1 keys to new node;
    int i = 0;
    for (; i < _degree - 1; ++i)
        pNew->_keys[i] = pOld->_keys[i + _degree];
    if (!pOld->_leaf) {
        //move t+1 to 2*t child to new node;
        for (i = 0; i < _degree; ++i)
            pNew->_child[i] = pOld->_child[i + _degree];
    }

    //insert pOld t-th key to Node p index-th key;
    p->setNums(p->_nums + 1);
    i = p->_nums - 1;
    for (; i > index; --i)
        p->_keys[i] = p->_keys[i - 1];
    p->_keys[i] = pOld->_keys[_degree - 1];
    //insert pNew to Node p (index+1)-th child;
    for (i = p->_nums; i > index; --i)
        p->_child[i] = p->_child[i - 1];
    p->_child[index + 1] = pNew;

    pOld->setNums(_degree - 1);
}

template<typename KEY, typename VAL>
void BTree<KEY, VAL>::insert(BNode* pNode, BData* pData) {
    if (pNode->_leaf) {
        //if node is leaf, insert it.
        int i = pNode->_nums - 1;
        pNode->setNums(pNode->_nums + 1);
        while (i >= 0 && pData->_key < pNode->_keys[i]->_key) {
            pNode->_keys[i + 1] = pNode->_keys[i];
            --i;
        }
        pNode->_keys[i + 1] = pData;
    }
    else {
        //if node is not leaf, find k(i-1) < k < k(i);
        int i = pNode->_nums - 1;
        while (i >= 0 && pData->_key < pNode->_keys[i]->_key) --i;
        ++i;
        //check child(i); if need split, split and check i;
        if (pNode->_child[i]->_nums == 2*_degree-1) {
            splitNode(pNode, i);
            if (pData->_key > pNode->_keys[i]->_key)
                ++i;
        }
        //then insert at child(i)
        insert(pNode->_child[i], pData);
    }
}

template<typename KEY, typename VAL>
typename BTree<KEY, VAL>::BData* BTree<KEY, VAL>::insert(const KEY& k, const VAL& v) {
    BData* pNewData = new BData(k, v);
    BNode* pNode = _root;
    if (pNode->_nums == _maxKeys) {
        BNode* pNewRoot = newNode();
        _root = pNewRoot;
        pNewRoot->_leaf = false;
        pNewRoot->setNums(0);
        pNewRoot->_child[0] = pNode;
        splitNode(pNewRoot, 0);
        insert(pNewRoot, pNewData);
    }
    else
        insert(pNode, pNewData);
    return pNewData;
}


template<typename KEY, typename VAL>
typename BTree<KEY, VAL>::BData* BTree<KEY, VAL>::erase(BNode* p, const KEY& k) {
    int i = 0;
    BData* pData = NULL;
    while (i < p->_nums && k > p->_keys[i]->_key) ++i;

    if (i < p->_nums && p->_keys[i]->_key == k) {
        pData = p->_keys[i];
        if (p->_leaf) { //k in node p, and p is leaf, return p;
            while (i < p->_nums - 1) {
                p->_keys[i] = p->_keys[i + 1];
                ++i;
            }
            p->setNums(p->_nums - 1);
            return pData;
        }
        BNode* pPioneer = p->_child[i];
        if (pPioneer->_nums >= _degree) {   
            //pioneer has enough keys, use pioneer key instead of key[i]; erase pioneer key;
            p->_keys[i] = pPioneer->_keys[pPioneer->_nums - 1];
            erase(pPioneer, p->_keys[i]->_key);
            return pData;
        }
        assert(pPioneer->_nums == _degree - 1);
        BNode* pSucceed = p->_child[i + 1];
        if (pSucceed->_nums >= _degree) {
            //succeed such as pioneer;
            p->_keys[i] = pSucceed->_keys[0];
            erase(pSucceed, p->_keys[i]->_key);
            return pData;
        }
        assert(pSucceed->_nums == _degree - 1);
        assert(pSucceed->_leaf == pPioneer->_leaf);
        //merge pioneer, key[i] and succeed
        pPioneer->setNums(2 * _degree - 1);
        int index = _degree - 1;
        pPioneer->_keys[index] = pData;
        for (index += 1; index < 2 * _degree - 1; ++index) {
            pPioneer->_keys[index] = pSucceed->_keys[index - _degree];
            if (!pPioneer->_leaf)
                pPioneer->_child[index] = pSucceed->_child[index - _degree];
        }
        if (!pPioneer->_leaf)
            pPioneer->_child[index] = pSucceed->_child[_degree - 1];
        //delete key[i] from node p
        index = i;
        while (index < p->_nums - 1) {
            p->_keys[index] = p->_keys[index + 1];
            p->_child[index + 1] = p->_child[index + 2];
            ++index;
        }
        p->setNums(p->_nums - 1);
        delete pSucceed;
        //delete key[i] from node pioneer
        erase(pPioneer, k);
        return pData;
    }
    else {
        if (p->_leaf)
            return NULL;
        BNode* pChild = p->_child[i];
        if (pChild->_nums >= _degree)
            return erase(pChild, k);

        assert(pChild->_nums == _degree - 1);
        BNode* pBrother = NULL;
        bool bRight = false; //child is > brother?
        if (i == 0)
            pBrother = p->_child[1];
        else if (i == p->_nums) {
            pBrother = p->_child[i - 1];
            --i;
            bRight = true;
        }
        else {
            pBrother = p->_child[i + 1];
            if (pBrother->_nums == _degree - 1) {
                pBrother = p->_child[i - 1];
                --i;
                bRight = true;
            }
        }

        if (pBrother->_nums >= _degree) {
            //move key[i] to pChild and move pBrother->key[0] or pBrother->key[t-1]  to p, then erase(pchild, k);
            pChild->setNums(_degree);
            if (bRight) {
                //if pchild is on right, key[i] to pChild->keys[0]
                int index = _degree - 1;
                if (!pChild->_leaf)
                    pChild->_child[_degree] = pChild->_child[_degree - 1];
                for (; index > 0; --index) {
                    pChild->_keys[index] = pChild->_keys[index - 1];
                    pChild->_child[index] = pChild->_child[index - 1];
                }
                pChild->_keys[0] = p->_keys[i];
                if (!pChild->_leaf)
                    pChild->_child[0] = pBrother->_child[pBrother->_nums];
                p->_keys[i] = pBrother->_keys[_degree - 1];
            }
            else {
                pChild->_keys[_degree - 1] = p->_keys[i];
                if (!pChild->_leaf)
                    pChild->_child[_degree] = pBrother->_child[0];
                p->_keys[i] = pBrother->_keys[0];
                int index = 0;
                for (; index < pBrother->_nums - 1; ++index) {
                    pBrother->_keys[index] = pBrother->_keys[index + 1];
                    if (!pBrother->_leaf)
                        pBrother->_child[index] = pBrother->_child[index + 1];
                }
                if (!pBrother->_leaf)
                    pBrother->_child[index] = pBrother->_child[index + 1];
            }
            
            pBrother->setNums(pBrother->_nums - 1);
            return erase(pChild, k);
        }
        else {
            //merge pChild, key[i] and pBrother;
            //make sure pChild is before pBrother;
            if (bRight) {
                BNode* pTemp = pBrother;
                pBrother = pChild;
                pChild = pTemp;
            }
            pChild->setNums(2 * _degree - 1);
            int index = _degree - 1;
            pChild->_keys[index] = p->_keys[i];
            for (index += 1; index < 2 * _degree - 1; ++index) {
                pChild->_keys[index] = pBrother->_keys[index - _degree];
                if (!pChild->_leaf)
                    pChild->_child[index] = pBrother->_child[index - _degree];
            }
            if (!pChild->_leaf)
                pChild->_child[index] = pBrother->_child[_degree - 1];
            //delete key[i] from node p
            index = i;
            while (index < p->_nums - 1) {
                p->_keys[index] = p->_keys[index + 1];
                p->_child[index + 1] = p->_child[index + 2];
                ++index;
            }
            if (p->_nums == 1) {
                assert(_root = p);
                _root = p->_child[0];
                p->setNums(0);                
                delete p;
            }
            delete pBrother;
            //delete key[i] from node pioneer
            return erase(pChild, k);
        }
    }
}

template<typename KEY, typename VAL>
void BTree<KEY, VAL>::erase(const KEY& k) {
    if (!search(k))
        return ;
    BData* pData = erase(_root, k);
    delete pData;
}