# LeetCode 765. Couples Holding Hands

## 题目

N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A *swap* consists of choosing **any** two people, then they stand up and switch seats.

The people and seats are represented by an integer from `0` to `2N-1`, the couples are numbered in order, the first couple being `(0, 1)`, the second couple being `(2, 3)`, and so on with the last couple being `(2N-2, 2N-1)`.

The couples' initial seating is given by `row[i]` being the value of the person who is initially sitting in the i-th seat.

**Example 1:**

```
Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
```



**Example 2:**

```
Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.
```



**Note:**

1. `len(row)` is even and in the range of `[4, 60]`.
2. `row` is guaranteed to be a permutation of `0...len(row)-1`.



## 分析

​	这题一样是使用贪心算法的思想求解，对数组中的元素遍历，每次取两个元素，若第二个元素不与第一个元素匹配，则遍历数组后面一段找到与第一个元素匹配的元素，并将其与第二个元素交换位置。

代码如下：

```cpp
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int res = 0;
        for (int i = 0; i < row.size(); i += 2) {
            int curr = row[i];
            int target = curr % 2 ? curr - 1 : curr + 1;
            if (row[i+1] != target) {
                for (int j = i + 2; j < row.size(); j++) {
                    if (row[j] == target) {
                        swap(row[j], row[i+1]);
                        break;
                    }
                }
                res++;
            }
        }
        return res;
    }
};
```



​	LeetCode 上的提交中排在第一位的 example 用了一个并查集的 union-find 方法，将每一组配对的元素视为图上的一个结点，当两个不同配对的元素放在了一起时，用 union 将其在图中连出。当新加入的边会导致图出现环时，表明该边所代表的两个元素已在之前的交换中完成了配对了，不需要再进行交换。

代码如下：

```cpp
struct NF{
    vector<int> grp;
    int cnt; // number of connected edges
    NF(int len){
        this->cnt = 0;
        // Update the initial group 
        for(int i = 0; i < len; i++){
            this->grp.push_back(i);
        }
    }
    // find; 
    int find(int i){
        if(grp[i] != i){
            grp[i] = find(grp[i]);
        }else{
            return grp[i];
        }
        return grp[i];
    }
    // union;
    void unionFunc(int i , int j){
        int grp_i = this->find(i);
        int grp_j = this->find(j);
        if(grp_i != grp_j){            
            cnt++; // connect one edge;
            this->grp[grp_j] = grp_i;
        }
    }
};

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int len = row.size();
        NF new_np(len/2);
        for(int i = 0; i < len/2; i++){
            int a = row[i*2];
            int b = row[i*2 + 1];
            new_np.unionFunc(a/2, b/2);
        }
        return new_np.cnt; 
    }
};
```

