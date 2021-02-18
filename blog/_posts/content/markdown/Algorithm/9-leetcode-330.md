---
date: 2021-2-18
tags: 
  - LeetCode
  - 算法
Author: Miguel Chen
---
# Leetcode 330. Patching Array

## 题目

Given a sorted positive integer array *nums* and an integer *n*, add/patch elements to the array such that any number in range `[1, n]`inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.

**Example 1:**

```
Input: nums = [1,3], n = 6
Output: 1 
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
```

**Example 2:**

```
Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
```

**Example 3:**

```
Input: nums = [1,2,2], n = 5
Output: 0
```



## 分析

​	这题可以使用贪心算法的思想进行求解。题目的要求是求出对给出的数组中需要添加多少个元素才能使其可以构成[1, n]区间的所有数值。

​	一个可以的做法是从1开始到 n，检查数组中的成员是否可以组成这个数，因为数组已经按照从小到大的顺序排序，我们可以从数组第一位元素开始检查。每一次检查若当前检查的数(设为 x)比数组检查到的对应元素(设索引为 i)大，则表明数组可以达到的区间至少为[1, nums[i] + x - 1]（因为此时数组必能组成[1, x-1]的数，所以可以组成x-num[i] 与 num[i]相加组成 x），所以下一次检查的 x 可以直接设为 nums[i] + x。若num[i] 大于 x，则表明此时数组无法组成 x，此时我们将 x 加入到数组中，那么此时数组可以组成的区间为[1, 2x-1]，所以下一次检查的 x 可以设为2x。

### 代码

```cpp
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int res = 0;
        long x = 1;
        for (int i = 0; x <= n;) {
            if (i < nums.size() && x >= nums[i]) {
                x += nums[i];
                i += 1;
            } else {
                x *= 2;
                res += 1;
            }
        }
        return res;
    }
};
```

代码中存储每次检查的数值的变量需使用 long 类型，因为测试样例中存在 n 为2147483647的样例，若 x 为 int 则当 x 每步乘2接近 n 时会直接溢出导致程序陷入死循环.