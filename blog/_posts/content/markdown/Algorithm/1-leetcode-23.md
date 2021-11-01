---
date: 2021-2-18
tags: 
  - LeetCode
  - Algorithm
Author: Miguel Chen
---


# 23. Merge k Sorted Lists

## 题目

Merge *k* sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

**Example:**

```c
Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
```

## Answer

### 1

受到归并排序中对两个已排序的序列合并操作的启发，第一种解法在每添加一个元素进入目标序列中时从所有剩余序列中找到头部数值最小的序列，将最小的头部节点加入目标序列，并将对应的序列头部移至其下一节点。每进行一次添加后排除掉剩余序列中的空序列。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* findAndPopSmallestNode(vector<ListNode*>& nodeList) {
        int smallest = INT_MAX, smallestNodeIndex = 0;
        for (int i = 0; i < nodeList.size(); i++) {
            auto node = nodeList[i];
            if (smallest > node->val) {
                smallest = node->val;
                smallestNodeIndex = i;
            }
        }
        auto res = nodeList[smallestNodeIndex];
        nodeList[smallestNodeIndex] = nodeList[smallestNodeIndex]->next;
        if (nodeList[smallestNodeIndex] == nullptr) {
            nodeList.erase(nodeList.begin() + smallestNodeIndex);
        }
        return res;
    }
    
    void clearEmptyList(vector<ListNode*>& nodeList) {
        for (int i = 0; i < nodeList.size(); i++) {
            if (nodeList[i] == nullptr) {
                nodeList.erase(nodeList.begin() + i);
                i--;
            }
        }
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> validNodes(lists);
        clearEmptyList(validNodes);
        if (validNodes.size() == 0) return nullptr;
        ListNode* head = findAndPopSmallestNode(validNodes);
        ListNode* tail = head;
        while (validNodes.size() > 1) {
            tail->next = findAndPopSmallestNode(validNodes);
            tail = tail->next;
        }
        tail->next = validNodes[0];
        return head;
    }
};
```

这种方法的缺点是时间复杂度较高，为 $O(nk)$ 在 leetcode 中提交后运行时间为 **124 ms** ，效果不太理想，因此给出下面的第二种做法：

### 2

第二种方法把合并序列的过程采用分治法，每一轮合并将剩余序列前半与后半每两个序列进行合并，不断重复直到剩下一个序列，使用这种方法可以使时间复杂度降至 $O(nlogk)$ , 在 LeetCode 中提交后运行时间为**20 ms** ，相较第一种方法有较大提升。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        ListNode* result = list1->val > list2->val ? list2 : list1;
        ListNode* tail = result;
        list1->val > list2->val ? list2 = list2->next : list1 = list1->next;
        while (list1 != nullptr && list2 != nullptr) {
            tail->next = list1->val > list2->val ? list2 : list1;
            list1->val > list2->val ? list2 = list2->next : list1 = list1->next;
            tail = tail->next;
        }
        if (list1) {
            tail->next = list1;
        }
        if (list2) {
            tail->next = list2;
        }
        return result;
    }
    
    void clearEmptyList(vector<ListNode*>& nodeList) {
        for (int i = 0; i < nodeList.size(); i++) {
            if (nodeList[i] == nullptr) {
                nodeList.erase(nodeList.begin() + i);
                i--;
            }
        }
    }
    
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> validNodes(lists);
        //clearEmptyList(validNodes);
        if (validNodes.size() == 0) return nullptr;
        int listCount = validNodes.size();
        while (listCount > 1) {
            int newCount = (listCount + 1) / 2;
            for (int i = 0; i < listCount / 2; i++) {
                validNodes[i] = mergeTwoLists(validNodes[i], validNodes[i + newCount]);
            }
            listCount = newCount;
        }
        return validNodes[0];
    }
};
```

