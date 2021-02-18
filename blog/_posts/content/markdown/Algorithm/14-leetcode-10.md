---
date: 2021-2-18
tags: 
  - LeetCode
  - 算法
Author: Miguel Chen
---
# LeetCode 10. Regular Expression Matching

## 题目

Given an input string (`s`) and a pattern (`p`), implement regular expression matching with support for `'.'` and `'*'`.

```
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
```

The matching should cover the **entire** input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters `a-z`.
- `p` could be empty and contains only lowercase letters `a-z`, and characters like `.` or `*`.

**Example 1:**

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

**Example 2:**

```
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
```

**Example 3:**

```
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
```

**Example 4:**

```
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
```

**Example 5:**

```
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
```

## 分析

本题使用动态规划求解，使用 $m\times n $大小的动态规划表，其中第（i, j）位元素的意义是 p 的前 i 位元素和 s 的前 j 位元素可以匹配。对于s 为空串时，p 为空串则匹配，p 不为空串时若 p[j] 为*则 $dp[j+1][0]=dp[j-1][0]$。s 不为空串时表的元素算法为如下：

$$dp[i+1][j+1] = \begin{cases} dp[i][j], \text{if }p[i]='.' \text{or }p[i]==s[j] \\ dp[i-1][j+1]\text{, if } p[i] = '*' \text{ and } p[i-1] \neq s[j] \text{ and } p[i-1] \neq '.'  \\ dp[i+1][j] || dp[i][j+1] || dp[i-1][j+1] \text{, if  } p[i] = '*' \text{ and } ( p[i-1] =s[j] \text{ or } p[i-1] = '.')\end{cases}$$

 解释如下：

- 当p[i]为 ‘.’ 或与 s[j] 相同时，代表匹配 s 中的一个字符，因此此时的状态与两字符串各退一个字符的状态相同。
- 当p[i]为'*'时，分为如下两种状态：
  1. 若此时p[i-1]与 s[j] 匹配，代表匹配 s 中的一个字符，此时可能为匹配了多个该字符或匹配到第一个该字符，若匹配了多个字符，则状态与 dp\[i+1\]\[j\] 时相同，若仅是匹配到了第一个该字符，则状态与 dp[i]\[j+1]相同, 若不将这个字符与*进行匹配，则目前的状态与dp[i-1][j+1\] 相同。
  2. 若此时p[i-1]与 s[j] 不匹配，则将*号视为匹配了空串，状态与dp[i-1][j+1\] 相同。

代码如下：

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;
        for (int i = 1; i < n; i++) {
            if (p[i] == '*') {
                dp[i+1][0] = dp[i-1][0];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                switch (p[i]) {
                    case '.':
                        dp[i+1][k+1] = dp[i][k];
                        break;
                    case '*':
                        if (p[i-1] == s[k] || p[i-1] == '.') {
                            dp[i+1][k+1] = dp[i+1][k] || dp[i][k+1] || dp[i-1][k+1];
                        } else {
                            dp[i+1][k+1] = dp[i-1][k+1];
                        }
                        break;
                    default:
                        if (s[k] == p[i]) {
                            dp[i+1][k+1] = dp[i][k];
                        }
                        break;
                }
            }
        }
        return dp[n][m];
    }
};
```

​	提交后运行时间为**8 ms**。

