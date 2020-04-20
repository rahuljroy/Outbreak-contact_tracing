#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 


using namespace std;

struct graph{
    int Day;
    vector< vector<long int> > graph_for_the_day;
};

long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else{
        cout<<"File not opened"<<endl;
    }
    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    return no_vertices;
}


void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph){
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
    
    int i, j;
    long int u, v, graph_number;

    struct graph day_graphs[10];

    // vector<vector<long int>> graph1, graph2, graph3, graph4, graph5, graph6, graph7, graph8, graph9, graph10;
    vector< vector<long int> > weight, node_weights;
    long int no_vertices = 0;
    string data, file_number, txt, filename;
    char* file;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);
    cout<<"The number of vertices are : "<<no_vertices<<endl;

    // graph1.resize(no_vertices), graph2.resize(no_vertices), graph3.resize(no_vertices), graph4.resize(no_vertices), graph5.resize(no_vertices);
    // graph6.resize(no_vertices), graph7.resize(no_vertices), graph8.resize(no_vertices), graph9.resize(no_vertices), graph10.resize(no_vertices);

    weight.resize(no_vertices);
    node_weights.resize(no_vertices);

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    build_graph(file, no_vertices, node_weights);
    filename = "../../../../scratch/graph-inputs_PP/wiki-";
    txt = ".txt";


    for (i=1; i<=10; i++){
        day_graphs[i-1].Day = i;
        day_graphs[i-1].graph_for_the_day.resize(no_vertices);

        graph_number = i;
        file_number = to_string(graph_number);

        filename = filename+file_number+txt;
        strcpy(filem filename);
        build_graph(file, no_vertices, day_graphs[i-1].graph_for_the_day);
    }

    // filename = "../../../../scratch/graph-inputs_PP/wiki-6.txt";

    for (i=0; i<no_vertices; i++){
        for (j=0; j<day_graphs[6].graph_for_the_day[i].size(); j++){
            cout<<"the node weight of "<<i<<" is "<<day_graphs[6].graph_for_the_day[i][j];
        }
    }
}