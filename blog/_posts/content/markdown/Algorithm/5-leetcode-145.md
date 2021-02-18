---
date: 2021-2-18
tags: 
  - LeetCode
  - 算法
Author: Miguel Chen
---

# LeetCode 145. Binary Tree Postorder Traversal

## 题目

Given a binary tree, return the *postorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
```

**Follow up:** Recursive solution is trivial, could you do it iteratively?

## Answer

本题要求使用迭代法进行二叉树的后序遍历，虽然标记的难度为 Hard，但是实际解法并不难，对照递归法的做法可以比较容易地编写出答案。使用一个栈来存放需要重新访问的节点，当当前访问的节点左右子树均为 null 或已访问过时，将其从栈中移除，同时将其数值存入要返回的数组中。

代码如下：

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        bool leftChecked = false;
        while (nodeStack.size() != 0) {
            auto currentNode = nodeStack.top();
            if (!leftChecked && currentNode->left != nullptr) {
                nodeStack.push(currentNode->left);
                continue;
            } else {
                leftChecked = true;
            }
            if (currentNode->right != nullptr) {
                nodeStack.push(currentNode->right);
                leftChecked = false;
            } else {
                nodeStack.pop();
                result.push_back(currentNode->val);
                while (nodeStack.size() != 0 && nodeStack.top()->right == currentNode) {
                    currentNode = nodeStack.top();
                    nodeStack.pop();
                    result.push_back(currentNode->val);
                }
            }
        }
        return result;
    }
};
```

提交至 LeetCode 后运行时间为**0 ms**。