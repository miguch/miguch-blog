---
date: 2021-2-18
tags: 
  - LeetCode
  - 算法
Author: Miguel Chen
---
# 115. Distinct Subsequences

## 题目

Given a string **S** and a string **T**, count the number of distinct subsequences of **S** which equals **T**.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, `"ACE"` is a subsequence of `"ABCDE"` while `"AEC"` is not).

**Example 1:**

```
Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:

As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
```

**Example 2:**

```
Input: S = "babgbag", T = "bag"
Output: 5
Explanation:

As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
```

## 分析

题目的意思是要求出对于一个字符串 S 有几种删除字符的方法使得删除后的字符串为 T。

一种做法是使用递归，对于输入的 S 和 T 字符串的第一个字符若匹配，则可以有删去和不删去两种情况，那么此时的结果就是对这两种情况递归执行该函数的结果和；若第一个字符不匹配，则此时只能去除该字符，结果为对去除该字符的 S 与没有去除该字符的 T 执行函数的结果。

这种方法的代码如下（使用备忘录）：

```cpp
class Solution {
public:
    map<pair<int, int>, int> distinct;
    
    int numDistinct(string s, string t, int sIndex = 0, int tIndex = 0) {
        auto p = make_pair(sIndex, tIndex);
        if (distinct.count(p)) return distinct[p];
        if (s == t) return 1;
        if (s.size() < t.size()) return 0;
        int res;
        if (s[0] == t[0]) {
            res = numDistinct(s.substr(1), t.substr(1), sIndex + 1, tIndex + 1) + numDistinct(s.substr(1), t, sIndex + 1, tIndex);
        } else {
            res = numDistinct(s.substr(1), t, sIndex + 1, tIndex);
        }
        distinct[p] = res;
        return res;
    }
};
```

提交运行后耗时达到了**656 ms**，在分布表上都不显示了。所以还是不足以接受啊。

根据以上的思路其实可以想到使用动态规划进行求解，使用了一个len(t)+1长度的数组作为状态表dp，dp[i]表示的是从 S 到 T[0:i+1] 有多少种方法。当 len(t) > len(s) 时结果为0，当 S 与 T 相同时结果为1。

对 S 中的每一个字符对 T 进行遍历，若此时 S 的字符与 T 的字符匹配，则将dp 中对应位置加1，表示此时可有额外的一种方法进行删除，当出现dp[k]为0时（k 为此时循环到的 T 的字符的索引），直接进入下一个 S 的字符循环，因为dp[k]为0代表此时 S所循环到的位置无法组成 T 后续的字符串。



代码如下：

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s == t) return 1;
        if (s.size() < t.size()) return 0;
        vector<int> dp(t.size() + 1, 0);
        dp[0] = 1;
        
        for (int i = 0; i < s.size(); i++) {
            int pre = 1;
            for (int k = 0; k < t.size(); k++) {
                int curr = dp[k+1];
                if (s[i] == t[k]) {
                    dp[k+1] += pre;
                }
                pre = curr;
                if (pre == 0) break;
            }
        }
        return dp[t.size()];
    }
};
```

提交后运行时间为**0 ms**。