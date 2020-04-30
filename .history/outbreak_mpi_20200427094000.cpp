#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include "mpi.h"

using namespace std;

long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    return no_vertices;
}

void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph){
    long int u, node_weight;
    string data;

    ifstream myfile;

    myfile.open(filename);


    while(myfile>>u>>node_weight){
        graph[u].push_back(node_weight);
    }
    myfile.close();
    // cout<<"Graph created"<<endl;
}


int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    int myrank, num_procs;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &num_procs);

    char* file;
    long int no_vertices=0, per_process, start, end;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);

    per_process = no_vertoces/num_procs;
    start = myrank*per_process;
    if (myrank==num_procs-1){
        end = no_vertoces-start;
    }
    else{
        end = start+per_process;
    }

    vector< vector<long int> > node_weights, graph;
    node_weights.resize(no_vertices);
    graph.resize(end-start);

    
}



