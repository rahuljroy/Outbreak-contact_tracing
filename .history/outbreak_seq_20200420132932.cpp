#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else
        cout<<"File not opened"<<endl;
    }
    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    return no_vertices;
}


void build_graph(char* filename, long int no_vertices, vector<vector<long int>>& graph){
    long int u, node_weight;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open(filename);

    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else{
        cout<<"File not opened"<<endl;
    }

    while(myfile>>u>>node_weight){
        graph[u].push_back(node_weight);
    }

}
int main(int argc, char** argv){
    
    int i, j, graph_num;
    long int u, v;
    vector<vector<long int>> graph1, graph2, graph3, graph4, graph5, graph6, graph7, graph8, graph9, graph10;
    vector<vector<long int>> weight, node_weights;
    long int no_vertices = 0;
    string data, graph_number;

    map<int, vector<vector<long int>>> graph;

    graph[1] = graph1, graph[2] = graph2, graph[3] = graph3, graph[4] = graph4, graph[5] = graph5, graph[6] = graph6, graph[7] = graph7, graph[8] = graph8, graph[9] = graph9, graph[10] = graph10;


    for (i=0; i<=10; i++){
        graph[1].resize(no_vertices);
    }

    char* filename = "../../../../scratch/graph-inputs_PP/wiki-1.txt";
    no_vertices = get_no_lines(filename);
    cout<<"The number of vertices are : "<<no_vertices<<endl;

    // graph1.resize(no_vertices);
    // weight.resize(no_vertices);
    // node_weights.resize(no_vertices);

    filename = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    build_graph(filename, no_vertices, graph[1]);

    
    // for (i=0; i<no_vertices; i++){
    //     for (j=0; j<node_weights[i].size(); j++){
    //         cout<<"the node weight of "<<i<<" is "<<node_weights[i][j];
    //     }
    // }
}