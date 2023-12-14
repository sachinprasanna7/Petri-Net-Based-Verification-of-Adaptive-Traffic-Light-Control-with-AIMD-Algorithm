# Petri Net-Based Verification of Adaptive Traffic Light Control with AIMD Algorithm

This C++ program performs verification of a Petri Net representing a traffic control system with signalized intersections. The simulation includes reachability analysis, deadlock checks and boundedness analysis.

## Overview

The program defines a Petri Net using C++ structures for places, transitions, Petri Net, and a node in the Reachability Graph. It utilizes a novel algorithm based on Depth First Search (DFS) with backtracking to generate the Reachability Graph. 

The structures and algorithm details are provided in the pseudo code below.

### Defining the Required Structures


The structure of the Petri Net is defined using these structures. Places, transitions, and initial markings are initialized, and the Petri Net structure is set up.


```cpp
Structure Definition: Place
Attributes: name (string), tokens (int), incoming (vector of Transition), outgoing (vector of Transition)

Structure Definition: Transition
Attributes: name (string), incoming (vector of Place), outgoing (vector of Place)

Structure Definition: petriNet
Attributes: places (vector of Place), transitions (vector of Transition)

Structure Definition: Node
Attributes: name (string), neighbour (vector of Node*)
```


### Generating Reachability Graph

This algorithm utilizes DFS with backtracking to generate the Reachability Graph. It explores different markings and transitions in the Petri Net
```cpp
Function dfs(Node* node, set<string>&visited, set<Node*>&reachabilityGraph, petriNet &net)
    insert node->name into visited;
    insert node into reachabilityGraph;
    for each transition in net.transitions do
        if isTransitionEnabled(transition, net) then
            insert transition into visitedTransitions;
            vector<int>tokenCount(19);
            for int i = 0; i < net.places.size(); i++ do
                tokenCount[i] = net.places[i].tokens;
            string newName = transferTokens(transition, net);
            Node* newNode = new Node;
            newNode->name = newName;
            node->neighbour.push back(newNode);
            if not (exists newNode->name in visited) then
                dfs(newNode, visited, reachabilityGraph, net);
            for int i = 0; i < net.places.size(); i++ do
                net.places[i].tokens = tokenCount[i];
```



### Pseudocode for isTransitionEnabled Function

This function checks whether a transition can be fired based on the current marking in the Petri Net.
```cpp
Function isTransitionEnabled(Transition &transition, petriNet &net)
    for each place in transition.incoming do
        for int i = 0; i < net.places.size(); i++ do
            if net.places[i].name = place.name and net.places[i].tokens < 1 then
                return false;
    return true;
```


### Pseudocode for transferTokens Function

This function transfers tokens from incoming places to outgoing places during a transition.

```cpp 
Function transferTokens(Transition &transition, petriNet &net)
    for each place in transition.incoming do
        for int i = 0; i < net.places.size(); i++ do
            if net.places[i].name = place.name then
                net.places[i].tokens--;
    string name = "";
    for each place in transition.outgoing do
        for int i = 0; i < net.places.size(); i++ do
            if net.places[i].name = place.name then
                net.places[i].tokens++;
    for each place in net.places do
        name += to string(place.tokens);
    return name;
```

### Detecting Boundedness

This algorithm verifies the 1-bounded nature of the Petri Net.

``` cpp
bound ← 0;
foreach place in visited do
    for i ← 0 to place.length() do
        if place[i] - '0' > bound then
            bound ← place[i] - '0';
```



### Prerequisites

Before you begin, ensure you have the following installed:

1. **C++ compiler** (e.g., g++)
2. **Standard Template Library (STL)**



### Usage

1. **Copy Code:** Copy the source code.

2. **Compile the Program:**
    ```bash
    g++ -o traffic_simulator main.cpp
    ```

3. **Run the Executable:**
    ```bash
    ./traffic_simulator
    ```


