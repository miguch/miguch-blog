#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

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
        while (true) {
            auto current = holding.top();
            holding.pop();
            res = max(res, current.second);
            if (current.first == n * n - 1) return res;
            int x = current.first % 4, y = current.first / 4;
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

int main() {
    Solution s;
    vector<vector<int>> in{{0,2},{1,3}};
    cout << s.swimInWater(in) << endl;
    return 0;
}