#include <fstream>
#include <iostream>
#include "avltree.h"
#include <vector>
#include "searcher.h"

using namespace std;

double get_timestamp_seconds(std::string & time_stamp) {

    istringstream timestamp(time_stamp);
    tm tmb;
    double r;
    timestamp >> get_time(&tmb, "%Y-%m-%d %T") >> r;    
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return r;

}

int main(int argc, const char** argv) {
    //First, let's get the phrase we want to search for:
    std::string input;
    cout<<"Please input the phrase you want to search: " << endl;
    getline(cin, input);
    //Then we'll open up the file we're searching in.
    std::string file;
    cout<< "Please input the name of the file that you want to search through: " << endl;
    cin >> file;
    std::vector<std::vector<std::string> > result = search(input, file);
    //Trees start here
    AVLTree avltree;
    for (vector<string> data: result) {
        double time_stamp = get_timestamp_seconds(data[1]);
        avltree.insert(time_stamp, data[0]);
    }
    std::vector<double> inOrderTraversal = avltree.getInorderTraversal();
    for (double timestamp : inOrderTraversal) {
        std::cout << avltree.find(timestamp) << std::endl;
    }


}
