---
date: 2021-2-18
tags:
  - LeetCode
  - Algorithm
Author: Mingtao Chen
---

# 143. Reorder List (Go 实现)

## 题目

Given a singly linked list $$L: L_0→L_1→…→L_{n-1}→L_n$$,
reorder it to: $$L_0→L_n→L_1→L_{n-1}→L_2→L_{n-2}→…$$

You may **not** modify the values in the list's nodes, only nodes itself may be changed.

**Example 1:**

```
Given 1->2->3->4, reorder it to 1->4->2->3.
```

**Example 2:**

```
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
```

## Answer

最近开始重新学习 Go 语言，所以本题试着用 Go 语言来做。

题目要求将头结点后按照倒数第一个元素，第二个元素，倒数第二个元素，第三个元素这样排下去。具体做法就是先找出中间的节点，方法是使用两个指针分别每步走 1 和 2 个节点向前遍历，走 2 步的节点到达末尾时走 1 步的节点就处在链表中间位置；第二步是将链表的后半部分翻转，以方便第三步的合并。链表翻转的具体方法是从头开始对于链表中的每一个节点将其 next 指向前一节点（若无则置为`nil` ）。第三步就将前两步获得的两半链表进行合并即可获得结果。

具体代码实现如下：

```go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reorderList(head *ListNode)  {
    if head == nil || head.Next == nil{
        return
    }
    //Part One: Find the node that can split the list in two
    stepOne := head.Next
    stepTwo := stepOne
    for stepTwo != nil && stepTwo.Next != nil && stepTwo.Next.Next != nil {
        stepOne = stepOne.Next
        stepTwo = stepTwo.Next.Next
    }
    //Part Two: Reverse the second half of the list
    secondHalf := reverseList(stepOne.Next)
    //Part Three: join the two parts of the list.
    stepOne.Next = nil
    temp := head
    for secondHalf != nil && temp.Next != nil {
        hold := temp.Next
        temp.Next = secondHalf
        secondHalf = secondHalf.Next
        temp.Next.Next = hold
        temp = hold
    }
    if secondHalf != nil {
        temp.Next = secondHalf
    }
}

func reverseList(head *ListNode) *ListNode {
    if head == nil {
        return nil
    }
    var prev *ListNode
    temp := head
    var tempNext *ListNode
    for temp != nil {
        tempNext = temp.Next
        temp.Next = prev
        prev = temp
        temp = tempNext
    }
    return prev
}
```

提交至 LeetCode 的运行时间为 **12 ms**，属于所有提交中最快的一部分。
