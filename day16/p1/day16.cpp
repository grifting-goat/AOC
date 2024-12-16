//i now have done a dijikstras .. i dont want to any more
//the tuple has i stole from internets, i didnt need to use tuples i just wanted to learn them


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<tuple>
#include<unordered_set>
#include<unordered_map>

using namespace std;

string fileName = "input.txt";

pair<int,int> directions[4] = {{1,0},{0,1},{-1,0},{0,-1}};

int minCost(int x,int y, int dir, vector<vector<char>> mat);

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
            row.push_back(c);
        }
        mat.push_back(row);
    } 

    //print
    for (auto r : mat) {
        for (auto c : r) {
            cout << c << ' ';
        }
        cout << endl;
    }

    cout << minCost(rX,rY, dir, mat);
}


int minCost(int x,int y, int dir, vector<vector<char>> mat) {
    priority_queue<pair<int, tuple<int,int,int>>, vector<pair<int, tuple<int,int,int>>>, greater<pair<int, tuple<int, int,int>>>> pq;
    pq.push({0,{x,y,dir}});
    unordered_set<tuple<int, int, int>> visited;
    unordered_map<tuple<int, int, int>, int, hash<tuple<int, int, int>>> cost_map;
    cost_map[{x, y, dir}] = 0;

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        
        if (visited.find(top.second) != visited.end()) continue;

        visited.insert(top.second);

        //nameing   
        pair <int,int> coors = {get<0>(top.second), get<1>(top.second)};
        dir = get<2>(top.second);
        pair<int,int> newD = directions[dir];
        int dx = coors.first;
        int dy = coors.second;
        int cost = top.first;
        //cout << "<" << dx << ", " << dy << "> with cost:" << top.first << endl;


        //did win?
        if (mat[dy][dx] == 'E') {
            return cost;
        }

        //forward
        if (isValid(dx + directions[dir].first, dy + directions[dir].second, mat)) {
            int new_cost = cost + 1;
            if (cost_map.find({dx + directions[dir].first, dy + directions[dir].second, dir}) == cost_map.end() || new_cost < cost_map[{dx + directions[dir].first, dy + directions[dir].second, dir}]) {
                pq.push({new_cost,{dx + directions[dir].first, dy + directions[dir].second,dir}});
                cost_map[{dx + directions[dir].first, dy + directions[dir].second, dir}] = new_cost;
            }
        }

        //counter
        newD = directions[(dir + 1)%4];
        int new_cost = cost + 1001;
        if (isValid(dx + newD.first, dy + newD.second, mat)) {
            if (cost_map.find({dx + newD.first, dy + newD.second, (dir + 1) % 4}) == cost_map.end() || new_cost < cost_map[{dx + newD.first, dy + newD.second, (dir + 1) % 4}]) {
                pq.push({new_cost, {dx + newD.first, dy + newD.second, (dir + 1) % 4}});
                cost_map[{dx + newD.first, dy + newD.second, (dir + 1) % 4}] = new_cost;
            }
        }

        //clockwise
        new_cost = cost + 1001;
        newD = directions[(dir - 1 + 4) % 4]; // Ensure we get a positive modulo result
        if (isValid(dx + newD.first, dy + newD.second, mat)) {
            if (cost_map.find({dx + newD.first, dy + newD.second, (dir - 1 + 4) % 4}) == cost_map.end() || new_cost < cost_map[{dx + newD.first, dy + newD.second, (dir - 1 + 4) % 4}]) {
                pq.push({new_cost, {dx + newD.first, dy + newD.second, (dir - 1 + 4) % 4}});
                cost_map[{dx + newD.first, dy + newD.second, (dir - 1 + 4) % 4}] = new_cost;
            }
        }

    }

    return -1;
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
        