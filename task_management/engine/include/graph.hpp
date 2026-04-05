#ifndef GRAPH_HPP
#define GRAPH_HPP

#include<iostream>
#include<list>
#include<map>
#include<stack>
#include<vector>
#include<deque>
#include"../include/json.hpp"
#include"../include/task.hpp"

using namespace std;

class Graph{
  private: 
    map<int, list<int>> adjList;
    unordered_map<int, unordered_map<int, int>> weights;
    deque<int> topo;
    map<int,int> inDegree;
    //map<int, Task> data;
  public:
    Graph(nlohmann::json &tasks, map<int, Task> &data);
    void connect(nlohmann::json &depList);
    void add_edge(int u, int v, int lag);
    nlohmann::json to_json();
    void topoSort();
    void findTopoSort(int node, map<int, bool> &vis, stack<int> &st);
    nlohmann::json topo_json();
    int get_degree(int u);
    // Reduce Degree Function  
    int reduce_degree(int u);
    std::deque<int> get_Sorted();

    list<int> get_adjacency(int u);
};

#endif