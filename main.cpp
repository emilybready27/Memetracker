#include <fstream>
#include <iostream>
#include "avltree.h"
#include <vector>

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
    string input;
    cout<<"Please input the phrase you want to search: " << endl;
    getline(cin, input);
    //Then we'll open up the file we're searching in.
    string file;
    cout<< "Please input the name of the file that you want to search through: " << endl;
    cin >> file;
    vector<vector<string> > quotes = vector<vector<string> >();
    ifstream infile;
    infile.open (file);
    cout<< "Searching..." << endl;
    //Now that we have these two, let's begin sifting.
    if (infile.is_open()) {
        vector<string> data = vector<string>();  //Let's make a data vector to store our time and place.
        string line; //And this is the line in the file.
        bool found = false; //This bool helps make sure no duplicates occur.
        while (getline(infile, line)) {
            //Let's read every line in the document...
            if (line == "") {
                //If the line is empty, we exited a block and should clear the data.
                vector<string> data = vector<string>();
                continue;
            }
            if (line.at(0) == 'P') {
                //If the line starts with 'P', we entered a new block: pull the link...
                data.push_back(line.substr(2, line.size()));
                //...and reset our found boolean to false.
                found = false;
            } else if (line.at(0) == 'T') {
                //If we have a 'T', we need to input the timestamp into our data.
                data.push_back(line.substr(2, line.size()));
            } else if (line.at(0) == 'Q') {
                //If we have 'Q', we found a quote! Check if:
                //(A) the line matches our target and (B) it's not akin to another one in the same block.
                if ("Q	" + input == line && !found) {
                    //If those two ring true, send this block to our list of matches and set found to true. 
                    quotes.push_back(data);
                    found = true;
                }
            }
        }
        AVLTree avltree;
        for (vector<string> data: quotes) {
            double time_stamp = get_timestamp_seconds(data[1]);
            avltree.insert(time_stamp, data[0]);

        }
        avltree.getInorderTraversal();
    }

}





