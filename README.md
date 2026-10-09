# Task Scheduling Engine

A task-scheduling engine written in **C++**, exposed through a **Node.js/Express** API. It takes a set of tasks with dependencies and priorities, orders them with a topological sort, and is being extended to assign the ready tasks to workers by priority and cost.

## How it works

1. A client sends tasks and dependencies as JSON to `POST /`.
2. The Express server writes the worker list to `public/workers.csv` and spawns the compiled C++ engine as a child process, piping the JSON to `stdin`.
3. The engine:
   - builds a **dependency graph** (adjacency lists + in-degrees),
   - runs a **topological sort** to get a valid execution order,
   - loads the tasks with no remaining dependencies into a **priority queue** keyed on task priority,
   - releases dependent tasks as their in-degree drops to zero.
4. The engine prints the result as JSON on `stdout`, and the API returns it.

Each task carries an id, priority, complexity score, preferred worker type, status, completion time and profit. Each worker has an id and a cost.

## Tech stack

C++17 (nlohmann/json), Node.js, Express, Make

## Getting started

```bash
git clone https://github.com/aseel332/task-algorithm.git
cd task-algorithm/task_management

# build the engine
cd engine && make && cd ..

# run the API
npm install
npm run dev     # http://localhost:3000
```

On Linux or macOS, point `src/services/cppEngine.js` at `engine/build/engine` instead of `engine.exe`.

## Status

Work in progress. The dependency graph, topological ordering and priority queue are implemented. Worker assignment that balances cost and priority is next.

## Project structure

```
task_management/
  engine/
    include/   graph, task, priority, worker headers (+ json.hpp)
    src/       graph.cpp, priority.cpp, task.cpp, workers.cpp, main.cpp
  src/         Express app, routes, and the service that runs the C++ engine
  public/      workers.csv input
```
