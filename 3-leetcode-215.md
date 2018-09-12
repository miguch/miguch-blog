# 215. Kth Largest Element in an Array

## 题目

Find the **k**th largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

**Example 1:**

```
Input: [3,2,1,5,6,4] and k = 2
Output: 5
```

**Example 2:**

```
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

**Note:** 
You may assume k is always valid, 1 ≤ k ≤ array's length.



## Answer

### 1

第一种方法就是直接的进行排序后返回第 k 大的元素，时间复杂度为排序的$O(nlogn)$。

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
```

提交至 LeetCode 运行时间8 ms。

### 2

第二种方法思想与快速排序类似，每一次操作从数组中选出一个数值，然后将数组分为三部分：左边为小于该数值的部分，中部为与该数值相等的部分，右部为大于该数值的部分。若要命中的数值的索引在相等的部分，则可直接返回这个数值。否则根据目标索引选择左半边或右半边进行下一步操作。

虽然这种方法在每一次选中的数值只能去除一个元素的极端情况下事件复杂度会达到$O(n^2)$ ，但是由于每次操作选中合适的元素的概率足够高，选中合适元素的操作次数期望值为2，因此令$T(n)$ 为运行时间期望值，则有$T(n) \leq T(3n/4) + O(n)$ .则可得此方法时间复杂度为$O(n)$

```cpp
class Solution {
public:
    
    vector<int> divide(vector<int>& nums, int startIndex, int endIndex) {
        int v = nums[startIndex + (endIndex - startIndex) / 2], vIndex = startIndex;
        int temp = nums[startIndex];
        nums[startIndex] = v;
        nums[startIndex + (endIndex - startIndex) / 2] = temp;
        int firstBigIndex = startIndex + 1;
        int firstEqualIndex = endIndex;
        for (int i = startIndex + 1; i < endIndex; i++) {
            if (nums[i] < v) {
                firstBigIndex++;
            } else {
                break;
            }
        }
        for (int i = firstEqualIndex - 1; i > firstBigIndex; i++) {
            if (nums[i] == v) {
                firstEqualIndex--;
            } else {
                break;
            }
        }
        for (int i = firstBigIndex; i < firstEqualIndex; i++) {
                if (nums[i] < v) {
                    int temp = nums[i];
                    nums[i] = nums[firstBigIndex];
                    nums[firstBigIndex] = temp;
                    firstBigIndex++;
                    i--;
                } else if (nums[i] == v) {
                    int temp = nums[i];
                    nums[i] = nums[firstEqualIndex-1];
                    nums[firstEqualIndex-1] = temp;
                    firstEqualIndex--;
                    i--;
                }
                if (i < firstBigIndex) i = firstBigIndex;
        }
        int equalSize = endIndex - firstEqualIndex, bigSize = firstEqualIndex - firstBigIndex;
        if (nums[firstEqualIndex - 1] <= v) bigSize = 0;
        for (int i = 0; i < min(bigSize, equalSize); i++) {
            int temp = nums[firstBigIndex + i];
            nums[firstBigIndex + i] = nums[endIndex - 1 - i];
            nums[endIndex - 1 - i] = temp;
        }
        nums[startIndex] = nums[firstBigIndex - 1];
        nums[firstBigIndex - 1] = v;
        return vector<int>{startIndex, firstBigIndex - 1, firstBigIndex + equalSize, endIndex};
    }
    int findKthLargest(vector<int>& nums, int k) {
        int targetIndex = nums.size() - k;
        bool finished = false;
        vector<int> indexes = divide(nums, 0, nums.size());
        while (!finished) {
            if (targetIndex >= indexes[1] && targetIndex < indexes[2]) {
                finished = true;
                return nums[targetIndex];
            } else if (targetIndex < indexes[1]) {
                indexes = divide(nums, indexes[0], indexes[1]);
            } else if (targetIndex >= indexes[2]) {
                indexes = divide(nums, indexes[2], indexes[3]);
            }
        }
    }
};
```

提交至 LeetCode 运行时间为**4 ms**。