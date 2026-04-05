#include "../include/priority.hpp"
#include "../include/task.hpp"
#include "../include/graph.hpp"
#include<deque>
#include <iostream>
#include <algorithm>

// here topo is only till the in degree is zero 
Priority::Priority(deque<int> &ready, map<int, Task> &data){
  for(auto i : ready){
     pq.push(make_pair(data[i].priority, i));
  }
}

int Priority::top(){
  return pq.top().second;
}

int Priority::pop(Graph &g, deque<int> &topo, vector<Task> &data){
  pair<int,int> p = pq.top();
  pq.pop();
  int u = p.second;

  // get adacency 
  list<int> adj = g.get_adjacency(u);

  for(auto i : adj){
    int d = g.reduce_degree(i);
    if(d == 0){
      pq.push(make_pair(data[i].priority, i));
      auto it = find(topo.begin(), topo.end(), i);
      topo.erase(it);
    }
  }
  return u;
} 



