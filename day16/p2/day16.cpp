//this is wrong and a mess

//i am not goated enough to grasp what i need to do, very little experience with this flavor of coding
//looking at other solutions online i am pretty close but i ain't got the time to fix this mess

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<tuple>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<algorithm>

using namespace std;

string fileName = "input.txt";

pair<int,int> directions[4] = {{1,0},{0,1},{-1,0},{0,-1}};

int minCost(int x,int y, int dir, vector<vector<char>> &mat);

bool isValid(int x,int y,vector<vector<char>> map);

template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
          }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0>
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            hash_combine(seed, std::get<0>(tuple));
          }
        };


    template <typename ... TT>
    struct hash<std::tuple<TT...>> 
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {                                              
            size_t seed = 0;                             
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);    
            return seed;                                 
        }                                              

    };

int rX;
int rY;
pair<int,int> endC;
int dir = 0;
    
int main () {
    fstream file(fileName);
    string line;

    vector<vector<char>> mat;

    //get map
    while (getline(file, line)) {
        vector<char> row;  
        for (auto c : line) {
            if (c == 'S') {
                rX = row.size();
                rY = mat.size();
            }
            if (c == 'E') {
                endC.first = row.size();
                endC.second = mat.size();
            }
            row.push_back(c);
        }
        mat.push_back(row);
    } 

    //print
    

    cout << minCost(rX,rY, dir, mat) << endl;

    for (auto r : mat) {
        for (auto c : r) {
            cout << c << ' ';
        }
        cout << endl;
    }
}


int minCost(int x, int y, int dir, vector<vector<char>>& mat) {
    priority_queue<pair<int, tuple<int, int, int>>, vector<pair<int, tuple<int, int, int>>>, greater<>> pq;
    pq.push({0, {x, y, dir}});
    unordered_set<tuple<int, int, int>> visited;
    unordered_map<tuple<int, int, int>, int> cost_map;
    unordered_map<tuple<int, int, int>, tuple<int, int, int>> parent;
    vector<vector<bool>> onOptimalPath(mat.size(), vector<bool>(mat[0].size(), false));
    int lowestCost = INT_MAX;
    int count = 0;
    cost_map[{x, y, dir}] = 0;

    while (!pq.empty()) {
        auto [cost, state] = pq.top();
        pq.pop();

        if (visited.find(state) != visited.end()) continue;
        visited.insert(state);

        auto [cx, cy, cdir] = state;

        if (mat[cy][cx] == 'E') {
            lowestCost = min(lowestCost, cost);
        }

        // Explore possible moves
        for (int turn = -1; turn <= 1; ++turn) {
            int newDir = (cdir + turn + 4) % 4;
            int newCost = cost + (turn == 0 ? 1 : 1001);
            int nx = cx + directions[newDir].first;
            int ny = cy + directions[newDir].second;

            if (isValid(nx, ny, mat)) {
                auto newState = make_tuple(nx, ny, newDir);
                if (cost_map.find(newState) == cost_map.end() || newCost < cost_map[newState]) {
                    pq.push({newCost, newState});
                    cost_map[newState] = newCost;
                    parent[newState] = state;
                }
            }
        }
    }

    //optimal paths
    for (const auto& [state, cost] : cost_map) {
        if (cost == lowestCost) {
            auto curr = state;
            while (parent.find(curr) != parent.end()) {
                auto [px, py, _] = curr;
                onOptimalPath[py][px] = true;
                curr = parent[curr];
            }
        }
    }

    //update the maze with optimal path tiles
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].size(); ++j) {
            if (onOptimalPath[i][j] && mat[i][j] != 'S' && mat[i][j] != 'E') {
                count++;
                mat[i][j] = 'O';
            }
        }
    }

    return count;
}


bool isValid(int x,int y,vector<vector<char>> map) {
    if (y < 0 || y >= map.size() || x < 0 || x >= map[y].size()) {
            return 0;
        }
    else if(map[y][x] == '#') {
            return 0;
        }

    return 1;
}
        