#include <fstream>
#include <iostream>
#include "avltree.h"
#include <vector>
#include "searcher.h"
#include "graph.h"

using namespace std;

double get_timestamp_seconds(std::string & time_stamp) {

    istringstream timestamp(time_stamp);
    tm tmb;
    double r;
    timestamp >> get_time(&tmb, "%Y-%m-%d %T");    
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tmb));
    r = tp.time_since_epoch().count();
    return r;

}

AVLTree & makeTree(std::string input, std::string file) {
    std::vector<std::vector<std::string> > result = search(input, file);
    //Trees start here
    AVLTree avltree;
    for (vector<string> data: result) {
        double time_stamp = get_timestamp_seconds(data[1]);
        avltree.insert(time_stamp, data[0]);
    }
    return avltree;
}

int main(int argc, const char** argv) {
    // //First, let's get the phrase we want to search for:
    // std::string input;
    // cout<<"Please input the phrase you want to search: " << endl;
    // getline(cin, input);
    // //Then we'll open up the file we're searching in.
    // std::string file;
    // cout<< "Please input the name of the file that you want to search through: " << endl;
    // cin >> file;
    Graph g(false);
    std::vector<std::string> phrases;
    phrases.push_back("activity");
    phrases.push_back("priority");
    phrases.push_back("position");
    phrases.push_back("business ");
    for (auto it = phrases.begin(); it != phrases.end(); ++it) {
        AVLTree a = makeTree(*it, "large_test_file.txt");
        std::vector<double> inOrderTraversal = a.getInorderTraversal();
        for (double timestamp : inOrderTraversal) {
            std::cout << a.find(timestamp) << std::endl;
            g.insertVertex(a.find(timestamp));
        }
    }
}
