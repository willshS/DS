#include "GreedAlgorithm.h"

/*this is DP solution down to top
int chooseActivity(std::vector<int> s, std::vector<int> f) {
    int nLen = s.size();
    std::vector<std::vector<int> > maxNums(s.size(), std::vector<int>(s.size()));
    for (int i = 0; i < nLen; ++i)
        maxNums[i][i] = 0;

    for (int l = 2; l < nLen + 1; ++l) {
        for (int i = 0; i < nLen - l + 1; ++i) {
            int j = i + l -1;
            maxNums[i][j] = 0;
            for (int x = i; x < j; ++x) {
                if (s[x] >= f[i] && f[x] <= s[j]) {
                    int temp = maxNums[i][x] + maxNums[x][j] + 1;
                    if (maxNums[i][j] < temp)
                        maxNums[i][j] = temp;
                }
            }
        }
    }
    return maxNums[0][nLen - 1] + 2;//add 0 and nLen-1 activity.
}
*/

/*this is greed algorithm
  in this way, we will choose the first finish activity,
  because it will leave the more time to choose activity.
  Notes: if the problem is as many as possible and 
  as the least free time of the room it will be wrong.
*/
int chooseActivity(std::vector<int> s, std::vector<int> f) {
    int nLen = s.size();
    int nCount = 1; //the s[0] activity add.
    int lastActivity = 0; //the last add activity
    for (int i = 1; i < nLen; ++i) {
        if (s[i] >= f[lastActivity]) {
            ++nCount;
            lastActivity = i;
        }
    }
    return nCount;
}