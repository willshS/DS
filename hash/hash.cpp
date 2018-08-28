#include <stdio.h>
#include "universal_chaining.h"
#include <hash_map>

int main()
{
    std::hash_map<int, int> hashd;
    hashd[1] = 1;

    cHashTable<int, int> table;
    for (int i = 0; i < 50; ++i)
    {
        table.insert(i, i);
    }
    
    for (int i = 0; i < 50; ++i)
    {
        int n = table.search(i);
        printf("n %d\n", n);
    }

    getchar();
    return 0;
}