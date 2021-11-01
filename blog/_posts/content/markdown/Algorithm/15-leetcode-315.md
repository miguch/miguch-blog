---
date: 2021-2-18
tags: 
  - LeetCode
  - Algorithm
Author: Miguel Chen
---
# LeetCode 315. Count of Smaller Numbers After Self

## 题目

You are given an integer array *nums* and you have to return a new *counts* array. The *counts* array has the property where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

**Example:**

```
Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
```

## 分析

本题在 LeetCode 上的标签是BST，因此考虑使用二叉搜索树求解。对于二叉搜索树上的每一个节点，额外记录两个字段：`leftCount` 表示该节点左子树的节点数量以及在插入过程中该节点的累计重复数量，`duplicate`表示在插入过程中该节点的累计重复数量。

对于给出的数组，从尾部开始进行二叉树节点的插入，插入过程中同时计算已插入的节点中比新节点值小的节点数量，在插入过程中每访问一个节点，若该节点小于新节点，则访问该节点的右节点，否则访问左节点并将该节点`leftCount`加1（因为新节点必将成为该节点的新左子树节点），若该节点等于新节点，则`leftCount`与`duplicate`同时加1.

在插入过程中每次准备访问下一个右节点时都将当前节点的`leftCount+1`加至新节点的计数，以为此时当前节点的左子树所有节点和其本身都小于新节点，因此加入计数。若访问的节点与新节点相等，返回当前累计的计数与当前节点左子树计数的和减去累计的重复数。

## 代码

```cpp
class Solution {
public:
    struct node {
        node* left, *right;
        int val, leftCount, duplicate;
        node(int v, int lc) {
            val = v;
            leftCount = lc;
            duplicate = 0;
            left = right = nullptr;
        }
    };
    
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.empty()) return {};
        if (nums.size() == 1) return {0};
        int n = nums.size();
        vector<int> res(n, 0);
        node* root = new node(nums[n-1], 0);
        for (int i = n - 2; i >= 0; i--) {
            res[i] = insert(nums[i], root);
        }
        deleteTree(root);
        return res;
    }
    
    void deleteTree(node* root) {
        if (root != nullptr) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }
    
    int insert(int num, node* root, int lc = 0) {
        if (root->val > num) {
            root->leftCount += 1;
            if (root->left != nullptr) {
                return insert(num, root->left, lc);
            }
            root->left = new node(num, 0);
            return lc;
        } else if (root->val < num) {
            if (root->right != nullptr) {
                return insert(num, root->right, lc + 1 + root->leftCount);
            }
            root->right = new node(num, 0);
            return lc + 1 + root->leftCount;    
        } else {
            return lc + (root->leftCount++) - (root->duplicate++);
        }
    } 
    
    
};
```

提交至 LeetCode 运行时间为**28 ms**，高于64%的提交。