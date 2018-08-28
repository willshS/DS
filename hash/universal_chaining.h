//全域散列(universal hashing)
//链接法(chaining)
#include <algorithm>
#include <functional>
#include <time.h>
#include <vector>
#include "global.h"

//how to write a iterator;
template<typename _Key, typename _Val>
class cHashTable
{
private:
    struct HashNode
    {
        HashNode():_pre(NULL),_Next(NULL){}
        _Val        _value;
        _Key        _key;
        HashNode*   _pre;
        HashNode*   _Next;
    };

    int hash_func(const _Key& k)
    {
        return static_cast<int>(_a * hash_value(k) + _b) % _p % _tSize;
    }

    int _p;
    int _a;
    int _b;

    int                     _tSize;
    std::vector<HashNode*>  _table;
public:
    cHashTable(int nSize = 8, int keyLenth = 100);
    ~cHashTable();

    _Val& operator[](const _Key& k);

    void insert(const _Key& k, const _Val& v);
    _Val search(const _Key& k);
    bool del(const _Key& k);
};

template<typename _Key, typename _Val>
cHashTable<_Key, _Val>::cHashTable(int nSize, int keyLenth /*= 100*/)\
:_tSize(nSize), _table(nSize, NULL)
{
    for (;; ++keyLenth)
    {
        int i = 2, j = sqrt(keyLenth);
        for (; i < j; ++i)
        {
            if (keyLenth % i == 0)
                break;
        }

        if (i >= j)
        {
            _p = keyLenth;
            break;
        }
    }

    srand((unsigned int)time(NULL));
    _a = rand() % (_p - 1) + 1;
    _b = rand() % _p;
}

template<typename _Key, typename _Val>
cHashTable<_Key, _Val>::~cHashTable()
{
    for (int i = 0; i < _tSize; ++i)
    {
        HashNode* node = _table[i];
        if (node)
        {
            delete node;
            node = NULL;
        }
    }
}

template<typename _Key, typename _Val>
void cHashTable<_Key, _Val>::insert(const _Key& k, const _Val& v)
{
    HashNode* node = new HashNode;
    node->_key = k;
    node->_value = v;
    int buket = hash_func(k);
    HashNode* pBuket = _table[buket];
    if (pBuket == NULL)
    {
        _table[buket] = node;
        return;
    }

    while (pBuket->_Next)
        pBuket = pBuket->_Next;
    pBuket->_Next = node;
    node->_pre = pBuket;
}

template<typename _Key, typename _Val>
_Val cHashTable<_Key, _Val>::search(const _Key& k)
{
    int buket = hash_func(k);
    HashNode* node = _table[buket];
    while (node)
    {
        if (node->_key == k)
            return node->_value;
        node = node->_Next;
    }
    printf("no key");
    return _Val(0);
}

template<typename _Key, typename _Val>
bool cHashTable<_Key, _Val>::del(const _Key& k)
{
    int buket = hash_func(k);
    HashNode* node = _table[buket];
    while (node)
    {
        if (node->_key == k)
        {
            node->_pre->_Next = node->_Next;
            node->_Next->_pre = node->_pre;
            delete node;
            return true;
        }
    }
    printf("no key");
    return false;
}

template<typename _Key, typename _Val>
_Val& cHashTable<_Key, _Val>::operator[](const _Key& k)
{
    int buket = hash_func(k);
    HashNode* node = _table[buket];
    while (node)
    {
        if (node->_key == k)
            return node->_value;
        node = node->_Next;
    }
    insert(k, _Val());
    return _Val(0);
}
