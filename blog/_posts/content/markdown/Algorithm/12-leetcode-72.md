---
date: 2021-2-18
tags:
  - LeetCode
  - Algorithm
Author: Mingtao Chen
---

# LeetCode 72. Edit Distance

## 题目

Given two words _word1_ and _word2_, find the minimum number of operations required to convert _word1_ to _word2_.

You have the following 3 operations permitted on a word:

1. Insert a character
2. Delete a character
3. Replace a character

**Example 1:**

```
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
```

**Example 2:**

```
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
```

## 分析

​ 这道题在课本上 6.3 也有出现，使用动态规划求解，其思路是将问题转换为求解 word1 的前 m 个字符可以最少通过几步修改变为 word2 的前 n 个字符，其中 m，n 分别为 word1，word2 的长度，将该问题成为 $E(i,j)$。然后可以考虑到三种情况，$E(i-1,j), E(i, j-1)$与$E(i-1,j-1)$ 。对于 word1[:i]，可以通过删除一个字符使问题变为$E(i-1,j)$, 或通过添加一个字符使问题变为$E(i, j-1)$. 若$word1[i] \neq word2[j]$ ，则可以通过替换一个字符使问题变为$E(i-1, j-1)$ , 否则可以直接匹配该位置。

​ 由以上思路可以构建出子问题表，大小为$(m+1,n+1)$ , 对于$E(i,j)$ , 其算法为：

$$E(i, j) = min\{E(i-1,j)+1, E(i, j-1)+1, E(i-1,j-1)+ diff(i,j)\}$$

​ 其中 $diff(i, j)$ 为 1，若 word1[i]=word2[j], 否则为 0.

### 代码

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int height = word1.size()+1, width = word2.size()+1;
        vector<vector<int>> dp(height, vector<int>(width, 0));
        for (int i = 0; i < height; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j < width; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i < height; i++) {
            for (int j = 1; j < width; j++) {
                int val = INT_MAX;
                if (val > dp[i-1][j] + 1) {
                    val = dp[i-1][j] + 1;
                }
                if (val > dp[i][j-1] + 1) {
                    val = dp[i][j-1] + 1;
                }
                if (val > dp[i-1][j-1] + (word1[i-1] != word2[j-1])) {
                    val = dp[i-1][j-1] + (word1[i-1] != word2[j-1]);
                }
                dp[i][j] = val;
            }
        }
        return dp[height-1][width-1];
    }
};
```

提交至 LeetCode 运行时间为**8 ms**。

此法的时间复杂度为$O(mn)$, 空间复杂度为$O(mn)$.

考虑到对每一个$E(i,j)$，实际只需要三个数据进行计算，因此可以将空间复杂度降为$O(n)$

代码如下：

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word2.size() == 0) return word1.size();
        int height = word1.size()+1, width = word2.size()+1;
        vector<int> dp(width,  0);
        for (int i = 1; i < width; i++) {
            dp[i] = i;
        }
        for (int i = 1; i < height; i++) {
            dp[0] = i - 1;
            int curr = i-1;
            for (int j = 1; j < width; j++) {
                int val = INT_MAX;
                if (val > dp[j-1]+1) {
                    val = dp[j-1]+1;
                }
                if (val > dp[j] + 1) {
                    val = dp[j] + 1;
                }
                if (val > curr + (word1[i-1] != word2[j-1])) {
                    val = curr + (word1[i-1] != word2[j-1]);
                }
                curr = dp[j];
                dp[j] = val;
            }
        }
        return dp[width-1];
    }
};
```

提交后运行时间为**4 ms**。
