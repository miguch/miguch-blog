---
date: 2021-11-30
tags:
  - LeetCode
  - Algorithm
Author: Mingtao Chen
---

# 1573. Number of Ways to Split a String

Given a binary string `s` (a string consisting only of '0's and '1's), we can split `s` into 3 **non-empty** strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways `s` can be split such that the number of characters '1' is the same in s1, s2, and s3.

Since the answer may be too large, return it modulo 10^9 + 7.

**Example 1:**

```
Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"
```

**Example 2:**

```
Input: s = "1001"
Output: 0
```

**Example 3:**

```
Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.
"0|0|00"
"0|00|0"
"00|0|0"
```

**Example 4:**

```
Input: s = "100100010100110"
Output: 12
```

**Constraints:**

- `3 <= s.length <= 10^5`
- `s[i]` is `'0'` or `'1'`.

## Answer

Notice that there is only going to be a fixed number of 1s in each part for a string. So we just need to count the number zeros in between the parts to get the number of ways to split. Special case is a string with only 0s, the number of ways would be $1+2+...+(n-2)=\frac{(n-1)\times(n-2)}{2}$

```cpp
class Solution {
public:
    int numWays(string s) {
        int totalOnes = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                totalOnes++;
            }
        }
        if (totalOnes % 3 != 0) {
            return 0;
        }
        if (totalOnes == 0) {
            return (long long)(s.size() - 1) * (s.size() - 2) / 2 % int(1e9 + 7);
        }
        int firstOneIndex = 0, lastOneIndex = s.size() - 1;
        for (; s[firstOneIndex] == '0'; firstOneIndex++);
        for (; s[lastOneIndex] == '0'; lastOneIndex--);
        long long ways = 1;
        int consecutiveZeros = 0;
        int cumulativeOnes = 0;
        int partOnes = totalOnes / 3;
        for (int i = firstOneIndex; i < lastOneIndex + 1; i++) {
            if (s[i] == '1') {
                if (consecutiveZeros > 0) {
                    ways *= consecutiveZeros + 1;
                    ways %= int(1e9 + 7);
                    consecutiveZeros = 0;
                }
                cumulativeOnes++;
            } else if (cumulativeOnes % partOnes == 0) {
                consecutiveZeros++;
            }
        }
        return ways;
    }
};
```

Runtime: 36 ms

Memory: 13.8 MB
