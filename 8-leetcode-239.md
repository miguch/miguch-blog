# 239. Sliding Window Maximum

## [题目](https://leetcode.com/problems/sliding-window-maximum/)

Given an array *nums*, there is a sliding window of size *k* which is moving from the very left of the array to the very right. You can only see the *k* numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

**Example:**

```
Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

**Note:** 
You may assume *k* is always valid, 1 ≤ k ≤ input array's size for non-empty array.

**Follow up:**
Could you solve it in linear time?

## Answer

题目要求得到从左到右每一个 k 大小的 sliding window 中的最大元素。

看到最大元素最开始的想法就是使用堆，然而用堆仅添加 n 个元素的复杂度就达到了$O(nlogn)$ ,且每移动一步后将前一元素从堆中移除的复杂度也达到了$O(n)$, 所以使用堆将无法达到题目所要求的线性时间。

一个可以达到线性时间的做法是使用一个双向链表，链表中存放的是元素的index，链表头部是当前 window 最大元素的 index；每一步时若头部 index 已不在当前 window 范围内，则从链表中移除；对于要新加入的元素 index，先从链表尾部将所有小于新加入元素的对应 index 移除，再将新的 index 加入链表尾部。因为后加入的元素更晚从链表移除，我们可以保证那些被移除的元素肯定不会是后面的 window 中的最大元素。

代码如下：

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        list<int> indexes;
        for (int i = 0; i < nums.size(); i++) {
            if (i - k == indexes.front()) 
                indexes.pop_front();
            while (indexes.size() > 0 && nums[indexes.back()] < nums[i])
                indexes.pop_back();
            indexes.push_back(i);
            if (i >= k - 1) 
                res.push_back(nums[indexes.front()]);
        }
        return res;
    }
};
```

