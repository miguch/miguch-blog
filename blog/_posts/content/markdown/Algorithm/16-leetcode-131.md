---
date: 2021-10-31
tags:
  - LeetCode
  - Algorithm
  - DFS
  - Backtracking
Author: Mingtao Chen
---

# 131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.

## Answer

使用 DFS+回溯，每步向前一个字符，若前段的字符串是回文则对后段递归

```cpp
class Solution {
public:
    bool isPalindrome(string& str, int start, int end) {
        int n = (end - start) / 2;
        for (int i = 0; i < n; i++) {
            if (str[i + start] != str[end - i - 1]) {
                return false;
            }
        }
        return true;
    }
    void helper(string& s, int start, int end, vector<vector<string>>& result, vector<string>& buf) {
        if (start >= end) {
            result.push_back(buf);
            return;
        }
        for (int i = 1; i <= end - start; i++) {
            if (isPalindrome(s, start, start + i)) {
                //prefix checked
                buf.push_back(s.substr(start, i));
                helper(s, start + i, end, result, buf);
                buf.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> buf;
        helper(s, 0, s.length(), res, buf);
        return res;
    }
};
```

复杂度： $O(2^N N)$ - 最差情况下 DFS 树的节点数 \* 检测回文
