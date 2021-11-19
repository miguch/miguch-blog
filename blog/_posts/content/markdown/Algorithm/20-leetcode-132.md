---
date: 2021-11-14
tags: 
  - LeetCode
  - Algorithm
  - DP
  - Hard
Author: Miguel Chen
---

# 132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1
 

Constraints:

1 <= s.length <= 2000
s consists of lower-case English letters only.

## Answer
1. get number of cuts for trailing substring at each index. $O(N^3)$ complexity.
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
    int helper(string& str, int start, vector<int>& memo) {
        if (start >= str.size()) {
            return -1;
        }
        if (memo[start] != -1) {
            return memo[start];
        }
        memo[start] = INT_MAX;
        for (int i = start; i < str.size(); i++) {
            if (isPalindrome(str, start, i + 1)) {
                memo[start] = min(memo[start], helper(str, i + 1, memo) + 1);
            }
        }
        return memo[start];
    }
    
    int minCut(string s) {
        vector<int> memo(s.size(), -1);
        return helper(s, 0, memo);
    }
};
```
Runtime: 460 ms
Memory: 6.6 MB	

2. Use dynamic programming to get which substrings are palindrome first. Time complexity is reduced to $O(n^2)$ But also requires $O(n^2)$ space complexity.
```cpp
class Solution {
public:
    vector<vector<uint8_t>> getPalins(string& s) {
        vector<vector<uint8_t>> dp = vector<vector<uint8_t>>(s.size(), vector<uint8_t>(s.size(), 0));
        for (int i = 0; i < s.size(); i++) {
            dp[i][i] = 1;
        }
        for (int i = 0; i < s.size() - 1; i++) {
            dp[i][i+1] = s[i] == s[i+1] ? 1 : 0;
        }
        for (int subLength = 2; subLength < s.size(); subLength++) {
            for (int i = 0; i < s.size() - subLength; i++) {
                int j = i + subLength;
                dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1] ? 1 : 0;
            }
        }
        return dp;
    }
    int helper(string& str, int start, vector<int>& memo, vector<vector<uint8_t>>& palins) {
        if (start >= str.size()) {
            return -1;
        }
        if (memo[start] != -1) {
            return memo[start];
        }
        memo[start] = INT_MAX;
        for (int i = start; i < str.size(); i++) {
            if (palins[start][i]) {
                memo[start] = min(memo[start], helper(str, i + 1, memo, palins) + 1);
            }
        }
        return memo[start];
    }
    
    int minCut(string s) {
        vector<vector<uint8_t>> palins = getPalins(s);
        vector<int> memo(s.size(), -1);
        return helper(s, 0, memo, palins);
    }
};
```
Runtime: 60 ms
Memory: 14.9 MB