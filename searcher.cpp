#include "searcher.h"

using namespace std;

std::vector<std::vector<std::string> > search(std::string input, std::string file) {
    //If the input's too small, dismiss the search.
    if (input.size() < 8) {
        cout << "Sorry, but we can't sift for such a small phrase, maybe something larger?" << endl;
        return std::vector<std::vector<std::string> >();
    }
    //If not, let's make a bin to store our results.
    std::vector<std::vector<std::string> > quotes = std::vector<std::vector<std::string> >();
    ifstream infile;
    infile.open (file);
    //Let's begin sifting.
    if (infile.is_open()) {
        cout << "Searching for " << input << "..." << endl;
        vector<std::string> data = std::vector<std::string>();  //Let's make a data vector to store our time and place.
        string line; //And this is the line in the file.
        bool found = false; //This bool helps make sure no duplicates occur.
        while (getline(infile, line)) {
            //Let's read every line in the document...
            if (line == "") {
                //If the line is empty, we exited a block and should clear the data.
                data = std::vector<std::string>();
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
                //If we have 'Q', we found a quote! For every segment, try to find the phrase:
                if (line.find(input, 2) != string::npos && !found) {
                      //If we found it, add this to our results and set 'found' to true.
                      quotes.push_back(data);
                      found = true;
                }
            }
        }
        //After we searched through the whole document, let's print out the results.
        for (vector<string> data: quotes) {
            //cout<<data[0]<<std::endl<<data[1]<<std::endl<<std::endl;
        }
    }

    return quotes;

}