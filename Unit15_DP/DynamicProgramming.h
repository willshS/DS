#include <vector>

/******************************************************** 
    *  @function :  
    *  @brief    :  cut rod
    *  @Args     :  price[1] is price of rod whicth length is 1;
    *  @return   :  rod list
 
    *  @author   :  sgf
    *  @date	 :  2018/06/19 21:44
********************************************************/  
void cutRod(std::vector<int> price, int cutLen);

/******************************************************** 
    *  @function :  
    *  @brief    :  matrix chain order 
    *  @Args     :  matrix[0]*matrix[1] is first matrix, matrix[1]*matrix[2] is second matrix......
    *  @return   :  matrix node
 
    *  @author   :  sgf
    *  @date	 :  2018/06/20 21:27
********************************************************/  
void MatrixOrder(std::vector<int> matrix);

/******************************************************** 
    *  @function :  
    *  @brief    :  longest common subsequence problem
    it is similar to pick apple up from rectangle[x][y], 
    rectangle[i][j](0<i<=x, 0<j<=y) has zero or some apples.
    how we can has max apples from [0][0] to [x][y].
    *  @Args     :  
    *  @return   :  std::string longest subsequence
 
    *  @author   :  sgf
    *  @date	 :  2018/07/09 21:56
********************************************************/  
std::string longestSubStr(std::string a, std::string b);

/******************************************************** 
    *  @function :  
    *  @brief    :  optimal binary search tree 
    *  @Args     :  we will search some words, some are in the tree, some are not in the three
    words which in the tree, their probability is pi, 
    other words which don't in the tree, their probability are qi.
    *  @return   :  tree
 
    *  @author   :  sgf
    *  @date	 :  2018/07/12 21:48
********************************************************/  
double optimalBST(std::vector<double> pi, std::vector<double> qi, int n);

/******************************************************** 
    *  @function :  
    *  @brief    :  0-1 knapsack problem 
    *  @Args     :  v is value of goods, h is heavy of goods, n is knapsack capacity
    *  @return   :  max value.
 
    *  @author   :  sgf
    *  @date	 :  2018/07/26 20:59
********************************************************/  
int maxValue(std::vector<int> v, std::vector<int> h, int n); 