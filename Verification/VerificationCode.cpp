#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <utility>

using namespace std;


struct Transition;

struct Place {
    string name;
    int tokens; 
    vector <Transition> incoming;
    vector <Transition> outgoing;
};

struct Transition {
    string name;
    vector <Place> incoming;
    vector <Place> outgoing;

     bool operator<(const Transition& other) const {
        return name < other.name;
    }
};

struct PetriNet {
    vector<Place> places;
    vector<Transition> transitions;
};

struct Node{
    string name;
    vector <Node*> neighbour;
};



//Begin Functions
bool isTransitionEnabled(Transition &transition, PetriNet &net){
    
    for (auto &place : transition.incoming) {
        // Check if the place has enough tokens
        for(int i = 0 ; i < net.places.size() ; i++){
            if((net.places[i].name == place.name) && (net.places[i].tokens < 1)){
                return false;
            }
        }
    }

    return true;
}

string transferTokens(Transition &transition, PetriNet &net){

    for (auto &place : transition.incoming) {
        for(int i = 0 ; i < net.places.size(); i++){
            if(net.places[i].name == place.name){
                net.places[i].tokens--;
            }
        }
    }

    string name = "";

    for (auto &place : transition.outgoing) {
        for(int i = 0 ; i < net.places.size() ; i++){
            if(net.places[i].name == place.name){
                net.places[i].tokens++;
            }
        }
    }

    //iterate through the places vector in the PetriNet structure to give it a name
    for (auto &place : net.places) {
        name += to_string(place.tokens);
    }

    return name;
}

set <Transition> visitedTransitions;

void dfs(Node* node, set <string> &visited, set <Node*> &reachabilityGraph, PetriNet &net){

    visited.insert(node->name);
    reachabilityGraph.insert(node);

    for (auto &transition : net.transitions) {
        if (isTransitionEnabled(transition, net)) {

            //Store the transition in the visited transitions set  
            visitedTransitions.insert(transition);

            //Save Current State to backtrack later
            vector <int> tokenCount(19);

            for(int i = 0 ; i < net.places.size() ; i++){
                tokenCount[i] = net.places[i].tokens;
            }

            // Transfer tokens
            string newName = transferTokens(transition, net);

            // Create a new node
            Node* newNode = new Node;
            newNode->name = newName;

            // Add the new node to the neighbour of the current node
            node->neighbour.push_back(newNode);
            
            // Check if the new node has already been visited
            if (visited.find(newNode->name) == visited.end()) {
                dfs(newNode, visited, reachabilityGraph, net);
            }

            //return state
            for(int i = 0 ; i < net.places.size() ; i++){
                net.places[i].tokens = tokenCount[i];
            }

        }
    }
}


void printReachabilityGraph(set<Node*> reachabilityGraph) {

    // Printing the adjacency list of the reachability graph
    for (auto& node : reachabilityGraph) {
        cout << node->name << " -> [";

        // Iterating over neighbors
        auto it = node->neighbour.begin();
        while (it != node->neighbour.end()) {
            cout << (*it)->name;

            // Checking if it's the last element before printing the comma
            if (++it != node->neighbour.end()) {
                cout << ", ";
            }
        }

        cout << "]";
        cout << endl;
    }

    // Printing the number of nodes in the reachability graph
    cout << "\nNumber of nodes in the reachability graph -> " << reachabilityGraph.size() << endl;
}



void checkDeadlock(set <Node*> reachabilityGraph){

    for (auto &node : reachabilityGraph) {
        int count = 0;

        for(auto adj : node->neighbour){
            if(node->name != adj->name){
                count++;
            }
        }

        if(count == 0){
            cout<<"There is a Deadlock Present in the Petri Net";
            return ;
        }
    }

    cout<<"There is no Deadlock Present in the Petri Net"<<endl;
    

}


void checkBoundedness(set <string> &visited){

    int bound = 0;

    for(auto &place : visited){
        for(int i = 0 ; i < place.length() ; i++){
            if(place[i] - '0' > bound){
                bound = place[i] - '0';
            }
        }
    }

    //Printing the boundedness of the Petri Net
    cout<<"\nThe Petri Net is "<<bound<<" bounded"<<endl;

}


void verifyPlaceInvariant1(set <string> &visited){

    // P-Invariant1: PL1+PL2+PL3=1

    //Looping through all possible markings of Petri Net
    for(auto &place : visited){
        
        //Checking that marking to see if it holds
        int count = (place[3] - '0') + (place[4] - '0') + (place[5] - '0');

        if(count != 1){
            cout<<"P-Invariant is not satisfied!\n";
            return ;
        }
    }

    cout<<"\nP-Invariant1: PL1+PL2+PL3=1 is verified!";

}

void verifyPlaceInvariant2(set <string> &visited){

    // P-Invariant2: Green+Red=1

    //Looping through all possible markings of Petri Net
    for(auto &place : visited){
        
        //Checking that marking to see if it holds
        int count = (place[16] - '0') + (place[17] - '0');

        if(count != 1){
            cout<<"P-Invariant is not satisfied!\n";
            return ;
        }
    }
    
    cout<<"\nP-Invariant2: Green+Red=1 is verified!";

}

void verifyPlaceInvariant3(set <string> &visited){

    // P-Invariant3: T48+T58+T68+T78+T88=1

    //Looping through all possible markings of Petri Net
    for(auto &place : visited){
        
        //Checking that marking to see if it holds
        int count = (place[6] - '0') + (place[7] - '0') + (place[8] - '0') + (place[9] - '0') + (place[10] - '0');

        if(count != 1){
            cout<<"P-Invariant is not satisfied!\n";
            return ;
        }
    }
    
    cout<<"\nP-Invariant3: T48+T58+T68+T78+T88=1 is verified!";

}

void verifyPlaceInvariant4(set <string> &visited){

    // P-Invariant4: L1+L2+L3+PL1+PL2+PL3+T4+T5+T6+T7+T8+T4_+T5_+T6_+T7_+T8_+2∗(Red)+Green+Picker=4

    //Looping through all possible markings of Petri Net
    for(auto &place : visited){
        
        //Checking that marking to see if it holds
        int count = 0;

        for(int i = 0 ; i < place.size() ; i++){

            if(i == 17){
                count += (2*(place[i] - '0'));
            }

            else{
                count += (place[i] - '0');
            }
        }


        if(count != 4){
            cout<<"\nP-Invariant is not satisfied!\n";
            return ;
        }
    }
    
    cout<<"\nP-Invariant4: L1+L2+L3+PL1+PL2+PL3+T4+T5+T6+T7+T8+T4_+T5_+T6_+T7_+T8_+2*(Red)+Green+Picker=4 is verified!";

}

int main(){

    PetriNet net;

    //Defining All Places, with their initial tokens
    Place l1 = {"l1", 1};
    Place l2 = {"l2", 0};
    Place l3 = {"l3", 0};
    Place pl1 = {"pl1", 1};
    Place pl2 = {"pl2", 0};
    Place pl3 = {"pl3", 0};

    Place t4 = {"t4", 1};
    Place t5 = {"t5", 0};
    Place t6 = {"t6", 0};
    Place t7 = {"t7", 0};
    Place t8 = {"t8", 0};

    Place t4_ = {"t4_", 0};
    Place t5_ = {"t5_", 0};
    Place t6_ = {"t6_", 0};
    Place t7_ = {"t7_", 0};
    Place t8_ = {"t8_", 0};

    Place green = {"green", 1};
    Place red = {"red", 0};
    Place picker = {"picker", 0};

    //Defining All Transitions
    Transition T114 = {"T114", {l1, pl1, t4}, {pl1, t4, t4_}};
    Transition T115 = {"T115", {l1, pl1, t5}, {pl1, t4, t4_}};
    Transition T116 = {"T116", {l1, pl1, t6}, {pl1, t7, t7_}};
    Transition T117 = {"T117", {l1, pl1, t7}, {pl1, t7, t7_}};
    Transition T118 = {"T118", {l1, pl1, t8}, {pl1, t8, t8_}};

    Transition T124 = {"T124", {l1, pl2, t4}, {pl1, t5, t5_}};
    Transition T125 = {"T125", {l1, pl2, t5}, {pl1, t6, t6_}};
    Transition T126 = {"T126", {l1, pl2, t6}, {pl1, t6, t6_}};
    Transition T127 = {"T127", {l1, pl2, t7}, {pl1, t7, t7_}};
    Transition T128 = {"T128", {l1, pl2, t8}, {pl1, t8, t8_}};

    Transition T134 = {"T134", {l1, pl3, t4}, {pl1, t6, t6_}};
    Transition T135 = {"T135", {l1, pl3, t5}, {pl1, t6, t6_}};
    Transition T136 = {"T136", {l1, pl3, t6}, {pl1, t8, t8_}};
    Transition T137 = {"T137", {l1, pl3, t7}, {pl1, t8, t8_}};
    Transition T138 = {"T138", {l1, pl3, t8}, {pl1, t8, t8_}};

    Transition T214 = {"T214", {l2, pl1, t4}, {pl2, t4, t4_}};
    Transition T215 = {"T215", {l2, pl1, t5}, {pl2, t6, t6_}};
    Transition T216 = {"T216", {l2, pl1, t6}, {pl2, t7, t7_}};
    Transition T217 = {"T217", {l2, pl1, t7}, {pl2, t8, t8_}};
    Transition T218 = {"T218", {l2, pl1, t8}, {pl2, t5, t5_}};

    Transition T224 = {"T224", {l2, pl2, t4}, {pl2, t4, t4_}};
    Transition T225 = {"T225", {l2, pl2, t5}, {pl2, t6, t6_}};
    Transition T226 = {"T226", {l2, pl2, t6}, {pl2, t6, t6_}};
    Transition T227 = {"T227", {l2, pl2, t7}, {pl2, t7, t7_}};
    Transition T228 = {"T228", {l2, pl2, t8}, {pl2, t8, t8_}};

    Transition T234 = {"T234", {l2, pl3, t4}, {pl2, t6, t6_}};
    Transition T235 = {"T235", {l2, pl3, t5}, {pl2, t6, t6_}};
    Transition T236 = {"T236", {l2, pl3, t6}, {pl2, t7, t7_}};
    Transition T237 = {"T237", {l2, pl3, t7}, {pl2, t8, t8_}};
    Transition T238 = {"T238", {l2, pl3, t8}, {pl2, t8, t8_}};

    Transition T314 = {"T314", {l3, pl1, t4}, {pl3, t5, t5_}};
    Transition T315 = {"T315", {l3, pl1, t5}, {pl3, t7, t7_}};
    Transition T316 = {"T316", {l3, pl1, t6}, {pl3, t7, t7_}};
    Transition T317 = {"T317", {l3, pl1, t7}, {pl3, t8, t8_}};
    Transition T318 = {"T318", {l3, pl1, t8}, {pl3, t8, t8_}};

    Transition T324 = {"T324", {l3, pl2, t4}, {pl3, t4, t4_}};
    Transition T325 = {"T325", {l3, pl2, t5}, {pl3, t7, t7_}};
    Transition T326 = {"T326", {l3, pl2, t6}, {pl3, t6, t6_}};
    Transition T327 = {"T327", {l3, pl2, t7}, {pl3, t7, t7_}};
    Transition T328 = {"T328", {l3, pl2, t8}, {pl3, t8, t8_}};

    Transition T334 = {"T334", {l3, pl3, t4}, {pl3, t6, t6_}};
    Transition T335 = {"T335", {l3, pl3, t5}, {pl3, t8, t8_}};
    Transition T336 = {"T336", {l3, pl3, t6}, {pl3, t8, t8_}};
    Transition T337 = {"T337", {l3, pl3, t7}, {pl3, t8, t8_}};
    Transition T338 = {"T338", {l3, pl3, t8}, {pl3, t8, t8_}};

    Transition pick1 = {"pick1", {picker}, {l1}};
    Transition pick2 = {"pick2", {picker}, {l2}};
    Transition pick3 = {"pick3", {picker}, {l3}};

    Transition T_4 = {"T_4", {t4_, green}, {red}};
    Transition T_5 = {"T_5", {t5_, green}, {red}};
    Transition T_6 = {"T_6", {t6_, green}, {red}};
    Transition T_7 = {"T_7", {t7_, green}, {red}};
    Transition T_8 = {"T_8", {t8_, green}, {red}};

    Transition RedWait = {"RedWait", {red}, {green, picker}};

    //Definining Incoming and Outgoing of Places
    l1.incoming = {pick1};
    l1.outgoing = {T114, T115, T116, T117, T118, T124, T125, T126, T127, T128, T134, T135, T136, T137, T138};
    l2.incoming = {pick2};
    l2.outgoing = {T214, T215, T216, T217, T218, T224, T225, T226, T227, T228, T234, T235, T236, T237, T238};
    l3.incoming = {pick3};
    l3.outgoing = {T314, T315, T316, T317, T318, T324, T325, T326, T327, T328, T334, T335, T336, T337, T338};

    pl1.incoming = {T114, T115, T116, T117, T118, T124, T125, T126, T127, T128, T134, T135, T136, T137, T138};
    pl1.outgoing = {T114, T115, T116, T117, T118, T214, T215, T216, T217, T218, T314, T315, T316, T317, T318};
    pl2.incoming = {T214, T215, T216, T217, T218, T224, T225, T226, T227, T228, T234, T235, T236, T237, T238};
    pl2.outgoing = {T124, T125, T126, T127, T128, T224, T225, T226, T227, T228, T324, T325, T326, T327, T328};
    pl3.incoming = {T314, T315, T316, T317, T318, T324, T325, T326, T327, T328, T334, T335, T336, T337, T338};
    pl3.outgoing = {T134, T135, T136, T137, T138, T234, T235, T236, T237, T238, T334, T335, T336, T337, T338};

    t4.incoming = {T114, T115, T214, T224, T324};
    t4.outgoing = {};

    t5.incoming = {T124, T218, T314};
    t5.outgoing = {};

    t6.incoming = {T125, T126, T134, T135, T215, T225, T226, T234, T235, T326, T334};
    t6.outgoing = {};

    t7.incoming = {T116, T117, T127, T216, T227, T236, T315, T316, T325, T327, };
    t7.outgoing = {};

    t8.incoming = {T118, T128, T136, T137, T138, T217, T228, T237, T238, T317, T318, T328, T335, T336, T337, T338};
    t8.outgoing = {};

    t4_.incoming = {T114, T115, T214, T224, T324};
    t4_.outgoing = {T_4};

    t5_.incoming = {T124, T218, T314};
    t5_.outgoing = {T_5};

    t6_.incoming = {T125, T126, T134, T135, T215, T225, T226, T234, T235, T326, T334};
    t6_.outgoing = {T_6};

    t7_.incoming = {T116, T117, T127, T216, T227, T236, T315, T316, T325, T327, };
    t7_.outgoing = {T_7};

    t8_.incoming = {T118, T128, T136, T137, T138, T217, T228, T237, T238, T317, T318, T328, T335, T336, T337, T338};
    t8_.outgoing = {T_8};

    green.outgoing = {T_4, T_5, T_6, T_7, T_8};
    green.incoming = {RedWait};
    red.outgoing = {RedWait};
    red.incoming = {T_4, T_5, T_6, T_7, T_8};
    picker.outgoing = {pick1, pick2, pick3};
    picker.incoming = {RedWait};

    //Defining Petri Net
    net.places = {l1, l2, l3, pl1, pl2, pl3, t4, t5, t6, t7, t8, t4_, t5_, t6_, t7_, t8_, green, red, picker};
    net.transitions = {T114, T115, T116, T117, T118, T124, T125, T126, T127, T128, T134, T135, T136, T137, T138, T214, T215, T216, T217, T218, T224, T225, T226, T227, T228, T234, T235, T236, T237, T238, T314, T315, T316, T317, T318, T324, T325, T326, T327, T328, T334, T335, T336, T337, T338, pick1, pick2, pick3, T_4, T_5, T_6, T_7, T_8, RedWait};


    //Data Strcuture to hold reachability graph
    set <Node*> reachabilityGraph;

    //Data Structure to hold all the nodes that have been visited
    set <string> visited;

    //Initial Marking Node
    Node* initialNode = new Node;
    initialNode->name = "";
    
    //Loop through the places vector in the PetriNet structure to give the initial node it's name
    for (auto &place : net.places) {
        initialNode->name += to_string(place.tokens);
    }

    //Add the initial node to the visited set and the reachability graph
    visited.insert(initialNode->name);
    reachabilityGraph.insert(initialNode);

    //Call the dfs function to generate the reachability graph
    dfs(initialNode, visited, reachabilityGraph, net);

    cout<<"\n\n****WELCOME TO THE PETRI NET VERIFICATION!****\n\n";
    cout<<"Adjacency List of the Reachability Graph: \n\n";

    //Printing the adjacency list of the reachability graph
    printReachabilityGraph(reachabilityGraph);

    //Checking for dead transitions
    cout<<"\nNumber of live transitions -> "<<visitedTransitions.size()<<endl;
    cout<<"\nNumber of dead transitions -> "<<net.transitions.size() - visitedTransitions.size()<<endl<<endl;

    //Checking for Deadlock
    checkDeadlock(reachabilityGraph);

    //Checking for Boundedness
    checkBoundedness(visited);

    //Printing the Place Invariant Vector and the Constant (found through observation)
    cout<<"\nThe Place Invariant vector is -> 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1"<<endl;
    cout<<"The constant is -> 4"<<endl;

    //Verifying each of the Place Invariants mentioned in the paper
    verifyPlaceInvariant1(visited);
    verifyPlaceInvariant2(visited);
    verifyPlaceInvariant3(visited);
    verifyPlaceInvariant4(visited);



    //Hashing the names of the each marking to integers, for plotting and visualising the reachability graph
    map <string, int> mpp;
    int i = 1;

    for (auto &node : reachabilityGraph) {
        mpp[node -> name] = i; 
        i++;
    }


    //Data Structure to store all the edges of the reachability graph
    vector <pair <int, int>> edges;

    for (auto &node : reachabilityGraph) {

        int e1 = mpp[node -> name];

        for(auto adj : node->neighbour){
            int e2 = mpp[adj -> name];
            edges.push_back({e1, e2});
        }
    }

    //Storing the edges in a text file to run a python script to visualize the reachability graph
    ofstream outputFile("Generated Text Files/edges.txt");

    if (!outputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    // Writing the edges to the text file
    outputFile << "[";

    for (const auto& edge : edges) {
        outputFile << "(" << edge.first << ", " << edge.second << "), ";
    }

    // Removing the trailing comma and space
    outputFile.seekp(-2, ios_base::end);
    outputFile << "]";

    //Closing the file
    outputFile.close();


    // Open a file for writing the hash map
    ofstream outFile("Generated Text Files/hashmap.txt");

    // Check if the file is opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Print the table header to the file
    outFile << "\tMarking\t\t\t\tInteger Equivalent\n";

    // Iterating over the hashmap and writing each pair to the file
    for (const auto& pair : mpp) {
        outFile << pair.first << "\t\t\t\t" << pair.second << "\n";
    }

    // Close the file
    outFile.close();

    cout<<"\n\nStored the hashmap of markings to their integer equivalents in the file hashmap.txt in the folder `Generated Text Files`\n\n";

    // //Printing the hashmap of markings to their integer equivalents
    // cout<<endl<<endl;
    // for (const auto& pair : mpp) {
    //     std::cout << pair.first << " -> " << pair.second << std::endl;
    // }

  return 0;
}