#ifndef PRIORITY_HPP
#define PRIORITY_HPP
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <deque>

#include "../include/task.hpp"
#include "../include/graph.hpp"



using namespace std;

struct Compare{
  bool operator()(const pair<int,int> &a, const pair<int, int> &b){
    return a.first > b.first;
  }
};

class Priority{
  priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    Compare
  > pq; 

  public: 
    Priority(deque<int> &ready, map<int, Task> &data);
    int top();
    int pop(Graph &g, deque<int> &topo, vector<Task> &data);
};

#endif