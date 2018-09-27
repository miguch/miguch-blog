# LeetCode 787. Cheapest Flights Within K Stops



## 题目

There are `n` cities connected by `m` flights. Each fight starts from city `u `and arrives at `v` with a price `w`.

Now given all the cities and fights, together with starting city `src` and the destination `dst`, your task is to find the cheapest price from `src` to `dst` with up to `k` stops. If there is no such route, output `-1`.

```
Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:
```
![1](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/02/16/995.png)
```
The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:
```
![2](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/02/16/995.png)
```
The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
```

**Note:**

- The number of nodes `n` will be in range `[1, 100]`, with nodes labeled from `0` to `n`` - 1`.
- The size of `flights` will be in range `[0, n * (n - 1) / 2]`.
- The format of each flight will be `(src, ``dst``, price)`.
- The price of each flight will be in the range `[1, 10000]`.
- `k` is in the range of `[0, n - 1]`.
- There will not be any duplicated flights or self cycles.

## Answer

这题其实就是在课本4.4描述的带权图最短路径问题的基础上加上了最多走 k 步的条件。这里也照着课本的方法给出 BFS 和 Dijkstra 算法的做法。

### bfs

bfs 根据起点与当前节点的节点数距离进行遍历，所以对于带权图不能直接使用，但是可以将边的权值转为两点之间的节点数量，即在每两个相邻节点间添加权值-1个"dummy nodes".

然而，这种方法的效率非常低，尤其当各边的权值较大且最大公约数较小时，过程将需要添加很多"dummy nodes"，造成运算时间大幅増长。因此，使用 BFS 编写的程序提交至 LeetCode 会导致超时。

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        map<int, vector<pair<int, int>>> edges;
        int weight_gcd = flights[0][2];
        for (const auto & edge : flights) {
            if (!edges.count(edge[0])) {
                edges[edge[0]] = vector<pair<int, int>>();
            }
            edges[edge[0]].push_back(make_pair(edge[1], edge[2]));
            weight_gcd = GCD(weight_gcd, edge[2]);
        }
        return bfs(n, edges, src, dst, K, weight_gcd);
    }
    
    int GCD(int a, int b) {
        if(b) while((a %= b) && (b %= a));
        return a + b;
    }
    
    int bfs(int n, map<int,vector<pair<int,int>>>& edges, int src, int dst, int K, int gcd) {
        int length = INT_MAX;
        queue<vector<int>> unvisited;
        unvisited.push(vector<int>{src, 0, 0, 0});
        while (!unvisited.empty()) {
            auto node = unvisited.front();
            unvisited.pop();
            if (node[1] == 0 && node[2] <= K) {
                for (const auto &adj : edges[node[0]]) {
                    if (adj.first == dst) {
                        length = min(length, node[3] + adj.second);
                    } else if (node[2] < K) {
                        unvisited.push(vector<int>{adj.first, adj.second, node[2] + 1, node[3] + adj.second});
                    }
                }
            } else if (node[1] > 0) {
                unvisited.push(vector<int>{node[0], node[1] - gcd, node[2], node[3]});
            } 
        }
        return length == INT_MAX ? -1 : length;
    }
};
```

### Dijkstra 算法

因为上面的 BFS 算法运算效率过低，下面改用 dijkstra 算法进行，使用堆存放要访问的顶点，每次从堆中取出距离最短的顶点，用该点更新其他顶点的距离，重复进行直到堆为空。

本题中因为有步数限制，所以在每次更新顶点距离时需要同时更新顶点与起点的步数。

代码如下:

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int, vector<pair<int, int>>> edges;
        for (const auto & edge : flights) {
            if (!edges.count(edge[0])) {
                edges[edge[0]] = vector<pair<int, int>>();
            }
            edges[edge[0]].push_back(make_pair(edge[1], edge[2]));
        }
        return dijkstra(n, edges, src, dst, K);
    }
    
    struct node {
        int pos, length, level;
        bool operator < (const node& rhs) const{
            return length < rhs.length;
        }
    };
    
    int dijkstra(int n, unordered_map<int,vector<pair<int,int>>>& edges, int src, int dst, int K) {
        priority_queue<node> heap;
        vector<int> lengths(n, INT_MAX);
        lengths[src] = 0;
        heap.push(node{src, 0, 0});
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            if (lengths[curr.pos] != curr.length) continue;
            for (const auto& adj : edges[curr.pos]) {
                if (lengths[adj.first] > curr.length + adj.second) {
                    lengths[adj.first] = curr.length + adj.second;
                    if (curr.level < K) {
                        heap.push(node{adj.first, lengths[adj.first], curr.level + 1});
                    }
                }
            }
        }
        return lengths[dst] == INT_MAX ? -1 : lengths[dst];
    }
};
```

提交至 LeetCode 后运行时间为8 ms，效率有了很大的提升。

