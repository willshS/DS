// tree.cpp : 定义控制台应用程序的入口点。
//

#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "tree.h"
#include "rb_tree.h"
#include "BTree.h"

void testRBtree()  {
    std::vector<int> keys;
    {
        srand((unsigned)time(NULL));
        RBTree<int, std::string> temp;
        std::vector<int> eraseV;
        for (int i = 0; i < 1000; i++) {
            int k = rand() % 2000;
            temp.insert(k, "aaa");
            if (i % 17 == 0)
                eraseV.push_back(k);

            keys.push_back(k);
        }
        if (temp.Check())
            printf("ok\n");
        else
            printf("wrong\n");

        for (int i = 0; i < eraseV.size(); ++i) {
            temp.erase(eraseV[i]);
            if (!temp.Check())
                printf("%d wrong\n", i);
        }
        if (temp.Check())
            printf("ok\n");
        else
            printf("wrong\n");
    }
    getchar();
    {
        RBTree<int, std::string> temp;
        for (int i = 0; i < keys.size(); ++i) {
            temp.insert(keys[i], "aaa");
        }
    }
}

typedef BTree<char, int>::BData BData;
typedef BTree<char, int>::BNode BNode;
void testBTree() {
    BTree<char, int> tree(3);
    tree._root->_keys.resize(0);
    BData* pData = new BData('G', 1);
    tree._root->_keys.push_back(pData);
    pData = new BData('M', 1);
    tree._root->_keys.push_back(pData);
    pData = new BData('P', 1);
    tree._root->_keys.push_back(pData);
    pData = new BData('X', 1);
    tree._root->_keys.push_back(pData);
    tree._root->_leaf = false;
    tree._root->_nums = 4;
    tree._root->_child.resize(0);

    BNode* pNode = new BNode;
    pData = new BData('A', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('C', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('D', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('E', 1);
    pNode->_keys.push_back(pData);
    pNode->_leaf = true;
    pNode->_nums = 4;
    tree._root->_child.push_back(pNode);

    pNode = new BNode;
    pData = new BData('J', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('K', 1);
    pNode->_keys.push_back(pData);
    pNode->_leaf = true;
    pNode->_nums = 2;
    tree._root->_child.push_back(pNode);

    pNode = new BNode;
    pData = new BData('N', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('O', 1);
    pNode->_keys.push_back(pData);
    pNode->_leaf = true;
    pNode->_nums = 2;
    tree._root->_child.push_back(pNode);

    pNode = new BNode;
    pData = new BData('R', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('S', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('T', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('U', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('V', 1);
    pNode->_keys.push_back(pData);
    pNode->_leaf = true;
    pNode->_nums = 5;
    tree._root->_child.push_back(pNode);

    pNode = new BNode;
    pData = new BData('Y', 1);
    pNode->_keys.push_back(pData);
    pData = new BData('Z', 1);
    pNode->_keys.push_back(pData);
    pNode->_leaf = true;
    pNode->_nums = 2;
    tree._root->_child.push_back(pNode);

    tree.insert('B', 1);
    tree.insert('Q', 1);
    tree.insert('L', 1);
    tree.insert('F', 1);

    int i = tree.search('B')->_val;

    tree.erase('Q');
    tree.erase('F');
    tree.erase('M');
    tree.erase('G');
    tree.erase('D');
    tree.erase('B');
}

int main(int argc, char* argv[])
{
    for (int a = 0; a < 10; ++a) {
        printf("a %d\n", a);
    }

    int a = 1;
    printf("a %d\n", a);
    a += 1;
    testBTree();
	return 0;
}