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

int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &num_procs);
    
}



