#include <fstream>
#include <iostream>
#include "avltree.h"
#include <vector>
#include "searcher.h"
#include "graph.h"

using namespace std;

int main() {
    Graph g(true, true);
    std::vector<std::string> phrases;
   
    phrases.push_back("activity");
    phrases.push_back("priority");
    phrases.push_back("position");
    phrases.push_back("business ");

   
    Vertex start_vertex;
    for (auto it = phrases.begin(); it != phrases.end(); ++it) {
        AVLTree * a = new AVLTree(&g, *it, "large_test_file");
        std::cout << "height of tree for the word " << *it << " is " << a->getRoot()->height << std::endl;
        if (*it == "position") {
            start_vertex = a->getRoot()->url;
            std::cout << a->getRoot()->url << std::endl;
        }
        std::vector<double> inOrderTraversal = a->getInorderTraversal();
        std::cout << std::endl;
        delete a;
        a = NULL;
    }
    g.DFS(start_vertex);
    g.print();
    std::map<std::tuple<Vertex, Vertex>, int> path_lengths = g.floydWarshall();
    for (auto it = path_lengths.begin(); it != path_lengths.end(); ++it) {
        std::cout << "the shortest path between " << std::get<0>(it->first) << " and " << std::get<1>(it->first) << " is " << it->second << std::endl;

    }
    for (Vertex v : g.getVertices()) {
        g.Centrality(v);
    }





  

} 
