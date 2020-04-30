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

void get_infected(char* filename, long int no_infected, long int **infected, int rank){
    long int u, i=0;
    string data;

    ifstream myfile;

    myfile.open(filename);

    infected[rank] = new long int[no_infected];

    while(myfile>>u){
        infected[rank][i] = u;
        i++;
    }
    myfile.close();
}

void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph, long int start, long int end){
    long int u, node_weight;
    string data;

    ifstream myfile;

    myfile.open(filename);

    // if (myfile){
    //     cout<<"file opened"<<endl;
    // }
    // else{
    //     cout<<"file not opened"<<endl;
    // }


    while(myfile>>u>>node_weight){
        if (u>=start && u<=end){
            graph[u-start].push_back(node_weight);
        }
    }
    myfile.close();
}


int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    MPI_Comm comm;
    comm = MPI_COMM_WORLD;

    int myrank, num_procs, i, graph_number, j, k, l;
    double num;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &num_procs);

    string data, file_number, txt, filename, filename1;

    char* file;
    long int no_vertices=0, per_process, start, end;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);
    // cout<<"number of vertices "<<no_vertices<<" by proc "<<myrank<<endl;

    per_process = no_vertices/num_procs;
    start = myrank*per_process;

    if (myrank==num_procs-1){
        end = no_vertices;
    }
    else{
        end = start+per_process;
    }
    // cout<<"Rank: "<<myrank<<" start: "<<start<<" end: "<<end<<endl;

    vector< vector<long int> > node_weights, graph;
    node_weights.resize(no_vertices);
    graph.resize(end-start);

    filename = "../../../../scratch/graph-inputs_PP/wiki-";
    txt = ".txt";

    double graph_start, graph_end;
    graph_start = MPI_Wtime();

    for (i=1; i<=10; i++){

        file_number = std::to_string(i);

        filename1 = filename+file_number+txt;

        file = &filename1[0];
        build_graph(file, no_vertices, graph, start, end);
        // cout<<"Finished building graph "<<i<<" by proc "<<myrank<<endl;
    }
    MPI_Barrier(comm);
    graph_end = MPI_Wtime();

    filename = "infected.txt";
    file = &filename[0];

    int *infected_or_not, *quarantined, *infected_day, *quarantined_day;
    infected_or_not = new int[no_vertices];
    quarantined = new int[no_vertices];
    infected_day = new int[no_vertices];
    quarantined_day = new int[no_vertices];
    for(i=0; i<no_vertices; i++){
        infected_or_not[i] = 0;
        quarantined[i] = 0;
        infected_day[i] = 0;
        quarantined_day[i] =0;
    }
    // cout<<"Initialization done"<<myrank<<endl;

    long int *new_infected, **infected;
    long int *old_arraysize, *new_arraysize;
    old_arraysize = new long int[num_procs];
    new_arraysize = new long int[num_procs];
    long int initial_infected=0, current_infected=0, neighbour_size, size=0, new_size=0, totalsize=0, new_infected_size=0;
    

    vector<long int>neighbours;
    infected = new long int*[num_procs];
    new_infected = new long int[100];
    new_infected_size = 100;

    initial_infected = get_no_lines(file);
    current_infected = 0;
    totalsize=initial_infected;

    get_infected(file, initial_infected, infected, myrank);
    for (i=0; i<num_procs; i++){
        if (i==myrank){
            new_arraysize[myrank] = initial_infected;
        }
        else{
            new_arraysize[i] = 0;
        }
    }
    if (myrank==0){
        cout<<"The number of infected people on day 1 is "<<new_arraysize[myrank]<<endl;
    }

    double t1, t2;
    int day=0;
    t1 = MPI_Wtime();  // time start

    while(totalsize){
        for (i=0; i<num_procs; i++){
            for (j=0; j<new_arraysize[i]; j++){
                if ((infected[i][j]>=start) && (infected[i][j]<end)){
                    neighbours = graph[infected[i][j]-start];
                    for (k=0; k<neighbours.size(); k++){
                        if (infected_or_not[neighbours[k]]==0){
                            num = (double)((rand()%neighbours.size())) / neighbours.size();

                            if (num < 0.5){
                                infected_or_not[neighbours[k]] = 0;
                                quarantined[neighbours[k]] = 1;
                                quarantined_day[neighbours[k]] = day+2;
                            }
                            else{
                                if (quarantined[neighbours[k]]==0){
                                    infected_or_not[neighbours[k]] = 1;
                                    quarantined[neighbours[k]] = 1;
                                    current_infected++;

                                    if (current_infected>=(new_infected_size)){
                                        new_size = new_infected_size+100;
                                        long int *newArr;
                                        newArr = new long int[new_size];

                                        for (l=0; l<new_infected_size; l++){
                                            newArr[l] = new_infected[l];
                                        }
                                        new_infected_size=new_size;

                                        new_infected = newArr;
                                        new_infected[current_infected-1] = neighbours[k];
                                    }
                                    else{
                                        new_infected[current_infected-1] = neighbours[k];
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
        totalsize=0;

        MPI_Allgather(&current_infected, 1, MPI_LONG, new_arraysize, 1, MPI_LONG, comm);
        for (l=0; l<num_procs; l++){
            infected[l] = new long int[new_arraysize[l]];
            totalsize+=new_arraysize[l];
        }
        if (myrank==0){
            cout<<"The number of infected people on day "<<day+2<<" is "<<totalsize<<endl;
        }
        infected[myrank] = new_infected;
        for (l=0; l<num_procs; l++){
            MPI_Bcast(infected[l], new_arraysize[l], MPI_LONG, l, comm);
        }
        for(l=0;l<num_procs;l++){
            for(k=0; k<new_arraysize[l];k++){
                infected_or_not[infected[l][k]]=1;
                quarantined[infected[l][k]] = 1;
                infected_day[infected[l][k]] = day+2;
                quarantined_day[infected[l][k]] = day+2;
            }
        }

        current_infected=0;
        new_infected_size=0;
        day++;
    }
    t2 = MPI_Wtime();  // time ends
    if(myrank==0){
        // cout<<"The time taken for the code is: "<<t2-t1<<endl;
        printf("\nGraph read time for parallel code is,  %e", (graph_end-graph_start));
        printf("\nTime taken for parallel code for outbreak, excluding graph time,  is, %e", (t2-t1));
        printf("\nTime taken for parallel code for outbreak, inckuding graph time,  is, %e\n", (t2-t1+graph_end-graph_start));

        long int infected_count=0, quarantined_count=0, uninfected_count=0;
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
    MPI_Finalize();
}