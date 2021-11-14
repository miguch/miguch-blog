---
date: 2021-11-14
tags: 
  - LeetCode
  - Algorithm
  - Bit manipulation
Author: Miguel Chen
---
# 137. Single Number II
Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

 

Example 1:

Input: nums = [2,2,3,2]
Output: 3
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99
 

Constraints:

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each element in nums appears exactly three times except for one element which appears once.

## Answer

Assume num is 2(10)
1. For first time of 2: 
```
once: 00^10&11=10
twice: 00^10&01=00
```
2. Add a 1(01) that only appear once:
```
once: 10^01&11=11
twice: 00^01&00=00
```
3. For second time of 2:
```
once: 11^10&11=01
twice: 00^10&10=10
```
4. For third time of 2:
```
once: 01^10*01=01
twice: 10^10&10=00
```

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int once = 0;
        int twice = 0;

        for (int num : nums) {
            once = (once ^ num) & ~twice;
            twice = (twice ^ num) & ~once;
        }

        return once;
    }
};
```
