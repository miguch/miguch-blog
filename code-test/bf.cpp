#include <iostream>
#include <vector>
#include <map>

using namespace std;

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
        map<int, int> lengths;
        queue<vector<int>> unvisited;
        unvisited.push(vector<int>{src, 0, 0});
        lengths[src] = 0;
        while (!unvisited.empty()) {
            auto node = unvisited.front();
            unvisited.pop();
            if (node[1] == 0 && node[2] < K) {
                for (const auto &adj : edges[node[0]]) {
                    if (lengths.count(adj.first) == 0) {
                        lengths[adj.first] = INT_MAX;
                    }
                    if (lengths[adj.first] > lengths[node[0]] + adj.second) {
                        lengths[adj.first] = lengths[node[0]] + adj.second;
                        unvisited.push(vector<int>{adj.first, adj.second, node[2] + 1});
                    }
                }
            } else {
                unvisited.push(vector<int>{node[0], node[1] - gcd, node[2]});
            } 
            
            
        }
        return lengths.count(dst) ? lengths[dst] : -1;
    }
};

int main() {

}