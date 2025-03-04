---
date: 2021-11-14
tags:
  - LeetCode
  - Algorithm
  - LinkedList
  - Medium
Author: Mingtao Chen
---

# 138. Copy List with Random Pointer

A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Constraints:

0 <= n <= 1000
-10000 <= Node.val <= 10000
Node.random is null or is pointing to some node in the linked list.

## Answer

Use interweaving linkedlist, basically we create the copied node right next to the original node first, then we can know which copied node to set the random ptr to.

Time complexity: $O(n)$

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        Node* current = head;
        // make the copy right next to each node
        while (current) {
            Node* tmp = new Node(current->val);
            tmp->next = current->next;
            current->next = tmp;
            current = current->next->next;
        }
        current = head;
        // we now can get the which node the new ptr should point to
        while (current) {
            if (current->random) {
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }
        // seperate original list and copied list
        current = head;
        Node* res = head->next;
        while (current) {
            Node *next = current->next->next;
            if (next) {
                current->next->next = next->next;
            }
            current->next = next;
            current = next;
        }
        return res;
    }
};
```
