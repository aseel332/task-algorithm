#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include<fstream>
#include "../include/json.hpp"
#include "../include/graph.hpp"
#include "../include/task.hpp"
#include "../include/priority.hpp"
#include "../include/worker.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char* argv[]) {
    try {
        // Read input JSON from stdin
        json input;
        cin >> input;
        map<int, Task> data;
        vector<Worker> workers;

        // Get the command line csv file 
        string csvFile;
        if (argc > 1) {
            csvFile = argv[1];
        } else {
            throw runtime_error("CSV file not provided");
        }

        // Read workers from the CSV file
        ifstream file(csvFile);
        if (!file.is_open()) {
            throw runtime_error("Could not open CSV file");
        }
        string line;
        while (getline(file, line)) {
            if(line == "id,cost") continue; // skip header
            stringstream ss(line);
            string idStr, costStr;
            getline(ss, idStr, ',');
            getline(ss, costStr, ',');
            int id = stoi(idStr);
            float cost = stof(costStr);
            Worker w(id, cost, false, 0);
            workers.emplace_back(w);
        }
        file.close();


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

        int num_workers = workers.size();

        
        

        json output = dep.topo_json();

        // Print to stdout
        cout << output.dump();



    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}