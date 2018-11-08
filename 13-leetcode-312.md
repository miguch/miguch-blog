# LeetCode 312. Burst Balloons

## 题目

Given `n` balloons, indexed from `0` to `n-1`. Each balloon is painted with a number on it represented by array `nums`. You are asked to burst all the balloons. If the you burst balloon `i` you will get `nums[left] * nums[i] * nums[right]` coins. Here `left` and `right`are adjacent indices of `i`. After the burst, the `left` and `right` then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

**Note:**

- You may imagine `nums[-1] = nums[n] = 1`. They are not real therefore you can not burst them.
- 0 ≤ `n` ≤ 500, 0 ≤ `nums[i]` ≤ 100

**Example:**

```
Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
```

## 分析

本题在 LeetCode 中被归属在动态规划的 tag 下面，然而一个动态规划并不是那么第一眼就很容易可以想到的做法。

首先考虑到若是按从0开始去破坏每个气球的话，需要对每一步的各种情况都展开为更多的情况，复杂度很高。因此考虑从所有气球都是已经处于破裂状态开始逆向求解，此时第一个被还原的气球的硬币必定是$nums[-1] \times nums[i] \times nums[n]$ ,   然后就可以将被还原气球的左边和右边分开进行还原，从而分治完成求解，每一次还原完成后总数值最大的气球。

代码如下：

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> ballons(nums.size() + 2, 1);
        copy(nums.begin(), nums.end(), ballons.begin() + 1);
        results = vector<vector<int>>(nums.size() + 2, vector<int>(nums.size() + 2, 0));
        return divide(ballons, 0, nums.size() + 1);
    }
    vector<vector<int>> results;
    int divide(const vector<int> & ballons, int l, int r) {
        if (results[l][r] > 0) return results[l][r];
        for (int i = l+1; i < r; i++) {
            results[l][r] = max(results[l][r], ballons[i] * ballons[l] * ballons[r] + divide(ballons, l, i) + divide(ballons, i, r));
        }
        return results[l][r];
    }
};
```

提交后运行时间为**16 ms**。

根据分治的做法，可以将其改写为如下的动态规划做法，其中使用的表中元素(i, j) 所代表的是戳破第i+1 到第j-1个气球时所能获得的最大硬币数，因此算法对每一个元素的求解是找出其与可能的左右气球相乘后加上左右气球的最大硬币数的值。

代码如下：

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> ballons(nums.size() + 2, 1);
        copy(nums.begin(), nums.end(), ballons.begin() + 1);
        auto results = vector<vector<int>>(nums.size() + 2, vector<int>(nums.size() + 2, 0));
        
        for (int i = 0; i < nums.size() ; i++) {
            for (int l = 0; l < nums.size() - i; l++) {
                int r = l + i + 2;
                for (int k = l + 1; k < r; k++) {
                    results[l][r] = max(results[l][r], ballons[k] * ballons[l] * ballons[r] + results[l][k] + results[k][r]);
                }
            }
        }
        return results[0][nums.size()+1];
    }
};
```

提交后运行时间为**12 ms**。

