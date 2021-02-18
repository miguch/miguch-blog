---
date: 2021-2-18
tags: 
  - LeetCode
  - 算法
Author: Miguel Chen
---
# 778. Swim in Rising Water

##题目

On an N x N `grid`, each square `grid[i][j]` represents the elevation at that point `(i,j)`.

Now rain starts to fall. At time `t`, the depth of the water everywhere is `t`. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

You start at the top left square `(0, 0)`. What is the least time until you can reach the bottom right square `(N-1, N-1)`?

**Example 1:**

```
Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
```

**Example 2:**

```
Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
```

**Note:**

1. `2 <= N <= 50`.
2. grid[i][j] is a permutation of [0, ..., N*N - 1].

##  Answer

###1

第一种做法复杂度很高，对于每一个`t`，对所有可访问的节点的邻接节点进行检查，若该邻接节点数值小于`t` ，则将其标注为可访问节点，若没有邻接节点可访问，则 `t`变为未访问的邻接节点中的最小数值。

这种做法对于每一个`t`都要进行较多的操作，提交至 LeetCode 运行时间高达**124 ms**，效率非常差，因此下面将给出改进的其他方法。

```cpp
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), current = grid[0][0];
        const pair<int, int> directions[4] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
        auto length = vector<vector<int>>(n, vector<int>(n, -1));
        length[0][0] = grid[0][0];
        set<int> visited;
        visited.insert(0);
        while (length[n-1][n-1] == -1) {
            vector<int> toVisit;
            int min = INT_MAX;
            for (const auto &pos : visited) {
                bool clear = true;
                int x = pos % n, y = pos / n;
                for (const auto dir : directions) {
                    int newX = x + dir.first, newY = y + dir.second;
                    if (!isValidPosition(newX, newY, n)) continue;
                    if (current >= grid[newY][newX]) {
                        if (length[newY][newX] == -1) {
                            toVisit.push_back(newY * n + newX);
                            length[newY][newX] = current;
                        }
                    } else {
                        clear = false;
                        if (min > grid[newY][newX]) {
                            min = grid[newY][newX];
                        }
                    }
                }
                if (clear) visited.erase(pos);
            }
            for (const auto &pos : toVisit) visited.insert(pos);
            if (toVisit.empty()) current = min;
        }
        return length[n-1][n-1];
    }
    
    static bool isValidPosition(int x, int y, int n) {
        return x >= 0 && y >= 0 && y < n && x < n;
    }
};
```

### 2

第二种方法思路较简单，由题意可以知道`grid`中元素的数值范围为$[0, n\times n-1]$ ，因此对于该范围内的`t` 进行二分查找，使用 bfs 或 dfs 方法检查是否可以在当前`t`下找到一条从$(0, 0)$ 到$(n-1, n-1)$的路径即可。

**bfs 方法代码如下**

```cpp
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), lower = grid[0][0], higher = n * n - 1;
        while (lower < higher) {
            int depth = (higher - lower) / 2 + lower;
            unordered_set<int> visited;
            if (bfsCheck(grid, depth)) {
                higher = depth;
            } else {
                lower = depth + 1;
            }
        }
        return lower;
    }
    
    const pair<int, int> directions[4] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
    
    bool bfsCheck(const vector<vector<int>>& grid, int t) {
        unordered_set<int> visited;
        queue<int> unvisited;
        unvisited.push(0);
        visited.insert(0);
        while (!unvisited.empty()) {
            int pos = unvisited.front();
            unvisited.pop();
            int x = pos % grid.size(), y = pos / grid.size();
            for (auto dir : directions) {
                int newX = x + dir.first, newY = y + dir.second;
                if (isValidPosition(newX, newY, grid.size()) &&
                   grid[newY][newX] <= t && 
                   visited.count(newX + newY * grid.size()) == 0) {
                    if (newX == grid.size() - 1 && newY == grid.size() - 1) {
                        return true;
                    }
                    int newPos = newX + newY * grid.size();
                    unvisited.push(newPos);
                    visited.insert(newPos);
                }
            }
        }
        return false;
    }
    
    static bool isValidPosition(int x, int y, int n) {
        return x >= 0 && y >= 0 && y < n && x < n;
    }
};
```

提交后运行时间为**36 ms**

**dfs 方法代码如下**

```cpp
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), lower = grid[0][0], higher = n * n - 1;
        while (lower < higher) {
            int depth = (higher - lower) / 2 + lower;
            unordered_set<int> visited;
            if (dfsCheck(grid, depth, 0, 0, visited)) {
                higher = depth;
            } else {
                lower = depth + 1;
            }
        }
        return lower;
    }
    
    bool dfsCheck(const vector<vector<int>>& grid, int t, int x, int y, unordered_set<int> &visited) {
        const pair<int, int> directions[4] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
        visited.insert(x + y * grid.size());
        for (auto dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (isValidPosition(newX, newY, grid.size()) &&
                t >= grid[newY][newX] && 
                visited.count(newX + newY * grid.size()) == 0) {
                if (dfsCheck(grid, t, newX, newY, visited)) {
                    return true;
                }
            }
        }
        return visited.count(grid.size() * grid.size() - 1);
    }
    static bool isValidPosition(int x, int y, int n) {
        return x >= 0 && y >= 0 && y < n && x < n;
    }
};
```

提交后运行时间为**20 ms**。

### 3

第三种方法采用堆进行，本质上是要找出从起点到终点需要的最小的`t`值，将堆的排序规则设为数值最小的节点为堆顶，那么每一步从堆顶取出一个节点，将节点的未访问过的邻接节点放入堆中，如果堆顶节点的数值大于当前记录的`t`，则将`t`改为该数值。由于堆顶总是堆中数值最小的节点，我们可以保证当访问到终点时，记录到的`t`是所需要最小的`t`值。

代码如下：

```cpp
class Solution {
public:
    const pair<int, int> directions[4] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
    typedef pair<int, int> node;
    
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        priority_queue<node, vector<node>, function<bool(node,node)>> holding([](node n1, node n2) { return n1.second > n2.second;});
        unordered_set<int> visited;
        holding.push(make_pair(0, grid[0][0]));
        visited.insert(0);
        int res = 0;
        while (!holding.empty()) {
            auto current = holding.top();
            holding.pop();
            res = max(res, current.second);
            if (current.first == n * n - 1) return res;
            int x = current.first % n, y = current.first / n;
            for (auto dir : directions) {
                int newX = x + dir.first, newY = y + dir.second, newPos = newX + newY * n;
                if (!isValidPosition(newX, newY, n) || visited.count(newPos)) continue;
                holding.push(make_pair(newPos, grid[newY][newX]));
                visited.insert(newPos);
            }
        }
    }
    
    static bool isValidPosition(int x, int y, int n) {
        return x >= 0 && y >= 0 && y < n && x < n;
    }
};
```

提交后运行时间为**16 ms**。