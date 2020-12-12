#include "graph.h"
#include <map>
#include <tuple>
#include <set>
#include <stack>

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted),directed(false)
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed)
{
}


vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
       
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}

std::map<std::tuple<Vertex, Vertex>, int> Graph::floydWarshall() {
    std::map<std::tuple<Vertex, Vertex>, int> shortest_paths;
    std::vector<Vertex> v = getVertices();
    std::vector<Edge> e = getEdges();
 
    for (unsigned long i = 0; i < v.size(); i++) {
        for (unsigned long j = 0; j < v.size(); j++) {
            std::tuple<Vertex, Vertex> * vertices = new std::tuple<Vertex, Vertex>(v[i], v[j]);
            if (v[i] != v[j] && assertEdgeExists(v[i], v[j], "floydWarshall")) {
                shortest_paths[*vertices] = e[i].getWeight();
            }
            delete vertices;
        }
    }
    
    for (unsigned long k = 0; k < v.size(); k++) {
        int count = 0;
        for (unsigned long i = 0; i < v.size(); i++) {
            for (unsigned long j = 0; j < v.size(); j++) {
                std::tuple<Vertex, Vertex> * ik = new std::tuple<Vertex, Vertex>(v[i], v[k]);
                std::tuple<Vertex, Vertex> * ij = new std::tuple<Vertex, Vertex>(v[i], v[j]);
                std::tuple<Vertex, Vertex> * kj = new std::tuple<Vertex, Vertex>(v[k], v[j]);
                if (shortest_paths.find(*ij) != shortest_paths.end()) {
                    if (shortest_paths.find(*ik) != shortest_paths.end() && shortest_paths.find(*kj) != shortest_paths.end() && shortest_paths[*ik] + shortest_paths[*kj] < shortest_paths[*ij]) {
                        count++;
                        shortest_paths[*ij] = shortest_paths[*ik] + shortest_paths[*kj];
                        
                    }

                } else {
                    if (shortest_paths.find(*ik) != shortest_paths.end() && shortest_paths.find(*kj) != shortest_paths.end()) {
                        count++;
                        shortest_paths[*ij] = shortest_paths[*ik] + shortest_paths[*kj];
                        

                    }
                }

                delete ik;
                delete ij;
                delete kj;
            }
        }
        number_shortest_path_vertex[v[k]] = count;

    }
    total_paths = shortest_paths.size();
    return shortest_paths;
}

double Graph::Centrality(Vertex &v) {
    double num_short_paths = number_shortest_path_vertex[v];
    std::cout <<" Number of shortest paths for "  << v << " are " << num_short_paths << endl;
    std::cout <<" Number of total paths  are: " << total_paths << endl;
    double centrality = num_short_paths/total_paths;
    std::cout <<" Centrality for " <<  v << " is : "<< centrality << endl;
    if (centrality < 0 || centrality > 1) {
        std::cout << "Invalid value for centrality of " <<  v << endl;
        return -1;
    } else {
        return centrality;
    }
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

std::vector<Vertex> Graph::DFS(Vertex start) {
    // create set of references to visited vertices
    std::set<Vertex> visited;
    std::vector<Vertex> to_return;
    // create stack of references to UNVISITED vertices
    std::stack<Vertex> stack;
    Vertex curr_vertex;
    stack.push(start);
    visited.insert(start);
    to_return.push_back(start);
    while (!stack.empty()) {
        // 1. current vertex = stack.pop();
        curr_vertex = stack.top();
        stack.pop();
        // 2. do whatever with it (print it probably)
        std::cout << curr_vertex << std::endl;
        // 3. for each neighbor of the current vertex:
        for (const Vertex & neighbor : getAdjacent(curr_vertex)) {
            // - if neighbor is not in visited,
            if (visited.find(neighbor) == visited.end()) {
                // - stack.push(neighbor)
                stack.push(neighbor);
                // - visited.add(neighbor)
                visited.insert(neighbor);
                to_return.push_back(neighbor);
            }
        }
    }
    return to_return;
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = title + ".png";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    // sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
    //     return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    // });
    std::cout << "reached line " << __LINE__ << std::endl;

    int xpos1 = 100;
    int xpos2 = 100;
    std::cout << "reached line " << __LINE__ << std::endl;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }
    std::cout << "reached line " << __LINE__ << std::endl;

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";
    std::cout << "reached line " << __LINE__ << std::endl;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";                
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (weighted && it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";
            
            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }
    std::cout << "reached line " << __LINE__ << std::endl;

    neatoFile << "}";
    neatoFile.close();
    std::cout << "reached line " << __LINE__ << std::endl;
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    std::cout << "reached line " << __LINE__ << std::endl;
    int result = system(command.c_str());
    std::cout << "reached line " << __LINE__ << std::endl;


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }
    std::cout << "reached line " << __LINE__ << std::endl;

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    std::cout << "reached line " << __LINE__ << std::endl;
    system(rmCommand.c_str());
}
