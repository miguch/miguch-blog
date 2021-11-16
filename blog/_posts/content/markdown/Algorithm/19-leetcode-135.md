---
date: 2021-11-14
tags: 
  - LeetCode
  - Algorithm
Author: Miguel Chen
---
# 135. Candy
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104

## Answer
Use two runs to calculate the candies each child get.
First run ensures that children with higher rating get more than their left. Second run ensres that they get more than their right.

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() < 2) {
            return ratings.size();
        }
        vector<int> candies(ratings.size(), 0);
        candies[0] = 1;
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i-1]) {
                candies[i] = candies[i-1] + 1;
            } else {
                candies[i] = 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candies[i] = max(candies[i], candies[i+1] + 1);
            }
        }
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
```
