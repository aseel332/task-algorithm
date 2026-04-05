#include <iostream>
#include <deque>
#include "../include/json.hpp"
#include "../include/graph.hpp"
#include "../include/task.hpp"
#include "../include/priority.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    try {
        // Read input JSON from stdin
        json input;
        cin >> input;
        map<int, Task> data;
        Graph dep(input["tasks"], data);
        dep.connect(input["dependencies"]);
        dep.topoSort();
        // Echo back the same JSON

        deque<int> topo = dep.get_Sorted();
        deque<int> ready;
        
        while(dep.get_degree(topo.front()) != 0){
            ready.push_back(topo.front());
            topo.pop_front();
        }

        Priority p(ready, data);

        

        json output = dep.topo_json();

        // Print to stdout
        cout << output.dump();



    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}