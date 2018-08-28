#include <algorithm>
#include "DynamicProgramming.h"

/*normal recursion
int getMaxPrice(std::vector<int> price, int cutLen)
{
    if (cutLen == 1)
        return price[1];

    int maxPrice = price[cutLen];
    for (int i = 1; i <= cutLen/2; ++i)
    {
        maxPrice = std::max(getMaxPrice(price, cutLen - i) + getMaxPrice(price, i), maxPrice);
    }
    return maxPrice;
}
*/

/*this is top to down dp;
int getMaxPrice(std::vector<int> price, int cutLen, int* maxVec)
{
    if (maxVec[cutLen] != -1)
        return maxVec[cutLen];

    int maxPrice = price[cutLen];
    for (int i = 1; i <= cutLen / 2; ++i)
    {
        maxPrice = std::max(getMaxPrice(price, cutLen - i, maxVec) + getMaxPrice(price, i, maxVec), maxPrice);
        if (maxPrice > maxVec[cutLen])
            maxVec[cutLen] = maxPrice;
    }
    return maxVec[cutLen];
}

void cutRod(std::vector<int> price, int cutLen)
{
    int n = price.size();
    int* maxPrice = new int[n];
    for (int i = 0; i < n; ++i)
        maxPrice[i] = -1;
    maxPrice[1] = price[1];
    printf("max Price : %d\n", getMaxPrice(price, cutLen, maxPrice));
}
*/

/*this is down to top*/
void cutRod(std::vector<int> price, int cutLen)
{
    int n = price.size();
    int* maxPrice = new int[n];
    for (int i = 0; i < n; ++i)
        maxPrice[i] = -1;
    maxPrice[1] = price[1];

    for (int i = 2; i <= cutLen; ++i)
    {
        int nowMax = price[i];
        for (int j = 1; j < i; ++j)
            nowMax = std::max(nowMax, price[j] + maxPrice[i - j]);

        if (maxPrice[i] < nowMax)
            maxPrice[i] = nowMax;
    }

    printf("max Price : %d\n", maxPrice[cutLen]);
}

/*normal recursion, specify i is ith matrix.
int getMinMultiply(std::vector<int> matrix, int i, int j)
{
    if (i == j)
        return 0;
    int minij = 0x0fffffff;//if x86 is 0x0fff
    for (int k = i; k < j; ++k)
    {
        int nCount = getMinMultiply(matrix, i, k) + getMinMultiply(matrix, k+1, j) + matrix[i-1] * matrix[k] * matrix[j];
        if (nCount < minij)
            minij = nCount;
    }
    return minij;
}
*/

/*this is top to down dynamic programming
Although get i to j min multiply, but (i to i+1,i+2...j) and (i+1 to i+2, i+3...j)...
all in **minMultiply
int getMinMultiply(std::vector<int> matrix, int i, int j, int** &minMultiply){
    if (i == j)
        return 0;
    if (minMultiply[i][j] != -1)
        return minMultiply[i][j];

    for (int k = i; k < j; ++k){
        int nCount = getMinMultiply(matrix, i, k, minMultiply) + getMinMultiply(matrix, k + 1, j, minMultiply) + matrix[i - 1] * matrix[k] * matrix[j];
        if (minMultiply[i][j] == -1 || nCount < minMultiply[i][j])
            minMultiply[i][j] = nCount;
    }
    return minMultiply[i][j];
}

void MatrixOrder(std::vector<int> matrix){
    int nLen = matrix.size();
    int **minMultiply = new int*[nLen];
    for (int i = 0; i < nLen; i++){
        minMultiply[i] = new int[nLen];
        for (int j = 0; j < nLen; ++j)
            minMultiply[i][j] = -1;
    }

    getMinMultiply(matrix, 1, nLen - 1, minMultiply);
    for (int i = 1; i < nLen - 1; ++i){
        for (int j = i + 1; j < nLen; ++j)
            printf("matrix %d multiply matrix %d min is %d\n", i, j, minMultiply[i][j]);
    }
}
*/

/*this is down to top*/
void MatrixOrder(std::vector<int> matrix){
    int nLen = matrix.size();
    int **minMultiply = new int*[nLen];
    for (int i = 0; i < nLen; i++){
        minMultiply[i] = new int[nLen];
    }
    for (int i = 0; i < nLen; ++i)
        minMultiply[i][i] = 0;
    
    for (int l = 2; l < nLen; ++l){
        for (int i = 1; i < nLen - l + 1; ++i){
            int j = i + l - 1;
            minMultiply[i][j] = 0x0fffffff;
            for (int k = i; k < j; ++k){
                int nM = minMultiply[i][k] + minMultiply[k + 1][j] + matrix[i - 1] * matrix[k] * matrix[j];
                if (nM < minMultiply[i][j])
                    minMultiply[i][j] = nM;
            }
        }
    }

    for (int i = 1; i < nLen - 1; ++i){
        for (int j = i + 1; j < nLen; ++j)
            printf("matrix %d multiply matrix %d min is %d\n", i, j, minMultiply[i][j]);
    }
}

/* normal recursion
std::string longestSubStr(std::string a, std::string b)
{
    if (a.empty() || b.empty())
        return "";

    std::string longest;
    char ac = *(--a.end());
    char bc = *(--b.end());
    if (ac == bc)
    {
        a.erase(--a.end());
        b.erase(--b.end());
        longest = longestSubStr(a, b);
        longest.push_back(ac);
    }
    else
    {
        a.erase(--a.end());
        std::string xl = longestSubStr(a, b);
        a.push_back(ac);

        b.erase(--b.end());
        std::string yl = longestSubStr(a, b);
        b.push_back(bc);

        if (xl.length() > yl.length())
            longest = xl;
        else
            longest = yl;
    }
    return longest;
}
*/

/*this is top to down dynamic programming
so it is only set in length longest subproblem
std::string getlongest(std::string a, std::string b, std::string** &length) {
    if (a.empty() || b.empty())
        return "";

    if (!length[a.length()-1][b.length()-1].empty()) {
        return length[a.length() - 1][b.length() - 1];
    }

    std::string longest;
    char ac = *(--a.end());
    char bc = *(--b.end());
    if (ac == bc) {
        a.erase(--a.end());
        b.erase(--b.end());
        longest = getlongest(a, b, length);
        longest.push_back(ac);
        a.push_back(ac);
        b.push_back(ac);
    }
    else {
        a.erase(--a.end());
        std::string xl = getlongest(a, b, length);
        a.push_back(ac);

        b.erase(--b.end());
        std::string yl = getlongest(a, b, length);
        b.push_back(bc);

        if (xl.length() > yl.length())
            longest = xl;
        else
            longest = yl;
    }
    length[a.length() - 1][b.length() - 1] = longest;
    return longest;
}

std::string longestSubStr(std::string a, std::string b) {
    std::string **length = new std::string*[a.length()];
    for (int i = 0; i < a.length(); i++) {
        length[i] = new std::string[b.length()];
        for (int j = 0; j < b.length(); ++j) {
            length[i][j] = "";
        }
    }
    getlongest(a, b, length);
    return length[a.length() - 1][b.length() - 1];
}
*/

/*this is down to top
in this solution, we get all i = 0 to a.length() j = 0 to b.length() longest subsequence
so it is different from top to down*/
std::string longestSubStr(std::string a, std::string b) {
    std::string **length = new std::string*[a.length() + 1];
    for (int i = 0; i <= a.length(); i++) {
        length[i] = new std::string[b.length() + 1];
        for (int j = 0; j <= b.length(); ++j) {
            length[i][j] = "";
        }
    }

    for (int i = 1; i <= a.length(); ++i) {
        for (int j = 1; j <= b.length(); ++j) {
            if (a[i-1] == b[j-1]) {
                length[i][j] = length[i - 1][j - 1] + a[i - 1];
            }
            else if (length[i-1][j].length() >= length[i][j-1].length()) {
                length[i][j] = length[i - 1][j];
            }
            else {
                length[i][j] = length[i][j - 1];
            }
        }
    }
    return length[a.length()][b.length()];
}

/*normal recursion
double getCost(std::vector<double> p, std::vector<double> q, int i, int j) {
    if (i == j + 1)
        return q[i - 1];

    double nCount = 0;
    for (int l = i; l <= j; ++l) {
        nCount += p[l];
        nCount += q[l - 1];
    }
    nCount += q[j];
    double nMin = 0x0fff;
    for (int l = i; l <= j; l++) {
        double dTemp = getCost(p, q, i, l - 1) + getCost(p, q, l + 1, j);
        if (nMin > dTemp)
            nMin = dTemp;
    }
    nCount += nMin;
    return nCount;
}
*/

/*this is top to down
it is similar to normal recursion,
add a double**optimal store i to j optimal tree 
double getCost(std::vector<double> p, std::vector<double> q, int i, int j, double** &optimal) {
    if (i == j + 1)
        return q[i - 1];

    if (optimal[i][j] != 0)
        return optimal[i][j];

    for (int l = i; l <= j; ++l) {
        optimal[i][j] += p[l];
        optimal[i][j] += q[l - 1];
    }
    optimal[i][j] += q[j];
    double nMin = 0x0fff;
    for (int l = i; l <= j; l++) {
        double dTemp = getCost(p, q, i, l - 1, optimal) + getCost(p, q, l + 1, j, optimal);
        if (nMin > dTemp)
            nMin = dTemp;
    }
    optimal[i][j] += nMin;
    return optimal[i][j];
}
*/

double optimalBST(std::vector<double> p, std::vector<double> q, int n) {
    double **optimal = new double*[n+1];
    double **w = new double*[n+1];
    for (int i = 0; i <= n; i++) {
        optimal[i] = new double[n+1];
        w[i] = new double[n+1];
        for (int j = 0; j <= n; j++) {
            optimal[i][j] = 0;
            w[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        optimal[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l < n; ++l) {
        for (int i = 1; i < n - l + 1; ++i) {
            int j = i + l - 1;
            optimal[i][j] = 0x0fff;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; ++r) {
                double dTemp = optimal[i][r - 1] + optimal[r + 1][j] + w[i][j];
                if (optimal[i][j] > dTemp) {
                    optimal[i][j] = dTemp;
                }
            }
        }
    }
    return optimal[1][5];
}

int maxValue(std::vector<int> v, std::vector<int> h, int n) {
    int nLen = v.size() - 1;
    std::vector<std::vector<int>> f(v.size(), std::vector<int>(n+1));
    for (int i = 0; i < n; ++i)
        f[0][i] = 0;

    for (int i = 1; i <= nLen; ++i) {
        f[i][0] = 0;
        for (int j = 1; j <= n; ++j) {
            if (j < h[i]) {
                f[i][j] = f[i - 1][j];
            }
            else {
                f[i][j] = std::max(f[i - 1][j], f[i - 1][j - h[i]] + v[i]);
            }
        }
    }
    return f[nLen][n];
}
