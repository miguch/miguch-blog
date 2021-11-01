---
date: 2021-2-18
tags: 
  - LeetCode
  - Algorithm
Author: Miguel Chen
---

# 41. First Missing Positive

## 题目

Given an unsorted integer array, find the smallest missing positive integer.

**Example 1:**

```
Input: [1,2,0]
Output: 3
```

**Example 2:**

```
Input: [3,4,-1,1]
Output: 2
```

**Example 3:**

```
Input: [7,8,9,11,12]
Output: 1
```

**Note:**

Your algorithm should run in *O*(*n*) time and uses constant extra space.

## Answer

最开始可以想到的方法是从1开始对数组进行搜索，若搜到则加1搜索下一个正整数，但是这种方法的时间复杂度可以达到 $O(n^2)$，不符合题目中$O(n)$ 的要求。

第二种方法先将数组中所有非正数移动至数组末尾，然后从头遍历数组的正数部分，将数值小于其索引值+1的元素移动至其索引为其数值-1的位置。最后，数组正数部分第一个数值不等于其索引值+1的元素的索引值+1即为答案；若不存在这样的元素，则正数部分的元素数量+1则为答案。

## 代码

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        //First Swap all non-positive numbers to the end of the vector
        int lastPositiveIndex = nums.size() - 1;
        for (; lastPositiveIndex > 0; lastPositiveIndex--) {
            if (nums[lastPositiveIndex] > 0) break;
        }
        for (int i = 0; i < lastPositiveIndex; i++) {
            if (nums[i] <= 0) {
                int temp = nums[i];
                nums[i] = nums[lastPositiveIndex];
                nums[lastPositiveIndex] = temp;
                for (; lastPositiveIndex > 0; lastPositiveIndex--) {
                    if (nums[lastPositiveIndex] > 0) break;
                }
            }
        }
        for (int i = 0; i <= lastPositiveIndex; i++) {
            //Swap element so that its index is its value.
            while (nums[i] < i+1 && nums[nums[i]-1] != nums[i]) {
                int temp = nums[i];
                nums[i] = nums[nums[i]-1];
                nums[temp-1] = temp;
            }
        }
        for (int i = 0; i <= lastPositiveIndex; i++) {
            if (nums[i] != i+1) return i+1;
        }
        return lastPositiveIndex + 2;
    }
};
```

在 LeetCode 上提交运行通过，运行时间为**4 ms**。