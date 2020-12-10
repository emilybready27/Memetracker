#include <fstream>
#include <iostream>
#include "avltree.h"
#include <vector>
#include "searcher.h"
#include "graph.h"

using namespace std;

/*
double get_timestamp_seconds(std::string & time_stamp) {

    istringstream timestamp(time_stamp);
    tm tmb;
    double r;
    timestamp >> get_time(&tmb, "%Y-%m-%d %T");    
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tmb));
    r = tp.time_since_epoch().count();
    return r;

}

AVLTree *& makeTree(std::string input, std::string file) {
    std::vector<std::vector<std::string> > result = search(input, file);
    //Trees start here
    AVLTree *avltree = new AVLTree();
    for (vector<string> data: result) {
        double time_stamp = get_timestamp_seconds(data[1]);
        avltree->insert(time_stamp, data[0]);
    }
    std::cout << "lol";
    return avltree;
}
*/

int main() {
    // //First, let's get the phrase we want to search for:
    // std::string input;
    // cout<<"Please input the phrase you want to search: " << endl;
    // getline(cin, input);
    // //Then we'll open up the file we're searching in.
    // std::string file;
    // cout<< "Please input the name of the file that you want to search through: " << endl;
    // cin >> file;
    Graph g(true, true);
    std::vector<std::string> phrases;
    // std::vector<std::vector<std::string>> word1 = search("activity" , "large_test_file");
    // std::vector<std::vector<std::string>> word2 = search("priority" , "large_test_file");
    // std::vector<std::vector<std::string>> word3 = search("position" , "large_test_file");
    // std::vector<std::vector<std::string>> word4 = search("business " , "large_test_file");
    phrases.push_back("activity");
    phrases.push_back("priority");
    phrases.push_back("position");
    phrases.push_back("business ");

    /* Test for one word
    AVLTree *a = new AVLTree("activity", "large_test_file");
    std::vector<double> inOrderTraversal = a->getInorderTraversal();
    for (double timestamp : inOrderTraversal) {
        std::cout << "URL: " << a->find(timestamp) << std::endl;
        g.insertVertex(a->find(timestamp));
    }*/
    Vertex start_vertex;
    for (auto it = phrases.begin(); it != phrases.end(); ++it) {
        AVLTree * a = new AVLTree(&g, *it, "large_test_file");
        std::cout << "height of tree for the word " << *it << " is " << a->getRoot()->height << std::endl;
        if (*it == "position") {
            start_vertex = a->getRoot()->url;
            std::cout << a->getRoot()->url << std::endl;
        }
        std::vector<double> inOrderTraversal = a->getInorderTraversal();
        // for (double timestamp : inOrderTraversal) {
        //     // std::cout << "URL: " << a->find(timestamp) << std::endl;
        // }
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


    
    // for (const std::vector<std::string> & doc : word1) {
    //     for (const std:: vector<std::string> & other_doc : word1) {
    //         if (doc != other_doc && !g.edgeExists(doc[0], other_doc[0])) {
    //             g.insertEdge(doc[0], other_doc[0]);
    //         }
    //     }
    // }
    // for (const std::vector<std::string> & doc : word2) {
    //     for (const std:: vector<std::string> & other_doc : word2) {
    //         if (doc != other_doc && !g.edgeExists(doc[0], other_doc[0])) {
    //             g.insertEdge(doc[0], other_doc[0]);
    //         }
    //     }
    // }
    // for (const std::vector<std::string> & doc : word3) {
    //     for (const std:: vector<std::string> & other_doc : word3) {
    //         if (doc != other_doc && !g.edgeExists(doc[0], other_doc[0])) {
    //             g.insertEdge(doc[0], other_doc[0]);
    //         }
    //     }
    // }
    // for (const std::vector<std::string> & doc : word4) {
    //     for (const std:: vector<std::string> & other_doc : word4) {
    //         if (doc != other_doc && !g.edgeExists(doc[0], other_doc[0])) {
    //             g.insertEdge(doc[0], other_doc[0]);
    //         }
    //     }
    // }

} 
