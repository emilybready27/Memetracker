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

}
