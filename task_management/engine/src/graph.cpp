#include "../include/graph.hpp"
#include "../include/json.hpp"
#include "../include/task.hpp"
#include <queue>
#include <iostream>

using namespace std;

Graph::Graph(nlohmann::json &tasks, map<int, Task> &data){ 
  for (auto &a : tasks){
    int i = a["task_id"];
    adjList[i];
    inDegree[i] = 0;
    Task t(i, a["priority"], a["complexity_score"], a["preferred_role"], a["status"], a["complete"], a["profit"]);
    data.emplace(i, t);
  }
}


void Graph::connect(nlohmann::json &depList){ 
  for(auto &a : depList){
    int u = a["depends_on_task_id"];
    int v = a["task_id"];
    int lag = a["lag_min"];
    add_edge(u, v, lag);
  }
}

void Graph::add_edge(int u, int v, int lag){
  adjList[u].push_back(v);
  weights[u][v] = lag;
  inDegree[v]++;
};

nlohmann::json Graph::to_json(){
  nlohmann::json j; 
  for (auto& i : adjList) {
    j[to_string(i.first)] = i.second; 

  }
  return j;
};

void Graph::topoSort(){
  stack<int> st;
  map<int, bool> vis;

  for(auto &a: adjList){
    if(!vis[a.first]){
      findTopoSort(a.first, vis, st);
    }
  }

  while(!st.empty()){
    if(inDegree[st.top()] == 0){
      topo.push_front(st.top());
    }else{
      topo.push_back(st.top());
    }
    
    st.pop();
  }

  
}

void Graph::findTopoSort(int node, map<int, bool> &vis, stack<int> &st){
  vis[node] = true;

  for(auto a: adjList[node]){
    if(!vis[a]){
      findTopoSort(a, vis,st);
    }

  }
  st.push(node);
}


nlohmann::json Graph::topo_json(){
  nlohmann::json j;
  auto i = 0;
  for(auto a : topo){
    j[i++] = a;
  }
  return j;
}

int Graph::get_degree(int u){
  return inDegree[u];
}
std::deque<int> Graph::get_Sorted(){
  return topo;
}

int Graph::reduce_degree(int u){
  return --inDegree[u];
  
}

list<int> Graph::get_adjacency(int u){
  return adjList[u];
}