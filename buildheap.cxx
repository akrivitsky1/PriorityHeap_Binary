#include <iostream>
#include <fstream>
#include "priorityqueue.h"

using json = nlohmann::json;

int main(int argc, char** argv) { // parsing the input
    if (argc != 2) { //if not equal to 2, means wrong input given
        std::cerr << "Usage incorrect. Enter in a json file" << std::endl;
        return 1; //end code
    }
    std::ifstream file(argv[1]); //creates a file with json file input
    // Parse the JSON file
    json input; //creates json object
    file >> input; //reads file into json object
    file.close(); //close file

    // Create priority queue
    int max_size = input["metadata"]["maxHeapSize"].get<int>(); //get max size of queues
    PriorityQueue heap(max_size); //sets heap max size

    // Execute operations
    json::iterator it; //iterator
    int num_ops = 0; // Counter for number of operations
    for (it = input.begin(); it != input.end(); ++it) {
        if (it.key() == "metadata") { //keep going if metadata
            continue;
        }
        json op = it.value(); //operation for one section
        if (op["operation"] == "insert") { //if insert
            Key k = op["key"].get<Key>(); // add key to heap
            heap.insert(k); //insert to heap
        } else if (op["operation"] == "removeMin") { //remove Min value
            heap.removeMin();
        } else {
            std::cerr << "Invalid operation: " << op["operation"] << std::endl; //operation given is invalid
            return 1;
        }
        num_ops++; //increase number of operators
    }

    // Output priority queue as JSON object
    json output = heap.JSON(); 
    output["metadata"]["maxHeapSize"] = output["metadata"]["max_size"]; // update key name
    output["metadata"]["numOperations"] = num_ops; // Add numOperations field
    output["metadata"]["max_size"] = max_size; // Add max_size field
    std::cout << output.dump(2) << std::endl; //print to screen

    return 0;
}
