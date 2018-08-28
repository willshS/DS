#include <stdio.h>
#include "GreedAlgorithm.h"

class test
{
public:
    test(){}
    static void getA() {};
    void getB() {};
    virtual void getC() {};
    int a;
    static int c;
};

using namespace std;
int minCostClimbingStairs(vector<int>& cost) {
    if (cost.size() <= 1) return 0;
    int *nMin = new int[cost.size()];
    nMin[0] = cost[0];
    nMin[1] = cost[1];
    for (int i = 2; i < cost.size(); ++i) {
        nMin[i] = cost[i] + (nMin[i - 1] < nMin[i - 2] ? nMin[i - 1] : nMin[i - 2]);
    }
    return nMin[cost.size() - 1] > nMin[cost.size() - 2] ? nMin[cost.size() - 2] : nMin[cost.size() - 1];
}

int main() {
    std::vector<int> cost;
    cost.push_back(1);
    cost.push_back(1);
    cost.push_back(0);
    cost.push_back(0);
    int longest = minCostClimbingStairs(cost);
    //pT->getC();
//     std::vector<int> p, q;
//     p.push_back(1);
//     p.push_back(3);
//     p.push_back(0);
//     p.push_back(5);
//     p.push_back(3);
//     p.push_back(5);
//     p.push_back(6);
//     p.push_back(8);
//     p.push_back(8);
//     p.push_back(2);
//     p.push_back(12);
//     
//     q.push_back(4);
//     q.push_back(5);
//     q.push_back(6);
//     q.push_back(7);
//     q.push_back(9);
//     q.push_back(9);
//     q.push_back(10);
//     q.push_back(11);
//     q.push_back(12);
//     q.push_back(14);
//     q.push_back(16);
// 
//     int longest = chooseActivity(p, q);
     printf("longest %d", longest);
    getchar();
    return 0;
}