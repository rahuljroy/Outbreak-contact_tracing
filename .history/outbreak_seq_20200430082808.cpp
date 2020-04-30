#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>



using namespace std;

struct graph{
    // int Day;
    vector< vector<long int> > graph_for_the_day;
};


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


void get_infected(char* filename, long int no_infected, vector<long int>& infected, int day){
    long int u;
    string data;

    ifstream myfile;

    myfile.open(filename);


    while(myfile>>u){
        infected.push_back(u);
    }
    myfile.close();
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


void get_neighbours(vector< vector<long int> > graph, long int u, vector< vector<long int> >& neighbours, vector<int>& quarantined, vector<int>& processed){
    neighbours[u] = graph[u];
}


int main(){
    
    int i, j, k, l, count=0, day = 10, flag=1;
    long int u, v, graph_number, infected_count=0, quarantined_count = 0, uninfected_count=0;
    double num;

    struct graph day_graphs;

    struct timespec start1, finish, graph_start, graph_end;
    double time_seq = 0, time_graph=0;

    vector< vector<long int> > weight, node_weights, no_of_neighbours, neighbours;
    vector<long int> infected, current_infected;
    vector<int> infected_or_not, prev_infected, processed, quarantined, infected_day, quarantined_day;
    set<int> indices;
    set<int>::iterator itr;
    
    long int no_vertices = 0, no_infected = 0;
    string data, file_number, txt, filename, filename1;
    char* file;

    ifstream myfile;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);

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
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &graph_start);


    for (i=1; i<=10; i++){
        day_graphs.graph_for_the_day.resize(no_vertices);

        graph_number = i;
        file_number = to_string(graph_number);

        filename1 = filename+file_number+txt;

        file = &filename1[0];
        build_graph(file, no_vertices, day_graphs.graph_for_the_day);
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &graph_end);
    long seconds = graph_end.tv_sec - graph_start.tv_sec; 
    long ns = graph_end.tv_nsec - graph_start.tv_nsec;
    time_graph = (double)seconds + (double)ns/(double)1000000000;

    filename = "infected.txt";
    file = &filename[0];

    no_infected = get_no_lines(file);

    get_infected(file, no_infected, infected, day);

    for (i=0; i<infected.size(); i++){
        // cout<<infected[i]<<endl;
        infected_or_not[infected[i]]=1;
        quarantined[infected[i]] = 1;
        infected_day[infected[i]] = 1;
        quarantined_day[infected[i]] = 1;
    }
    
    cout<<"the number of infected people on day 1 is "<<infected.size()<<endl;
    neighbours.resize(no_vertices);
    
    i=0;
    count = infected.size();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start1);

    while(count!=0){
        count = infected.size();
        for (j=0; j<count; j++){

            neighbours[infected[j]] = day_graphs.graph_for_the_day[infected[j]];

            for(k=0; k<neighbours[infected[j]].size(); k++){
                num = (double)((rand()%neighbours[infected[j]].size())) / neighbours[infected[j]].size();
                if(infected_or_not[neighbours[infected[j]][k]]==0){
                    if (num<0.5){
                        infected_or_not[neighbours[infected[j]][k]] = 0;
                        quarantined[neighbours[infected[j]][k]] = 1;
                        infected_day[neighbours[infected[j]][k]] = i+2;
                        quarantined_day[neighbours[infected[j]][k]] = i+2;
                    }
                    else{
                        infected_or_not[neighbours[infected[j]][k]] = 1;
                        quarantined[neighbours[infected[j]][k]] = 1;
                        infected_day[neighbours[infected[j]][k]] = i+2;
                        quarantined_day[neighbours[infected[j]][k]] = i+2;
                        current_infected.push_back(neighbours[infected[j]][k]);
                    }
                }
            }
        }

        cout<<"The number of infected people on day "<<i+2<<" is "<<current_infected.size()<<endl;
        i++;
        infected = current_infected;
        current_infected.clear();
        count = infected.size();
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finish); 
    seconds = finish.tv_sec - start1.tv_sec; 
    ns = finish.tv_nsec - start1.tv_nsec;
    time_seq = (double)seconds + (double)ns/(double)1000000000;
    printf("\nGraph read time for sequential code is,  %e", time_graph);
    printf("\nTime taken for sequential code for outbreak, excluding graph time,  is, %e", time_seq);
    printf("\nTime taken for sequential code for outbreak, inckuding graph time,  is, %e", time_seq+time_graph);

    
    // cout<<endl<<"Person_ID\tInfected\tQuarantined\tQuarantin_Start\tQuarantine_end"<<endl;
    for (i=0; i<no_vertices; i++){
        if (infected_or_not[i] ==1){
            // cout<<i<<"\t"<<infected_or_not[i]<<"\t"<<quarantined[i]<<"\t"<<quarantined_day[i]<<"\t"<<quarantined_day[i]+20<<endl;
            infected_count++;
            quarantined_count++;
        }
        else if(infected_or_not[i]==0 && quarantined[i]==1){
            // cout<<i<<"\t"<<infected_or_not[i]<<"\t"<<quarantined[i]<<"\t"<<quarantined_day[i]<<"\t"<<quarantined_day[i]+20<<endl;
            quarantined_count++;
        }
        else{
            // cout<<i<<"\t"<<infected_or_not[i]<<"\t"<<quarantined[i]<<"\t"<<quarantined_day[i]<<"\t0"<<endl;
            uninfected_count++;
        }
    }
    // cout<<"Infected Count: "<<infected_count<<endl;
    // cout<<"Quanrantined Count: "<<quarantined_count<<endl;
    // cout<<"Uninfected count: "<<uninfected_count<<endl;
}