#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 
#include <stdlib.h>


using namespace std;

struct graph{
    int Day;
    vector< vector<long int> > graph_for_the_day;
};

struct neighbours{
    long int patient_id;
    int infected_or_not;
};


long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

    // if(myfile){
    //     cout<<"File Opened"<<endl;
    // }
    // else{
    //     cout<<"File not opened"<<endl;
    // }
    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    return no_vertices;
}


void get_infected(char* filename, long int no_infected, vector< vector<long int> >& infected, int day){
    long int u;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open(filename);

    // if(myfile){
    //     cout<<"File Opened"<<endl;
    // }
    // else{
    //     cout<<"File not opened"<<endl;
    // }

    while(myfile>>u){
        infected[day-10].push_back(u);
    }
    myfile.close();
    // cout<<"Graph created"<<endl;
}


void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph){
    long int u, node_weight;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open(filename);

    // if(myfile){
    //     cout<<"File Opened"<<endl;
    // }
    // else{
    //     cout<<"File not opened"<<endl;
    // }

    while(myfile>>u>>node_weight){
        graph[u].push_back(node_weight);
    }
    myfile.close();
    // cout<<"Graph created"<<endl;
}


void get_neighbours(vector< vector<long int> > graph, long int u, vector< vector<long int> >& neighbours, vector<int>& quarantined, vector<int>& processed){

    int i=0;
    // cout<<graph[u].size()<<endl;
    for (i=0; i<graph[u].size(); i++){
        if (processed[graph[u][i]]==0){
            neighbours[u].push_back(graph[u][i]);
            quarantined[graph[u][i]] = 1;
            processed[graph[u][i]] = 1;
        }
    }
    // cout<<"neighbours size is "<<neighbours[u].size()<<endl;
}


int main(){
    
    int i, j, k, l, count=0, day = 10, flag=1;
    long int u, v, graph_number, size = 100;
    double num;

    struct graph day_graphs[10];

    vector< vector<long int> > weight, node_weights, no_of_neighbours, infected, neighbours;
    vector<int> infected_or_not, prev_infected, processed, quarantined, infected_day, quarantined_day;
    set<int> indices;
    set<int>::iterator itr;
    
    long int no_vertices = 0, no_infected = 0;
    string data, file_number, txt, filename, filename1;
    char* file;

    ifstream myfile;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);
    // cout<<"The number of vertices are : "<<no_vertices<<endl;

    no_of_neighbours.resize(no_vertices);
    weight.resize(no_vertices);
    node_weights.resize(no_vertices);
    infected_or_not.resize(no_vertices, 0);
    prev_infected.resize(no_vertices, 0);
    processed.resize(no_vertices, 0);
    quarantined.resize(no_vertices);
    infected_day.resize(no_vertices, 0);
    quarantined_day.resize(no_vertices, 0);


    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    build_graph(file, no_vertices, node_weights);
    filename = "../../../../scratch/graph-inputs_PP/wiki-";
    txt = ".txt";


    for (i=1; i<=10; i++){
        day_graphs[i-1].Day = i;
        day_graphs[i-1].graph_for_the_day.resize(no_vertices);

        graph_number = i;
        file_number = to_string(graph_number);

        // filename.append(file_number);
        // filename.append(txt);
        filename1 = filename+file_number+txt;

        file = &filename1[0];
        // cout<<file<<endl;
        build_graph(file, no_vertices, day_graphs[i-1].graph_for_the_day);
        cout<<"Graph "<<i<<" built"<<endl;
    }

    // filename = "../../../../scratch/graph-inputs_PP/wiki-6.txt";

    for (k=0; k<10; k++){
        count = 0;
        for (i=0; i<no_vertices; i++){
            no_of_neighbours[i].push_back(day_graphs[k].graph_for_the_day[i].size());
        }
    }
        // cout<<"The final non zero count is "<<count<<" for graph "<<k<<endl;

    // for (i=0; i<no_vertices; i++){
    //     for (j=0; j<no_of_neighbours[i].size(); j++){
    //         cout<<no_of_neighbours[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }

    filename = "infected.txt";
    file = &filename[0];

    no_infected = get_no_lines(file);

    infected.resize(10);
    get_infected(file, no_infected, infected, day);

    for (i=0; i<infected.size(); i++){
        for (j=0; j<infected[i].size(); j++){
            // cout<<"day "<<i+10<<" : "<<infected[i][j]<<endl;
            infected_or_not[infected[i][j]]=1;
            quarantined[infected[i][j]] = 1;
            infected_day[infected[i][j]] = 1;
            quarantined_day[infected[i][j]] = 1;
        }
    }

    neighbours.resize(no_vertices);

    for (i=0; i<no_vertices; i++){
        processed.resize(no_vertices, 0);
            
        for (k=i; k<10; k++){
            get_neighbours(day_graphs[k].graph_for_the_day, infected[i][j], neighbours, quarantined, processed);
        }
    }
    i=0;
    while (flag!=0){
        if (infected.size()<i+1){
            infected.resize(i+10);
        }
        for (j=0; j<infected[i].size(); j++){
            cout<<"checking for: "<<infected[i][j]<<endl;
            // processed.resize(no_vertices, 0);
            
            // for (k=i; k<10; k++){
            //     get_neighbours(day_graphs[k].graph_for_the_day, infected[i][j], neighbours, quarantined, processed);
            // }
            // cout<<"size of neighbours for "<<infected[i][j]<<" is "<<neighbours[infected[i][j]].size()<<endl;
            // for (k=0; k<neighbours[infected[0][j]].size(); k++){
            //     cout<<"neighbour of the infected guy "<<infected[0][j]<<" is: "<<neighbours[infected[0][j]][k]<<endl;
            // }
            // cout<<"Neighbours from 10 graphs found out for "<<infected[i][j]<<endl;

            for (k=0; k<neighbours[infected[i][j]].size(); k++){
                num = (double)((rand()&neighbours[infected[i][j]].size()) / neighbours[infected[i][j]].size());
                if (infected_or_not[neighbours[infected[i][j]][k]] != 1){
                    if (num<0.5){
                        infected_or_not[neighbours[infected[i][j]][k]] = 0;
                        // quarantined[neighbours[infected[i][j]][k]] = 1;
                        infected_day[neighbours[infected[i][j]][k]] = i+2;
                        quarantined_day[neighbours[infected[i][j]][k]] = i+2;
                    }
                    else{
                        infected_or_not[neighbours[infected[i][j]][k]] = 1;
                        // quarantined[neighbours[infected[i][j]][k]] = 1;
                        infected_day[neighbours[infected[i][j]][k]] = i+2;
                        quarantined_day[neighbours[infected[i][j]][k]] = i+2;
                        infected[i+1].push_back(neighbours[infected[i][j]][k]);
                    }
                }
            }
            // while (indices.size() < (int) (5*neighbours[infected[i][j]].size()/10)){
            //     indices.insert(rand() % neighbours[infected[i][j]].size());
            //     // cout<<"Indices of the infected created for "<<infected[i][j]<<endl;
            // }
            
            // for (itr=indices.begin(); itr!=indices.end(); ++itr){
            //     if (infected_or_not[neighbours[infected[i][j]][*itr]]!=1){
            //         // cout<<"Infected person updated"<<endl;
            //         infected_or_not[neighbours[infected[i][j]][*itr]] = 1;
            //         // if (infected.size()<i+1){
            //         //     infected.resize(i+10);
            //         // }
            //         infected[i+1].push_back(neighbours[infected[i][j]][*itr]);
            //     }
            // }
            // indices.clear();
            // cout<<"indices cleared"<<endl;
        }
        cout<<"new infected vector row created of size "<<infected[i+1].size()<<endl;

        
        if (i!=0){
            // for (l=0; l<infected_or_not.size(); l++){
            //     if (prev_infected[l] != infected_or_not[l]){
            //         flag = 0;
            //     }
            // }
            if (prev_infected==infected_or_not){
                flag=0;
            }
        }
        // cout<<"Check for similarity done: "<<i<<endl;

        i++;
        prev_infected.swap(infected_or_not);
        // cout<<"Assignment done: "<<i<<endl;

    }

    for (i=0; i<no_vertices; i++){
        if (infected_or_not[i] == 1){
            cout<<i<<" : Infected"<<endl;
        }
        else{
            cout<<i<<" : Not infected"<<endl;
        }
    }
    // cout<<"code executed"<<endl;
}