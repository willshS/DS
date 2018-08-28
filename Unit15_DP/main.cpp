#include <stdio.h>
#include "DynamicProgramming.h"

int main()
{
    std::vector<int> p, q;
    p.push_back(0);
    p.push_back(60);
    p.push_back(100);
    p.push_back(120);

    q.push_back(0);
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);

    int longest = maxValue(p, q, 5);
    printf("longest %d", longest);
    getchar();
    return 0;
}